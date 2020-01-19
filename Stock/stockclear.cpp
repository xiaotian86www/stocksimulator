#include "stockclear.h"
#include "stockexchange.h"

StockClear StockClear::m_instance;

const static uint64_t uFee = 1;

StockClear::StockClear()
{

}

StockClear::~StockClear()
{

}

StockClear& StockClear::GetInstance()
{
    return StockClear::m_instance;
}

void StockClear::OnDeal(const Deal& deal)
{
    if (deal.m_eDirection == Direction::BUY)
    {
        m_uPositions[deal.m_uStockHolderId].m_uAmount += deal.m_uAmount;
        m_uPositions[deal.m_uStockHolderId].m_uBalance -= deal.m_uAmount * deal.m_uPrice + uFee;
    }
    else
    {
        m_uPositions[deal.m_uStockHolderId].m_uAmount -= deal.m_uAmount;
        m_uPositions[deal.m_uStockHolderId].m_uBalance += deal.m_uAmount * deal.m_uPrice - uFee;
    }
}

const Position& StockClear::GetPosition(uint64_t uStockHolderId) const
{
    return m_uPositions.at(uStockHolderId);
}

void StockClear::AddPosition(const Position& position)
{
    m_uPositions[position.m_uId] = position;
}

uint64_t StockClear::CalcAmount(uint64_t uBalance, uint64_t uPrice)
{
    return (uBalance - uFee) / uPrice;
}
