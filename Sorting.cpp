#include "Sorting.h"

Sorting::Sorting()
{
	int first = 1; int last = 100;
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
	for (int i = 0; i < 40; i++)
	{
		randomListDisplay.push_back(randomList[i]);
	}
	srand(time(NULL));
	randomNum = randomListDisplay[rand() % 40];
}

//Ascending Sort
void Sorting::merge(int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp vectors
	vector<int> L(n1), R(n2);

	// Copy data to temp vectors
	for (int i = 0; i < n1; i++)
		L[i] = randomListDisplay[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = randomListDisplay[m + 1 + j];

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	//Merge the subarrays back
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			randomListDisplay[k] = L[i];
			i++;
		}
		else
		{
			randomListDisplay[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[]
	while (i < n1)
	{
		randomListDisplay[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[]
	while (j < n2)
	{
		randomListDisplay[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is right index of the sub-array to be sorted 
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


//Descending Sort

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
vector, and places all elements greater than pivot
to left of pivot and all smaller elements to right
of pivot */
int Sorting::partition(int low, int high)
{
	int pivot = randomListDisplay[high]; // pivot
	int i = (low - 1);            // Index of greater element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is greater than the pivot
		if (randomListDisplay[j] > pivot)
		{
			i++; // increment index of greater element
			swap(randomListDisplay[i], randomListDisplay[j]);
		}
	}
	swap(randomListDisplay[i + 1], randomListDisplay[high]);
	return (i + 1);
}

void Sorting::quickSort(int low, int high)
{
	if (low < high)
	{
		//Moves the element to its correct place
		int pi = partition(low, high);

		// Separately sort elements before partition and after partition
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

int Sorting::getRandomNum()
{
	return randomNum;
}

int Sorting::findIndex()
{
	for (int i = 0; i < randomListDisplay.size(); i++)
	{
		std::cout << i + 1 << ": " << randomList[i] << std::endl;
		if (randomListDisplay[i] == randomNum)
		{
			return i + 1;
		}
	}
}

vector<int> Sorting::getSort()
{
	vector<int> randomInts;
	for (int i = 0; i < randomListDisplay.size(); i++)
	{
		randomInts.push_back(randomListDisplay[i]);
	}
	return randomInts;
}