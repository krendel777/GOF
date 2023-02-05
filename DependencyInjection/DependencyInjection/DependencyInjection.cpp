
#include <iostream>
#include <memory>

struct IStorage
{
    virtual ~IStorage() = default;
    virtual void ExecuteQuery() = 0;
};

class Report
{
public:
    Report(std::shared_ptr<IStorage> storage) :
        m_storage(storage)
    {}
    void Print()
    {
        if (m_storage != nullptr)
        {
            m_storage->ExecuteQuery();
            std::cout << "Print done\n";
        }
        else
            std::cout << "Member is not initialisation\n";
    }
private:
    std::shared_ptr<IStorage> m_storage;
};

struct TestStorage : public IStorage
{
    void ExecuteQuery() override
    {
        std::cout << "... fetching data" << std::endl;
    }
};

int main()
{
    auto storage = std::make_shared<TestStorage>();
    Report report(nullptr);
    report.Print();
}