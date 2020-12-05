#include "dijkstra.h"
#include<SFML/Window.hpp>

dijkstra::dijkstra()
{
	//set all the distances to maximum float value;theoritically infinity
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
			dist[i][j] = INT32_MAX;

}

void dijkstra::findmin(int dist[num][num], int& minX, int& minY) {

	int minimum = INT32_MAX;
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
			if (visited[i][j] == false && dist[i][j] < minimum) {
				minimum = dist[i][j];
				minX = i;
				minY = j;
			}
}


void dijkstra::findpath(pair<int, int> previous[num][num], int dist[num][num], int destX, int destY, int posX, int posY) {
	if (dist[destX][destY] > 100)
	{
		failed = true;
		cout << "Destination is out of reach, firstly clear the road!!!";
	}
	else
	{
		failed = false;
		cout << "\nLength of Dijkstra path is: " << dist[destX][destY] << endl;
		while (previous[destX][destY].first != posX || previous[destX][destY].second != posY) {        // both simultaneously not equal to source coordinates
			sf::sleep(sf::milliseconds(10));        //delay shortest pathD
			pathD.push_back(make_pair(previous[destX][destY].first, previous[destX][destY].second));
			int aX = destX, aY = destY;
			destX = previous[aX][aY].first;
			destY = previous[aX][aY].second;
		}
	}

}

void dijkstra::run(int posX, int posY, int destX, int destY, int grid[num][num]) {

	//set the distance of origin to zero
	dist[posX][posY] = 0.0;

	for (int i = 0; i < num && reached == 0; i++)
		for (int j = 0; j < num && reached == 0; j++) {


			findmin(dist, minX, minY);

			visited[minX][minY] = true;

			if (visited[destX][destY] == true) {
				reached = 1;
				break;
			}
			sf::sleep(sf::milliseconds(1));        //delay exploration
			//north
			if (grid[minX - 1][minY] != 0 && visited[minX - 1][minY] == false && dist[minX - 1][minY] > dist[minX][minY] + 1.0) {
				dist[minX - 1][minY] = dist[minX][minY] + 1.0;
				previous[minX - 1][minY] = make_pair(minX, minY);
			}
			//south
			if (grid[minX + 1][minY] != 0 && visited[minX + 1][minY] == false && dist[minX + 1][minY] > dist[minX][minY] + 1.0) {
				dist[minX + 1][minY] = dist[minX][minY] + 1.0;
				previous[minX + 1][minY] = make_pair(minX, minY);
			}
			//west
			if (grid[minX][minY - 1] != 0 && visited[minX][minY - 1] == false && dist[minX][minY - 1] > dist[minX][minY] + 1.0) {
				dist[minX][minY - 1] = dist[minX][minY] + 1.0;
				previous[minX][minY - 1] = make_pair(minX, minY);
			}
			//east:i,j+1
			if (grid[minX][minY + 1] != 0 && visited[minX][minY + 1] == false && dist[minX][minY + 1] > dist[minX][minY] + 1.0) {
				dist[minX][minY + 1] = dist[minX][minY] + 1.0;
				previous[minX][minY + 1] = make_pair(minX, minY);
			}
			//north-east:i-1,j+1
			// if(grid[minX-1][minY+1]==1 && visited[minX-1][minY+1]==false &&
			//     dist[minX-1][minY+1]>dist[minX][minY]+sqrt(2) && !(grid[minX-1][minY]==0 && grid[minX][minY+1]==0)){
			//     dist[minX-1][minY+1]=dist[minX][minY]+sqrt(2);
			//     previous[minX-1][minY+1]=make_pair(minX,minY);
			// }
			// //south-east:i+1,j+1
			// if(grid[minX+1][minY+1]==1 && visited[minX+1][minY+1]==false &&
			//     dist[minX+1][minY+1]>dist[minX][minY]+sqrt(2) && !(grid[minX+1][minY]==0 && grid[minX][minY+1]==0)){
			//     dist[minX+1][minY+1]=dist[minX][minY]+sqrt(2);
			//     previous[minX+1][minY+1]=make_pair(minX,minY);
			// }
			// //south-west:i+1,j-1
			// if(grid[minX+1][minY-1]==1 && visited[minX+1][minY-1]==false &&
			//     dist[minX+1][minY-1]>dist[minX][minY]+sqrt(2) && !(grid[minX+1][minY]==0 && grid[minX][minY-1]==0)){
			//     dist[minX+1][minY-1]=dist[minX][minY]+sqrt(2);
			//     previous[minX+1][minY-1]=make_pair(minX,minY);
			// }
			// //north-west:i-1,j-1
			// if(grid[minX-1][minY-1]==1 && visited[minX-1][minY-1]==false &&
			//     dist[minX-1][minY-1]>dist[minX][minY]+sqrt(2) && !(grid[minX-1][minY]==0 && grid[minX][minY-1]==0)){
			//     dist[minX-1][minY-1]=dist[minX][minY]+sqrt(2);
			//     previous[minX-1][minY-1]=make_pair(minX,minY);
			// }
		}
	findpath(previous, dist, destX, destY, posX, posY);
}

void dijkstra::destroy() {
	for (int i = 0; i < pathD.size(); i++)
	{                                                      //final pathD
		filled[pathD[i].first][pathD[i].second] = 0;
	}
	pathD.clear();
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
		{
			if (visited[i][j] == 1)
			{
				visited[i][j] = 0;
			}//all cells are unvisited
		}
	cout << "called";
}