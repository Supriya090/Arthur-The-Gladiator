#include "bfs.h"

bfs::bfs() {

}

bfs::~bfs() {

}


// Check if (x, y) is valid chess board coordinates
// Note that a knight cannot go out of the chessboard
bool bfs::valid(int x, int y)
{
	if (x < 0 || y < 0 || x >= N || y >= N)
		return false;
	//  tileMap[x][y].setFillColor(sf::Color::Yellow);
	return true;
}


// Find minimum number of steps taken by the knight
// from source to reach destination using BFS
bool bfs::BFS(pair<int, int> previous[N][N], int kx, int ky, int dx, int dy, int dist[N][N])
{

	pathD.clear();

	Node src(kx, ky);
	Node dest(dx, dy);

	// create a queue and enqueue first node
	queue<Node> q;
	q.push(src);

	// Below arrays details all 8 possible movements
// for a knight
	int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

	//set all the distances to maximum float value;theoritically infinity
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			dist[i][j] = INT32_MAX;
			visited[i][j] = false;
		}

	// loop till queue is empty
	while (!q.empty())
	{
		// pop front node from queue and process it
		Node node = q.front();
		q.pop();

		int x = node.x;
		int y = node.y;
		dist[x][y] = node.dist;

		visited[x][y] = true;

		if (x == dest.x && y == dest.y)
		{
			return true;
		}

		// Skip if location is visited before

		// check for all 8 possible movements for a knight
		// and enqueue each valid movement into the queue
		for (int i = 0; i < 8; ++i)
		{
			// Get the new valid position of Knight from current
			// position on chessboard and enqueue it with +1 distance
			int x1 = x + row[i];
			int y1 = y + col[i];

			if (valid(x1, y1) && visited[x1][y1] == false)
			{
				visited[x1][y1] = true;
				q.push({ x1, y1, dist[x][y] + 1 });
				previous[x1][y1] = make_pair(x, y);
				cout << "(" << x << "," << y << ")-->"
					<< "(" << x1 << "," << y1 << ")" << endl;
			}

			// if destination is reached, return distance
		}
	}

	return false;
}

void bfs::findpath(int destX, int destY, int posX, int posY)
{
	if (BFS(previous, posX, posY, destX, destY, dist) == false)
	{

		cout << "Destination is out of reach, firstly clear the road!!!";
		return;
	}

	else

	{
		cout << "\nLength of BFS path is: " << dist[destX][destY] << endl;

		pathD.push_back(make_pair(destX, destY));
		while (previous[destX][destY].first != posX || previous[destX][destY].second != posY)
		{ // both simultaneously not equal to source coordinates
			// sf::sleep(sf::milliseconds(10));        //delay shortest pathD
			// cout<<"buhjbujh"<<destX<<"  "<<destY<<endl;

			pathD.push_back(make_pair(previous[destX][destY].first, previous[destX][destY].second));
			int aX = destX, aY = destY;
			destX = previous[aX][aY].first;
			destY = previous[aX][aY].second;
		}

		// printing path from source to destination
		cout << pathD.size() << "\nPath is::\n";
		for (int i = pathD.size() - 1; i >= 0; i--)
			cout << "(" << pathD[i].first << " ," << pathD[i].second << ")" << endl;
	}
}
