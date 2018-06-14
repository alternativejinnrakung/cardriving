#pragma once
#include "Car.hpp"

template<class T>
class SpawnPoint {
	T cars;
public:
	SpawnPoint(T input_cars) {
		cars = input_cars;
	}
	T getCar();
	void addCar();
};

template<class T>
T SpawnPoint<T>::getCar() {
	return cars;
}

template<class T>
void SpawnPoint<T>::addCar() {
	cars.push_back(make_shared<Car>());
}

class Spawner
{
public:
	Spawner();
	virtual ~Spawner();
	virtual Car *car() = 0;
};

