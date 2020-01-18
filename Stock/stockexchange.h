#pragma once
#include <list>
#include <cstdint>
#include "stock.h"
#include "entrust.h"


class StockHolder;

class Entrust
{
public:
    uint8_t m_uPrice;
    uint64_t m_uAmount;
    uint64_t m_uTimeStamp;
    StockHolder* m_pStockHolder;
};

class Deal
{
public:
    uint8_t m_uPrice;
    uint64_t m_uAmount;
    StockHolder* m_pStockHolder;
};

class StockExchange
{
private:
    static StockExchange m_instance;
    Stock m_stock;
    std::list<Entrust> m_buyEntrusts;
    std::list<Entrust> m_saleEntrusts;
private:
    StockExchange();
    ~StockExchange();
public:
    StockExchange& GetInstance();
    void BuyEntrust(const Entrust& buyEntrust);
    void SaleEntrust(const Entrust& saleEntrust);
    void OnTime(uint64_t uTime);
};