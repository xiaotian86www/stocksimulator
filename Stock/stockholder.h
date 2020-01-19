#pragma once
#include <cstdint>
#include <random>
#include "stock.h"
#include "stockclear.h"
#include "stockexchange.h"

class StockHolder
{
private:
    uint8_t m_uBuyIntention;
    uint8_t m_uSaleIntention;
    static std::default_random_engine m_randomEngine;
public:
    uint64_t m_uId;
public:
    StockHolder();
    void OnTime();
};
