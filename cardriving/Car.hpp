#pragma once
class Car
{
private:
	int locX, locY;
	int fuel;
public:
	Car();
	~Car();
	void setLocX(const int& x);
	void setLocY(const int& y);
	int getLocX();
	int getLocY();
};

