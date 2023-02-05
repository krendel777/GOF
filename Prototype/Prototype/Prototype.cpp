// Prototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

struct IConnector
{
    virtual ~IConnector() = default;
    virtual void Connect() = 0;
    virtual std::shared_ptr<IConnector> Clone() = 0; //Prototype
};

struct TCPConnector : public IConnector
{
    void Connect()
    {
        std::cout << "TCP connection \n";
    }

    std::shared_ptr<IConnector> Clone() override //Prototype
    {
        return std::make_shared<TCPConnector>();
    }
};

struct UDPConnector : public IConnector
{
    void Connect() override
    {
        std::cout << "UDP connection \n";
    }

    std::shared_ptr<IConnector> Clone() override //Prototype
    {
        return std::make_shared<UDPConnector>();
    }
};

int main()
{
    std::cout << "Primary\n";
    auto connection = std::make_shared<TCPConnector>(); //We could use "factory" to create connection, but it is excample about "Prototype" only
    connection->Connect();

    std::cout << "Mirror\n";
    auto theSameTypeOfConnection = connection->Clone();
    theSameTypeOfConnection->Connect();
}