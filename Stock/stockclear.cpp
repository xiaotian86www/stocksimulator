#include "stockclear.h"
#include "stockexchange.h"

StockClear StockClear::m_instance;

const static uint64_t uFee = 0;

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

void StockClear::OnDeal(uint64_t uStockHolderId, uint64_t uAmount, uint64_t uPrice, Direction eDirection, uint64_t uTime)
{
    Position lastPosition = m_uPositions[uStockHolderId].back();
    lastPosition.m_uTime = uTime;
    if (eDirection == Direction::BUY)
    {
        lastPosition.m_uAmount += uAmount;
        lastPosition.m_uBalance -= uAmount * uPrice + uFee;
    }
    else
    {
        lastPosition.m_uAmount -= uAmount;
        lastPosition.m_uBalance += uAmount * uPrice;
    }
    m_uPositions[uStockHolderId].push_back(lastPosition);
}

const std::list<Position>& StockClear::GetPosition(uint64_t uStockHolderId) const
{
    return m_uPositions.at(uStockHolderId);
}

void StockClear::AddPosition(uint64_t uStockHolderId, uint64_t uAmount, uint64_t uBalance)
{
    m_uPositions[uStockHolderId].push_back(Position{ 0, uAmount, uBalance });
}

uint64_t StockClear::CalcAmount(uint64_t uBalance, uint64_t uPrice)
{
    if (uBalance > uFee)
        return (uBalance - uFee) / uPrice;
    else
        return 0;
}
