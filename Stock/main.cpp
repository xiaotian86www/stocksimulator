// Stock.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "stockholder.h"
#include "stockexchange.h"
#include <fstream>

int main()
{
    const size_t uStockHolderSize = 1000;
    StockHolder stockHolders[uStockHolderSize];

    uint64_t uTime = 1000;
    while (--uTime)
    {
        for (size_t i = 0; i < uStockHolderSize; ++i)
        {
            stockHolders[i].OnTime();
        }
        StockExchange::GetInstance().OnTime();
        uint64_t uTotalBalance = 0;
        //for (size_t i = 0; i < uStockHolderSize; ++i)
        //{
        //    uTotalBalance+= 
        //}
    }
    std::fstream fs("hq.csv", std::ios::out);

    fs << "时间,价格,数量" << std::endl;    

    for (size_t i = 0; i < StockExchange::GetInstance().m_stock.m_stockQuotations.size(); i++)
    {
        fs << i << "," << 
            StockExchange::GetInstance().m_stock.m_stockQuotations[i].m_uPrice << "," << 
            StockExchange::GetInstance().m_stock.m_stockQuotations[i].m_uAmount << std::endl;
    }

    //StockExchange::GetInstance().m_stock.Print();

    //for (size_t i = 0; i < uStockHolderSize; ++i)
    //{
    //    const Position& position = StockClear::GetInstance().GetPosition(i + 1);
    //    std::cout << "股东序号:" << i + 1 << "市值:" << (position.m_uAmount * StockExchange::GetInstance().m_stock.m_uLastPrice + position.m_uBalance) << std::endl;
    //}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件