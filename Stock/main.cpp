// Stock.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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

    fs << "ʱ��,�۸�,����" << std::endl;    

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
    //    std::cout << "�ɶ����:" << i + 1 << "��ֵ:" << (position.m_uAmount * StockExchange::GetInstance().m_stock.m_uLastPrice + position.m_uBalance) << std::endl;
    //}
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