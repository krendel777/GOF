// Builder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <cassert>

class Tariff {
    const std::vector<double> m_amount;
    const std::vector<int> m_discount;

public:
    Tariff(std::vector<double> amount, std::vector<int> discount)
        : m_amount(std::move(amount)), m_discount(std::move(discount))
    {
        static int copy = 0;
        std::cout << "copy n : " << ++copy << std::endl;

        assert(m_amount.size() == m_discount.size());
        //amount has to sort order by asc
        //amount values have to be unique
        //amount[i] corresponds discount[i]
    }

    void Apply();
};


class TariffBuilder
{
    std::map<double, int> m_tariff;

public:
    void AddDiscount(double subtotal, int discount)
    {
        m_tariff[subtotal] = discount;
    }

    Tariff Build()
    {
        int countValues = m_tariff.size();
        std::vector<double> amounts;
        std::vector<int> discounts;
        amounts.reserve(countValues);
        discounts.reserve(countValues);
        for (const auto& tariff : m_tariff)
        {
            amounts.push_back(tariff.first);
            discounts.push_back(tariff.second);
        }

        return Tariff(amounts, discounts);
    }
};

void Tariff::Apply()
{
    std::cout << "tariff is :" << std::endl;
    for (size_t i = 0; i < m_amount.size(); ++i)
    {
        std::cout << "after " << m_amount[i] << " RUB apply " << m_discount[i] << std::endl;
    }
}
int main()
{
    auto builder = TariffBuilder();
    builder.AddDiscount(1000.0, 10);
    builder.AddDiscount(25000.0, 25);
    builder.AddDiscount(15000.0, 15);

    auto t = builder.Build();

    t.Apply();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
