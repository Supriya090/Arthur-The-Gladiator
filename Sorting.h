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
	vector<int> randomList;
	sf::Texture boxTexture;
	sf::Sprite boxSprite;
	sf::RenderWindow renderWindow;
	sf::Font numFont;
	std::vector<std::pair<sf::Sprite, sf::Text>> boxSprites;

public:
	Sorting(int, int);
	void merge(int, int, int);
	void mergeSort(int, int);
	void quickSort(int, int);
	int partition(int, int);
	void displaySort();
	int findIndex(int);
	vector<std::pair<sf::Sprite, sf::Text>> setBoxIndices();
};

Sorting::Sorting(int first, int last)
{
	for (int i = first; i <= last; i++)
	{
		randomList.push_back(i);
	}
	int swapIndex;
	for (int i = 0; i < randomList.size(); i++)
	{
		swapIndex = rand() % randomList.size();
		std::swap(randomList[i], randomList[swapIndex]);
	}

	if (!boxTexture.loadFromFile("images/box.png"))
	{
		std::cout << "Error Displaying Boxes" << std::endl;
	};

	boxSprite.setTexture(boxTexture);
	boxSprite.scale(0.06f, 0.06f);
	//std::fill(boxSprites.begin(), boxSprites.end(), 0);

	renderWindow.create(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");
	
	if (!numFont.loadFromFile("fonts/mainFont.ttf"))
	{
		std::cout << "Error Displaying Fonttt" << std::endl;
	}
}

void Sorting::merge(int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	vector<int> L(n1), R(n2);

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = randomList[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = randomList[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			randomList[k] = L[i];
			i++;
		}
		else
		{
			randomList[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1)
	{
		randomList[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2)
	{
		randomList[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void Sorting::mergeSort(int l, int r)
{
	if (l >= r)
	{
		return; //returns recursively
	}
	int m = (l + r - 1) / 2;
	mergeSort(l, m);
	mergeSort(m + 1, r);
	merge(l, m, r);
}

void Sorting::displaySort()
{
	for (int i = 0; i < randomList.size(); i++)
	{
		cout << randomList[i] << " ";
	}
	cout << endl;
}

int Sorting::findIndex(int randomNum)
{
	for (int i = 0; i < randomList.size(); i++)
	{
		std::cout << i + 1 << ": " << randomList[i] << std::endl;
		if (randomList[i] == randomNum)	return i+1;
	}
}

vector<std::pair<sf::Sprite, sf::Text>> Sorting::setBoxIndices()
{
	std::vector<std::pair<sf::Sprite, sf::Text>> boxes;
	int coordY = 200;
	int a = 0;
	for (int j = 0; j < 4; j++)
	{
		int coordX = 15;
		for (int i = 0; i < 10; i++)
		{
			//cout << randomList[a] << endl;
			sf::Text message(std::to_string(randomList[a]), numFont, 25);
			boxSprites.push_back(make_pair(boxSprite, message));
			boxSprites[a].first.setPosition(coordX, coordY);
			//boxSprites[a].second.scale(8.0f, 8.0f);
			boxSprites[a].second.setPosition(coordX + 25, coordY + 35);
			boxes.push_back(make_pair(boxSprites[a].first, boxSprites[a].second));
			coordX += 100;
			a++;
		}
		coordY += 140;
	}
	return boxes;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int Sorting::partition(int low, int high)
{
	int pivot = randomList[high]; // pivot
	int i = (low - 1);            // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (randomList[j] > pivot)
		{
			i++; // increment index of smaller element
			swap(randomList[i], randomList[j]);
		}
	}
	swap(randomList[i + 1], randomList[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void Sorting::quickSort(int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

#endif