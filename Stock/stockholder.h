#pragma once
#include <cstdint>
#include "stock.h"
#include "stockclear.h"
#include "stockexchange.h"

class StockHolder
{
private:
    uint8_t m_uBuyIntention;
    uint8_t m_uSaleIntention;
public:
    uint64_t m_uId;
public:
    StockHolder(uint8_t uBuyIntention, uint8_t uSaleIntention);
    void OnTime(uint64_t uTime);
    static void OnDeal(const Deal& deal);
};
