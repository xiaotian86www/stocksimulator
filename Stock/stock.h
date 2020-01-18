#pragma once
#include <cstdint>
#include <list>

class Stock
{
public:
    struct StockQuotation
    {
        uint8_t m_uPrice;
        uint64_t m_uAmount;
    };
public:
    std::list<StockQuotation> m_stockQuotations;
    uint64_t m_uAmount;
};