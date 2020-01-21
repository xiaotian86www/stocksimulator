#include <ctime>
#include <climits>
#include "stockholder.h"

static uint64_t uStockHolderCount = 0;
std::default_random_engine StockHolder::m_randomEngine(time(nullptr));


StockHolder::StockHolder(uint8_t uBuyIntention, uint8_t uSaleIntention, Strategy* pStrategy)
    : m_uBuyIntention(uBuyIntention)
    , m_uSaleIntention(uSaleIntention)
    , m_pStrategy(pStrategy)
    , m_uId(++uStockHolderCount)
{
    StockClear::GetInstance().AddPosition(m_uId, 1000, 100000);
}

void StockHolder::OnTime(uint64_t uTime)
{
    (*m_pStrategy)(m_uBuyIntention, m_uSaleIntention);

    std::uniform_int_distribution<uint16_t> intentionRandom(0, 255);
    uint8_t uIntention = (uint8_t)intentionRandom(m_randomEngine);
    if (uIntention < m_uBuyIntention)
    {
        std::poisson_distribution<uint64_t> priceRandom(StockExchange::GetInstance().m_stock.m_uLastPrice);
        uint64_t uPrice = priceRandom(m_randomEngine);
        if (uPrice > 0)
        {
            uint64_t uAmount = StockClear::GetInstance().CalcAmount(StockClear::GetInstance().GetPosition(m_uId).back().m_uBalance, uPrice);
            if (uAmount > 0)
            {
                std::uniform_int_distribution<uint64_t> timeStampRandom;
                uint64_t uTimeStamp = timeStampRandom(m_randomEngine);
                StockExchange::GetInstance().OnEntrust(m_uId, uAmount, uPrice, Direction::BUY, uTimeStamp);
            }
        }
    }
    else if ((255 - uIntention) < m_uSaleIntention)
    {
        std::poisson_distribution<uint64_t> priceRandom(StockExchange::GetInstance().m_stock.m_uLastPrice);
        uint64_t uPrice = priceRandom(m_randomEngine);
        if (uPrice > 0)
        {
            uint64_t uAmount = StockClear::GetInstance().GetPosition(m_uId).back().m_uAmount;
            if (uAmount > 0)
            {
                std::uniform_int_distribution<uint64_t> timeStampRandom;
                uint64_t uTimeStamp = timeStampRandom(m_randomEngine);
                StockExchange::GetInstance().OnEntrust(m_uId, uAmount, uPrice, Direction::SALE, uTimeStamp);
            }
        }
    }
}