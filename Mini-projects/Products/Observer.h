#pragma once

#include <vector>
#include <algorithm>

using std::vector;
using std::remove;

class Observer
{
public:
	Observer() = default;

	virtual void update() = 0;

	virtual ~Observer() = default;
};

class Observable {
private:
	vector<Observer*> observers;

public:
	Observable() = default;

	void notify() {
		for (auto obs : observers)
			obs->update();
	}

	void attachObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void detachObserver(Observer* obs) {
		observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
	}

	virtual ~Observable() = default;
};

