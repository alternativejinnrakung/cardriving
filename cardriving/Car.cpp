#include "Car.hpp"



Car::Car()
{
}


Car::~Car()
{
}

void Car::setLocX(const int& x) {
	locX = x;
}

void Car::setLocY(const int& y) {
	locY = y;
}

int Car::getLocX() {
	return locX;
}

int Car::getLocY() {
	return locY;
}
