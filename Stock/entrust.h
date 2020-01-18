#pragma once

class StockHolder;

class Entrust
{
public:
    uint8_t m_uPrice;
    uint64_t m_uAmount;
    uint64_t m_uTimeStamp;
    StockHolder* m_pStockHolder;
};