#include <iostream>

#pragma once

struct mysql_client_native {
	void mysql_connect()
	{
		std::cout << "mysql connect\n";
	}	
		
	void mysql_execute()
	{
		std::cout << "mysql execute\n";
	}	
	
	void mysql_close()
	{
		std::cout << "mysql close\n";
	}
};

struct postgres_client_native {
	void postgres_open()
	{
		std::cout << "postgres open\n";
	}

	void postgres_query()
	{
		std::cout << "postgres query\n";
	}
};

struct IDatabase {
	virtual ~IDatabase() = default;

	virtual void connect() = 0;
	virtual void execute_query() = 0;
	virtual void close() = 0;
};

struct MysqlDatabase : public IDatabase
{
	mysql_client_native client;

	void connect() override
	{
		client.mysql_connect();
	}	
	
	void execute_query() override
	{
		client.mysql_execute();
	}	
	
	void close() override
	{
		client.mysql_execute();
	}
};

struct PostgresDatabase : public IDatabase
{
	postgres_client_native client;

	void connect() override
	{
		client.postgres_open();
	}	
	
	void execute_query() override
	{
		client.postgres_query();
	}	
	
	void close() override
	{
		//client.mysql_execute();
	}
};