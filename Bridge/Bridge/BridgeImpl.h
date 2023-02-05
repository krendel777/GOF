#include <iostream>
#include <memory>

#pragma once

struct ClockSignal
{
	virtual ~ClockSignal() = default;
	virtual void now() = 0;
};

struct InternetClockSignal : public ClockSignal
{
	void now() override
	{
		std::cout << "internet clock\n";
	}
};

struct LocalClockSignal : public ClockSignal
{
	void now() override
	{
		std::cout << "local clock\n";
	}
};

struct ClockType
{
	virtual ~ClockType() = default;
	virtual void display() = 0;
};

struct DigitalClock : public ClockType
{
	void display() override
	{
		std::cout << "digital type \n";
	}
};

struct AnalogClock : public ClockType
{
	void display() override
	{
		std::cout << "analog type \n";
	}
};

struct Clock
{
	Clock(std::shared_ptr<ClockSignal> sig, std::shared_ptr<ClockType> t)
	{
		signal = sig;
		type = t;
	}

	std::shared_ptr<ClockSignal> signal;
	std::shared_ptr<ClockType> type;

	virtual ~Clock() = default;

	void refresh()
	{
		if(signal)
			signal->now();
	}

	void display()
	{
		if(type)
			type->display();
	}
};
