#include "stockholder.h"

static uint64_t uStockHolderCount = 0;


StockHolder::StockHolder(uint8_t uBuyIntention, uint8_t uSaleIntention)
    : m_uBuyIntention(uBuyIntention)
    , m_uSaleIntention(uSaleIntention)
    , m_uId(++uStockHolderCount)
{

}

void StockHolder::OnTime(uint64_t uTime)
{

}