#pragma once
#include <cstdint>

class Strategy
{
public:
    virtual void operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention) = 0;
};

class NStrategy : public Strategy
{
public:
    virtual void operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention);
};

class BBStrategy : public Strategy
{
public:
    virtual void operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention);
};

class BSStrategy : public Strategy
{
public:
    virtual void operator()(uint8_t& uBuyIntention, uint8_t& uSaleIntention);
};