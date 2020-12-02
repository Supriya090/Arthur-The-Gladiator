#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <set>
#include <queue>
#include <climits>
#include <functional>
#include <math.h>
#include <float.h>
#include <vector>
#include <set>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

#define N 12


// queue node used in BFS
class Node
{
public:
	// (x, y) represents chess board coordinates
	// dist represent its minimum distance from the source
	int x, y, dist;

	//Default constructor
	Node()
	{
	}

	// Node constructor
	Node(int x, int y, int dist = 0) : x(x), y(y), dist(dist) {}

	// As we are using struct as a key in a std::set,
	// we need to overload < operator
	// Alternatively we can use std::pair<int, int> as a key
	// to store coordinates of the matrix in the set

	bool operator<(const Node &o) const
	{
		return x < o.x || (x == o.x && y < o.y);
	}
};

class bfs {
private:

	pair<int, int> previous[N][N];
	int dist[N][N]; //distance from the origin
	int visited[N][N];


public:

	vector<pair<int, int>> pathD; //Shortest pathD

	bfs();
	~bfs();

	bool valid(int x, int y);
	bool BFS(pair<int, int> previous[N][N], int kx, int ky, int dx, int dy, int dist[N][N]);
	void findpath(int destX, int destY, int posX, int posY);

};
