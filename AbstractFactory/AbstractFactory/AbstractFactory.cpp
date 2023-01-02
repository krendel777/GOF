// AbstractFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

enum class Env {
    cloud, local
};

// Config

struct IConfig {
    virtual ~IConfig() = default;

    virtual void Read() = 0;
};

class ConsulConfig : public IConfig {
    void Read() override
    {
        std::cout << "connect to consul" << std::endl;
    }
};

class LocalConfig : public IConfig {
    void Read() override
    {
        std::cout << "open local file" << std::endl;
    }
};

// Metric

struct IMetric {
    virtual ~IMetric() = default;

    virtual void Send() = 0;
};

struct PrometheusMetric : public IMetric {
    void Send() override
    {
        std::cout << "push to prometheus" << std::endl;
    }
};

struct LocalMetric : public IMetric {
    void Send() override
    {
        std::cout << "write to log" << std::endl;
    }
};


struct EnvironmentFactory {
    virtual ~EnvironmentFactory() = default;

    virtual std::unique_ptr<IConfig> CreateConfig() = 0;
    virtual std::unique_ptr<IMetric> CreateMetric() = 0;
};

struct CloudFactory : public EnvironmentFactory {
    std::unique_ptr<IConfig> CreateConfig() override
    {
        return std::make_unique<ConsulConfig>();
    }    
    
    std::unique_ptr<IMetric> CreateMetric() override
    {
        return std::make_unique<PrometheusMetric>();
    }
};

struct LocalFactory : public EnvironmentFactory {
    std::unique_ptr<IConfig> CreateConfig() override
    {
        return std::make_unique<LocalConfig>();
    }    
    
    std::unique_ptr<IMetric> CreateMetric() override
    {
        return std::make_unique<LocalMetric>();
    }
};

int main(int argc, char* argv[])
{
    auto environment = argc ? Env::cloud : Env::local;

    std::unique_ptr<EnvironmentFactory> factory = nullptr;
    switch (environment)
    {
    case Env::cloud:
        factory = std::make_unique<CloudFactory>();
        break;
    case Env::local:
        factory = std::make_unique<LocalFactory>();
        break;
    default:
        break;
    }

    auto config = factory->CreateConfig();
    auto metric = factory->CreateMetric();

    config->Read();
    metric->Send();
    std::unique_ptr<IMetric> temp = std::move(metric);
    std::cout << std::hex << metric << std::endl;
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
