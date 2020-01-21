#include <iostream>
#include "stock.h"

Stock::Stock()
    : m_uAmount(0)
    , m_uLastPrice(9)
{
    m_stockQuotations.push_back(StockQuotation{ m_uLastPrice, m_uAmount });
}
