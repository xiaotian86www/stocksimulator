// Stock.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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

    fs_hq << "ʱ��,�۸�,����" << std::endl;    

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
        fs_ps << "ʱ��,��ֵ,�ʽ�,�ֲ�" << std::endl;
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

    fs_ps << "�ɶ����,��ֵ,�ʽ�,�ֲ�" << std::endl;

    for (size_t i = 1; i <= uStockHolderSize; ++i)
    {
        const Position& position = StockClear::GetInstance().GetPosition(i).back();
        fs_ps <<  i << "," << position.m_uAmount * StockExchange::GetInstance().m_stock.m_uLastPrice + position.m_uBalance
            << "," << position.m_uBalance << "," << position.m_uAmount << std::endl;
    }

    fs_ps.close();
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�