#pragma once
#include <cstdint>
#include <unordered_map>

class Deal;

class Position
{
public:
    uint64_t m_uId;
    uint64_t m_uAmount;
    uint64_t m_uBalance;
};

class StockClear
{
private:
    static StockClear m_instance;
    std::unordered_map<uint64_t, Position> m_uPositions;
    StockClear();
    ~StockClear();
public:
    static StockClear& GetInstance();
    void OnDeal(const Deal& deal);
    const Position& GetPosition(uint64_t uStockHolderId) const;
    void AddPosition(const Position& position);
    uint64_t CalcAmount(uint64_t uBalance, uint64_t uPrice);
};