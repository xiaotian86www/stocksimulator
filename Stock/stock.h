#pragma once
#include <cstdint>
#include <vector>

class Stock
{
public:
    struct StockQuotation
    {
        uint64_t m_uPrice;
        uint64_t m_uAmount;
    };
public:
    std::vector<StockQuotation> m_stockQuotations;
    uint64_t m_uAmount;
    uint64_t m_uLastPrice;
    Stock();
    void Print();
};