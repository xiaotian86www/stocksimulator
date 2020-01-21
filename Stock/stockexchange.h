#pragma once
#include <list>
#include <cstdint>
#include "stock.h"


class StockHolder;

enum class Direction
{
    BUY = 1,
    SALE = 2
};

class Entrust
{
public:
    uint64_t m_uPrice;
    uint64_t m_uAmount;
    uint64_t m_uDealAmount;
    uint64_t m_uTimeStamp;
    uint64_t m_uStockHolderId;
    Direction m_eDirection;
public:
    bool operator<(const Entrust& entrust);
};

class Deal
{
public:
    uint64_t m_uPrice;
    uint64_t m_uAmount;
    uint64_t m_uStockHolderId;
    Direction m_eDirection;
};

class StockExchange
{
public:
    Stock m_stock;
private:
    static StockExchange m_instance;
    std::list<Entrust> m_buyEntrusts;
    std::list<Entrust> m_saleEntrusts;
private:
    StockExchange();
    ~StockExchange();
public:
    static StockExchange& GetInstance();
    void OnEntrust(uint64_t uStockHolderId, uint64_t uAmount, uint64_t uPrice, Direction eDirection, uint64_t uTimeStamp);
    void OnTime(uint64_t uTime);
};