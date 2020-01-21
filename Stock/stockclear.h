#pragma once
#include <cstdint>
#include <unordered_map>
#include "stockexchange.h"

class Deal;

class Position
{
public:
    uint64_t m_uTime;
    uint64_t m_uAmount;
    uint64_t m_uBalance;
};

class StockClear
{
private:
    static StockClear m_instance;
    std::unordered_map<uint64_t, std::list<Position>> m_uPositions;
    StockClear();
    ~StockClear();
public:
    static StockClear& GetInstance();
    void OnDeal(uint64_t uStockHolderId, uint64_t uAmount, uint64_t uPrice, Direction eDirection, uint64_t uTime);
    const std::list<Position>& GetPosition(uint64_t uStockHolderId) const;
    void AddPosition(uint64_t uStockHolderId, uint64_t uAmount, uint64_t uBalance);
    uint64_t CalcAmount(uint64_t uBalance, uint64_t uPrice);
};