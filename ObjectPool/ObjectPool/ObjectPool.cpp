// ObjectPool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

class PgConnection { };

class PgConnectionPool {
public:
    ~PgConnectionPool()
    {
        for (const auto& object : pool)
        {
            std::cout << object.connection << std::endl;
        }
    }

    PgConnection* Get() 
    {
        for (auto& object : pool)
        {
            if (!object.busy)
            {
                object.busy = true;
                return object.connection;
            }
        }

        auto block = PgConnectionBlock{ new PgConnection(), true };
        pool.push_back(block);

        return block.connection;
    }

    void Put(PgConnection* connection)
    {
        for (auto& object : pool)
        {
            if (connection == object.connection)
            {
                object.busy = false;
                break;
            }
        }
    }

private:
    struct PgConnectionBlock {
        PgConnection* connection;
        bool busy;
    };

    std::vector<PgConnectionBlock> pool;
};

int main()
{
    PgConnectionPool pool;
    auto report_conn = pool.Get();
    pool.Put(report_conn);    
    
    auto admin_conn = pool.Get();
    pool.Put(admin_conn);

    return 0;
}
