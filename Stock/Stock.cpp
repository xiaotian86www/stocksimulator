#include <iostream>
#include "stock.h"

Stock::Stock()
    : m_uAmount(0)
    , m_uLastPrice(10)
{
}

void Stock::Print()
{
    for (size_t i = 0; i < m_stockQuotations.size(); i++)
    {
        std::cout << i << ":成交价格:" << m_stockQuotations[i].m_uPrice << "成交数量:" << m_stockQuotations[i].m_uAmount << std::endl;
    }
}
