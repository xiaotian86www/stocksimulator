#include "stockexchange.h"
#include "stockclear.h"

bool Entrust::operator<(const Entrust& entrust)
{
	if (m_uPrice == entrust.m_uPrice)
	{
		if (entrust.m_eDirection == Direction::BUY)
		{
			return m_uTimeStamp > entrust.m_uTimeStamp;
		}
		else
		{
			return m_uTimeStamp < entrust.m_uTimeStamp;
		}
	}
	else
	{
		return m_uPrice < entrust.m_uPrice;
	}
}

StockExchange StockExchange::m_instance;

StockExchange::StockExchange()
	: m_stock{}
{

}

StockExchange::~StockExchange()
{

}

StockExchange& StockExchange::GetInstance()
{
    return m_instance;
}

void StockExchange::OnEntrust(uint64_t uStockHolderId, uint64_t uAmount, uint64_t uPrice, Direction eDirection, uint64_t uTimeStamp)
{
	switch (eDirection)
	{
	case Direction::BUY:
		m_buyEntrusts.push_back(Entrust{ uPrice, uAmount, 0, uTimeStamp, uStockHolderId, eDirection });
		break;
	case Direction::SALE:
		m_saleEntrusts.push_back(Entrust{ uPrice, uAmount, 0, uTimeStamp, uStockHolderId, eDirection });
		break;
	default:
		break;
	}
}

void StockExchange::OnTime(uint64_t uTime)
{
	std::list<Deal> deals;
	uint64_t uDealPrice = 0;
	uint64_t uTotalDealAmount = 0;
	if (!m_buyEntrusts.empty() && !m_saleEntrusts.empty())
	{

		m_buyEntrusts.sort();
		m_saleEntrusts.sort();

		auto&& buyEntrustIter = m_buyEntrusts.rbegin();
		auto&& saleEntrustIter = m_saleEntrusts.begin();
		while (buyEntrustIter != m_buyEntrusts.rend()
			&& saleEntrustIter != m_saleEntrusts.end()
			&& buyEntrustIter->m_uPrice >= saleEntrustIter->m_uPrice)
		{
			uint64_t uDealAmount = 0;
			if (buyEntrustIter->m_uAmount - buyEntrustIter->m_uDealAmount > saleEntrustIter->m_uAmount - saleEntrustIter->m_uDealAmount)
			{
				uDealAmount = saleEntrustIter->m_uAmount - saleEntrustIter->m_uDealAmount;
				uDealPrice = buyEntrustIter->m_uPrice;
				buyEntrustIter->m_uDealAmount += uDealAmount;
				saleEntrustIter->m_uDealAmount += uDealAmount;
				deals.push_back(Deal{ 0, saleEntrustIter->m_uDealAmount, saleEntrustIter->m_uStockHolderId, saleEntrustIter->m_eDirection });
				++saleEntrustIter;
			}
			else if (buyEntrustIter->m_uAmount - buyEntrustIter->m_uDealAmount < saleEntrustIter->m_uAmount - saleEntrustIter->m_uDealAmount)
			{
				uDealAmount = buyEntrustIter->m_uAmount - buyEntrustIter->m_uDealAmount;
				uDealPrice = saleEntrustIter->m_uPrice;
				buyEntrustIter->m_uDealAmount += uDealAmount;
				saleEntrustIter->m_uDealAmount += uDealAmount;
				deals.push_back(Deal{ 0, buyEntrustIter->m_uDealAmount, buyEntrustIter->m_uStockHolderId, buyEntrustIter->m_eDirection });
				++buyEntrustIter;
			}
			else
			{
				uDealAmount = buyEntrustIter->m_uAmount - buyEntrustIter->m_uDealAmount;
				uDealPrice = buyEntrustIter->m_uPrice;
				buyEntrustIter->m_uDealAmount += uDealAmount;
				saleEntrustIter->m_uDealAmount += uDealAmount;
				deals.push_back(Deal{ 0, buyEntrustIter->m_uDealAmount, buyEntrustIter->m_uStockHolderId, buyEntrustIter->m_eDirection });
				deals.push_back(Deal{ 0, saleEntrustIter->m_uDealAmount, saleEntrustIter->m_uStockHolderId, saleEntrustIter->m_eDirection });
				++saleEntrustIter;
				++buyEntrustIter;
			}
			uTotalDealAmount += uDealAmount;
		}

		if (buyEntrustIter != m_buyEntrusts.rend()
			&& buyEntrustIter->m_uDealAmount > 0)
		{
			deals.push_back(Deal{ 0, buyEntrustIter->m_uDealAmount, buyEntrustIter->m_uStockHolderId, buyEntrustIter->m_eDirection });
		}
		if (saleEntrustIter != m_saleEntrusts.end()
			&& saleEntrustIter->m_uDealAmount > 0)
		{
			deals.push_back(Deal{ 0, saleEntrustIter->m_uDealAmount, saleEntrustIter->m_uStockHolderId, saleEntrustIter->m_eDirection });
		}
	}

	if (!deals.empty())
	{
		for (auto& deal : deals)
		{
			deal.m_uPrice = uDealPrice;

			StockClear::GetInstance().OnDeal(deal.m_uStockHolderId, deal.m_uAmount, deal.m_uPrice, deal.m_eDirection, uTime);
		}
		m_stock.m_stockQuotations.push_back(Stock::StockQuotation{ uDealPrice, uTotalDealAmount });
		m_stock.m_uLastPrice = uDealPrice;

	}
	else
	{
		m_stock.m_stockQuotations.push_back(Stock::StockQuotation{ m_stock.m_uLastPrice, 0 });
	}

	m_buyEntrusts.clear();
	m_saleEntrusts.clear();
}
