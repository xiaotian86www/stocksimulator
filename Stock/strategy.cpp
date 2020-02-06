#include "strategy.h"
#include "stockexchange.h"

void BBStrategy::operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention)
{
    Stock& stock = StockExchange::GetInstance().m_stock;
    uint8_t uTime = stock.m_stockQuotations.size();
    if (uTime < 2) return;
    if (stock.m_stockQuotations[uTime - 1].m_uPrice > stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uSaleIntention > 0)
        {
            uint8_t uDeltaIntention = (stock.m_stockQuotations[uTime - 1].m_uPrice - stock.m_stockQuotations[uTime - 2].m_uPrice) * uSaleIntention / stock.m_stockQuotations[uTime - 2].m_uPrice;
            uSaleIntention -= uDeltaIntention;
            uBuyIntention += uDeltaIntention;
        }
    }
    else if (stock.m_stockQuotations[uTime - 1].m_uPrice < stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uBuyIntention > 0)
        {
            uint8_t uDeltaIntention = (stock.m_stockQuotations[uTime - 2].m_uPrice - stock.m_stockQuotations[uTime - 1].m_uPrice) * uBuyIntention / stock.m_stockQuotations[uTime - 2].m_uPrice;
            uSaleIntention += uDeltaIntention;
            uBuyIntention -= uDeltaIntention;
        }
    }
}

void BSStrategy::operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention)
{
    Stock& stock = StockExchange::GetInstance().m_stock;
    uint8_t uTime = stock.m_stockQuotations.size();
    if (uTime < 2) return;
    if (stock.m_stockQuotations[uTime - 1].m_uPrice > stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uBuyIntention > 0)
        {
            uint8_t uDeltaIntention = (stock.m_stockQuotations[uTime - 1].m_uPrice - stock.m_stockQuotations[uTime - 2].m_uPrice) * uBuyIntention / stock.m_stockQuotations[uTime - 2].m_uPrice;
            uSaleIntention += uDeltaIntention;
            uBuyIntention -= uDeltaIntention;
        }
    }
    else if (stock.m_stockQuotations[uTime - 1].m_uPrice < stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uSaleIntention > 0)
        {
            uint8_t uDeltaIntention = (stock.m_stockQuotations[uTime - 2].m_uPrice - stock.m_stockQuotations[uTime - 1].m_uPrice) * uSaleIntention / stock.m_stockQuotations[uTime - 2].m_uPrice;
            uSaleIntention -= uDeltaIntention;
            uBuyIntention += uDeltaIntention;
        }
    }
}

void NStrategy::operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention)
{

}
