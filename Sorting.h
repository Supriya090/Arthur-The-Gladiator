#ifndef SORTING_HPP
#define SORTING_HPP

#include<SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include<string>

using namespace std;

class Sorting
{
private:
	vector<int> randomList, randomListDisplay;
	int randomNum;

public:
	Sorting();
	void merge(int, int, int);
	void mergeSort(int, int);
	void quickSort(int, int);
	int partition(int, int);
	vector<int> getSort();
	int findIndex();
	int getRandomNum();
};

#endif