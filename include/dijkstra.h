#include<iostream>
#include<functional>        
#include<math.h>        
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>

using namespace std;

#define num 30

class dijkstra {

private:
	pair<int, int> previous[num][num];
	int dist[num][num];//distance from the origin
	int reached = 0;//whether the destination is reached or not


public:
	vector<pair<int, int>>  pathD;        //Shortest pathD
	int visited[num][num];
	int filled[num][num];       //cells except for the walking path 
	int minX = 0, minY = 0;
	bool failed = false;

	dijkstra();
	void findmin(int dist[num][num], int& minX, int& minY);
	void findpath(pair<int, int> previous[num][num], int dist[num][num], int destX, int destY, int posX, int posY);
	void run(int posX, int posY, int destX, int destY, int grid[num][num]);
	void destroy();


};