#pragma once
#include <cstdint>
#include <unordered_map>

class Position
{
public:
    uint64_t m_uId;
    uint64_t m_uAmount;
    uint64_t m_uPrice;
};

class StockClear
{
private:
    static StockClear m_instance;
    StockClear();
    ~StockClear();
public:
    static StockClear& GetInstance();
    std::unordered_map<uint64_t, Position> m_uPositions;
};