#pragma once

#include <iostream>

using namespace std;

class Shape
{
public:
	int edge_length;
	virtual int circumference()
	{
		std::cout << "Circumference of Base Class \n";
		return 0;
	}
};

class Triangle : public Shape
{
public:
	int circumference()
	{
		std::cout << "Circumference of Triangle Class \n";
		return 3 * edge_length;
	}
};