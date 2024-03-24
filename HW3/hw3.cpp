////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 3: Source file
// 1. Complete the implementation of Ordered
// 2. Add a new class, OrderedSet, using class inheritance
////////////////////////////////////////////////////////////////////////////////
#include "hw3.h"

#include <iostream>
#include <limits>

Ordered::Ordered() {
	m_size = 0;
	int *Oarr = new int[1000]{ 0 };
}

Ordered::~Ordered() {
	delete[] Oarr;
}

void Ordered::add(int v) {
	Oarr[m_size] = v;
	for (int i = m_size; i > 0; i--) {
		if (Oarr[i] < Oarr[i - 1]) {
			int saver = Oarr[i];
			Oarr[i] = Oarr[i - 1];
			Oarr[i - 1] = saver;
		}
	}
	m_size += 1;
}

void Ordered::remove(int index) {
	for (int i = index; i < m_size - 1; i++) {
		Oarr[i] = Oarr[i + 1];
	}
	m_size -= 1;
}

void Ordered::add(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		this->add(arr[i]);
	}
}

int Ordered::operator[](int index) {
	return Oarr[index];
}

bool Ordered::operator>>(int v) {
	for(int i = 0; i < m_size; i++) {
		if (Oarr[i] == v) {
			return true;
		}
	}
	return false;
}

OrderedSet::OrderedSet() {
	m_size=0;
	int *Oarr=new int[1000]{0};
}
OrderedSet::~OrderedSet() {
	
}

void OrderedSet::add(int v) {
	bool same = false;
	for (int i = 0; i < m_size; i++) {
		if (v == Oarr[i]) {
			same = true;
			break;
		}
	}
	if (same == false) {
		Oarr[m_size] = v;

		for (int i = m_size; i > 0; i--) {
			if (Oarr[i] < Oarr[i - 1]) {
				int saver = Oarr[i];
				Oarr[i] = Oarr[i - 1];
				Oarr[i - 1] = saver;
			}
		}
		m_size += 1;
	}
}
void OrderedSet::add(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		this->add(arr[i]);
	}
}