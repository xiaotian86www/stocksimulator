#pragma once
#include <cstdint>
#include <random>
#include "stock.h"
#include "stockclear.h"
#include "stockexchange.h"
#include "strategy.h"

class StockHolder
{
private:
    uint8_t m_uBuyIntention;
    uint8_t m_uSaleIntention;
    Strategy* m_pStrategy;
    static std::default_random_engine m_randomEngine;
public:
    uint64_t m_uId;
public:
    StockHolder(uint8_t uBuyIntention, uint8_t uSaleIntention, Strategy* pStrategy);
    void OnTime(uint64_t uTime);
};
