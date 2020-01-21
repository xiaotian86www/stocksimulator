#include "strategy.h"
#include "stockexchange.h"

void BBStrategy::operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention)
{
    Stock& stock = StockExchange::GetInstance().m_stock;
    uint8_t uTime = stock.m_stockQuotations.size();
    if (uTime < 2) return;
    if (stock.m_stockQuotations[uTime - 1].m_uPrice > stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uBuyIntention + 8 < 255)
        {
            uBuyIntention += 8;
        }
        if (uSaleIntention - 8 >= 0)
        {
            uSaleIntention -= 8;
        }
    }
    else if (stock.m_stockQuotations[uTime - 1].m_uPrice < stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uSaleIntention + 8 < 255)
        {
            uSaleIntention += 8;
        }
        if (uBuyIntention - 8 >= 0)
        {
            uBuyIntention -= 8;
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
        if (uSaleIntention + 8 < 255)
        {
            uSaleIntention += 8;
        }
        if (uBuyIntention - 8 >= 0)
        {
            uBuyIntention -= 8;
        }
    }
    else if (stock.m_stockQuotations[uTime - 1].m_uPrice < stock.m_stockQuotations[uTime - 2].m_uPrice)
    {
        if (uBuyIntention + 8 < 255)
        {
            uBuyIntention += 8;
        }
        if (uSaleIntention - 8 >= 0)
        {
            uSaleIntention -= 8;
        }
    }
}

void NStrategy::operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention)
{

}
