// FactoryMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum class Storage { mysql, postgres };

struct IStorage
{
    virtual ~IStorage() = default;

    virtual void Open() = 0;
    virtual void ExecuteQuery() = 0;
    virtual void Close() = 0;
};

class MysqlStorage : public IStorage {
    void Open() override
    {
        std::cout << "connect to mysql" << std::endl;
    }

    void ExecuteQuery() override
    {
        std::cout << "fetch mysql result" << std::endl;
    }

    void Close() override
    {
        std::cout << "disconnect from mysql" << std::endl;
    }
};

class PosrgressStorage : public IStorage {
    void Open() override
    {
        std::cout << "connect to pg" << std::endl;
    }

    void ExecuteQuery() override
    {
        std::cout << "fetch pg result" << std::endl;
    }

    void Close() override
    {
        std::cout << "disconnect from pg" << std::endl;
    }
};

int main(int argc, char * argv[] )
{
    //auto enviroment = argc ? Storage::mysql : S
    IStorage* pStorage = nullptr;
    switch (static_cast<Storage>(argc))
    {
    case Storage::mysql:
        pStorage = new MysqlStorage();
        break;    
    case Storage::postgres:
        pStorage = new PosrgressStorage();

        break;
    default:
        std::cout << "Don't choise storage\n";
        return 0;
        break;
    }

    pStorage->Open();
    pStorage->ExecuteQuery();
    pStorage->Close();

    return 0;
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
