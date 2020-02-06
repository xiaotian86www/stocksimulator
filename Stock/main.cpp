// Stock.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <string>
#include <iostream>
#include "stockholder.h"
#include "stockexchange.h"
#include <fstream>

int main()
{
    const size_t uStockHolderSize = 1000;
    StockHolder* stockHolders[uStockHolderSize];

    for (size_t i = 0; i < uStockHolderSize; ++i)
    {
        if (i < 250)
        {
            stockHolders[i] = new StockHolder(127, 127, new BSStrategy());
        }
        else if (i < 500)
        {
            stockHolders[i] = new StockHolder(63, 63, new BSStrategy());
        }
        else if (i < 750)
        {
            stockHolders[i] = new StockHolder(31, 31, new BSStrategy());
        }
        else
        {
            stockHolders[i] = new StockHolder(31, 31, new NStrategy());
        }
        //stockHolders[i] = new StockHolder(127, 127, new BBStrategy());
    }

    uint64_t uMaxTime = 3000;
    for (uint64_t uTime = 1; uTime <= uMaxTime; ++uTime)
    {
        for (size_t i = 0; i < uStockHolderSize; ++i)
        {
            stockHolders[i]->OnTime(uTime);
        }
        StockExchange::GetInstance().OnTime(uTime);
        uint64_t uTotalBalance = 0;
        //for (size_t i = 0; i < uStockHolderSize; ++i)
        //{
        //    uTotalBalance+= 
        //}
    }
    std::fstream fs_hq("hq.csv", std::ios::out);

    fs_hq << "时间,价格,数量" << std::endl;    

    for (size_t i = 0; i < StockExchange::GetInstance().m_stock.m_stockQuotations.size(); i++)
    {
        fs_hq << i << "," << 
            StockExchange::GetInstance().m_stock.m_stockQuotations[i].m_uPrice << "," << 
            StockExchange::GetInstance().m_stock.m_stockQuotations[i].m_uAmount << std::endl;
    }

    fs_hq.close();


    for (size_t i = 1; i <= uStockHolderSize; ++i)
    {
        std::string sFilePath = "positions\\" + std::to_string(i) + ".csv";
        std::fstream fs_ps(sFilePath, std::ios::out);
        fs_ps << "时间,市值,资金,持仓" << std::endl;
        const std::list<Position> positions = StockClear::GetInstance().GetPosition(i);
        uint64_t uTime = 0;
        uint64_t uBalance = 0;
        uint64_t uAmount = 0;
        for (const Position& position : positions)
        {
            while (uTime < position.m_uTime)
            {
                fs_ps << uTime << "," << uAmount * StockExchange::GetInstance().m_stock.m_stockQuotations[uTime].m_uPrice + uBalance
                    << "," << uBalance << "," << uAmount << std::endl;
                ++uTime;
            }
            uBalance = position.m_uBalance;
            uAmount = position.m_uAmount;
            fs_ps << uTime << "," << uAmount * StockExchange::GetInstance().m_stock.m_stockQuotations[uTime].m_uPrice + uBalance
                << "," << uBalance << "," << uAmount << std::endl;
            ++uTime;
        }
        while (uTime <= uMaxTime)
        {
            fs_ps << uTime << "," << uAmount * StockExchange::GetInstance().m_stock.m_stockQuotations[uTime].m_uPrice + uBalance
                << "," << uBalance << "," << uAmount << std::endl;
            ++uTime;
        }
        fs_ps.close();
    }

    std::fstream fs_ps("ps.csv", std::ios::out);

    fs_ps << "股东序号,市值,资金,持仓" << std::endl;

    for (size_t i = 1; i <= uStockHolderSize; ++i)
    {
        const Position& position = StockClear::GetInstance().GetPosition(i).back();
        fs_ps <<  i << "," << position.m_uAmount * StockExchange::GetInstance().m_stock.m_uLastPrice + position.m_uBalance
            << "," << position.m_uBalance << "," << position.m_uAmount << std::endl;
    }

    fs_ps.close();
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