////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "MyPlayer.h"
#include "Commons.h"
#include "Snake.h"
#include "Fruit.h"
#include <iostream>
namespace snake_arena {
	// Constructor
	MyPlayer::MyPlayer(int map_size) :
		Player(map_size) {
	}
	int MyPlayer::routedir(Snake* my_snake, Snake* enemy_snake, snake_arena::Pos objposition, snake_arena::Pos curposition, int turn, bool first) {
		if (objposition == curposition) return -1;
		int myx = curposition.x;
		int myy = curposition.y;
		int my_size = int(my_snake->getPositions().size());
		int en_size = int(enemy_snake->getPositions().size());
		bool graph[15][15][4];//동, 서, 남, 북 순으로!
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				for (int k = 0; k < 4; k++) {
					graph[i][j][k] = true;
				}
			}
		}
		for (int i = 0; i < 15; i++) {
			graph[0][i][1] = false;
			graph[14][i][0] = false;
			graph[i][14][2] = false;
			graph[i][0][3] = false;
		}
		for (int i = 0; i < my_size - 1; i++) {
			int rx = my_snake->getPositions()[i].x;
			int ry = my_snake->getPositions()[i].y;
			if (rx > 0) graph[rx - 1][ry][0] = false;
			if (rx < 14) graph[rx + 1][ry][1] = false;
			if (ry > 0) graph[rx][ry - 1][2] = false;
			if (ry < 14) graph[rx][ry + 1][3] = false;
		}
		for (int i = 0; i < en_size; i++) {
			int rx = enemy_snake->getPositions()[i].x;
			int ry = enemy_snake->getPositions()[i].y;
			if (rx > 0) graph[rx - 1][ry][0] = false;
			if (rx < 14) graph[rx + 1][ry][1] = false;
			if (ry > 0) graph[rx][ry - 1][2] = false;
			if (ry < 14) graph[rx][ry + 1][3] = false;
		}
		Pos Q[225];
		int Qstart = 0;
		int Qend = 0;
		Q[0] = curposition;
		Qend += 1;
		Pos parents[15][15];
		bool visited[15][15]{ false };
		visited[myx][myy] = true;
		while (Qstart != Qend) {
			Pos  cur = Q[Qstart];
			Qstart += 1;
			if (cur.x > 14 or cur.y > 14 or cur.y < 0 or cur.x < 0) {
				continue;
			}
			if (first) {
				if (turn % 2 == 0) {
					if (graph[cur.x][cur.y][2]) {
						Pos curr{ cur.x ,cur.y + 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][3]) {
						Pos curr{ cur.x ,cur.y - 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][0]) {
						Pos curr{ cur.x + 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y] != curposition) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][1]) {
						Pos curr{ cur.x - 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}


				}
				else
				{
					if (graph[cur.x][cur.y][0]) {
						Pos curr{ cur.x + 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y] != curposition) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][1]) {
						Pos curr{ cur.x - 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][2]) {
						Pos curr{ cur.x ,cur.y + 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][3]) {
						Pos curr{ cur.x ,cur.y - 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
				}
			}

			else {
				if (turn % 2 == 0) {
					if (graph[cur.x][cur.y][2]) {
						Pos curr{ cur.x ,cur.y + 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][3]) {
						Pos curr{ cur.x ,cur.y - 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][0]) {
						Pos curr{ cur.x + 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y] != curposition) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][1]) {
						Pos curr{ cur.x - 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}


				}
				else
				{
					if (graph[cur.x][cur.y][0]) {
						Pos curr{ cur.x + 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y] != curposition) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][1]) {
						Pos curr{ cur.x - 1,cur.y };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr == objposition) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][2]) {
						Pos curr{ cur.x ,cur.y + 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
					if (graph[cur.x][cur.y][3]) {
						Pos curr{ cur.x ,cur.y - 1 };
						if (not visited[curr.x][curr.y]) {
							Q[Qend] = curr; Qend += 1;
							visited[curr.x][curr.y] = true;
							parents[curr.x][curr.y] = cur;
						}
						if (curr.x == objposition.x and curr.y == objposition.y) {
							Pos son{ curr.x,curr.y };
							while (parents[son.x][son.y].x != myx or parents[son.x][son.y].y != myy) {
								Pos papa{ parents[son.x][son.y].x,parents[son.x][son.y].y };
								son = papa;
							}
							if (son.x == myx + 1) return 0;
							if (son.x == myx - 1) return 1;
							if (son.y == myy + 1) return 2;
							if (son.y == myy - 1) return 3;
						}
					}
				}
			}
		}
		return -1;
	}
	int MyPlayer::routedistance(Snake* my_snake, Snake* enemy_snake, snake_arena::Pos objposition, snake_arena::Pos curposition) {
		if (objposition == curposition) return 255;
		int myx = curposition.x;
		int myy = curposition.y;
		int my_size = int(my_snake->getPositions().size());
		int en_size = int(enemy_snake->getPositions().size());

		bool graph[15][15][4];//동, 서, 남, 북 순으로!
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				for (int k = 0; k < 4; k++) {
					graph[i][j][k] = true;
				}
			}
		}
		for (int i = 0; i < 15; i++) {
			graph[0][i][1] = false;
			graph[14][i][0] = false;
			graph[i][14][2] = false;
			graph[i][0][3] = false;
		}
		for (int i = 0; i < my_size - 1; i++) {
			int rx = my_snake->getPositions()[i].x;
			int ry = my_snake->getPositions()[i].y;
			if (rx > 0) graph[rx - 1][ry][0] = false;
			if (rx < 14) graph[rx + 1][ry][1] = false;
			if (ry > 0) graph[rx][ry - 1][2] = false;
			if (ry < 14) graph[rx][ry + 1][3] = false;
		}
		for (int i = 0; i < en_size; i++) {
			int rx = enemy_snake->getPositions()[i].x;
			int ry = enemy_snake->getPositions()[i].y;
			if (rx > 0) graph[rx - 1][ry][0] = false;
			if (rx < 14) graph[rx + 1][ry][1] = false;
			if (ry > 0) graph[rx][ry - 1][2] = false;
			if (ry < 14) graph[rx][ry + 1][3] = false;
		}
		Pos Q[225];
		int Qstart = 0;
		int Qend = 0;
		Q[0] = curposition;
		Qend += 1;
		bool visited[15][15]{ false };
		visited[myx][myy] = true;
		int distance[15][15]{ 255 };
		distance[myx][myy] = 0;
		while (Qstart != Qend) {
			Pos  cur = Q[Qstart];
			Qstart += 1;
			if (cur.x > 14 or cur.y > 14 or cur.y < 0 or cur.x < 0) {
				continue;
			}
			if (graph[cur.x][cur.y][0]) {
				Pos curr{ cur.x + 1,cur.y };
				if (not visited[curr.x][curr.y]) {
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
					distance[curr.x][curr.y] = distance[cur.x][cur.y] + 1;
				}
				if (curr == objposition) return distance[curr.x][curr.y];
			}
			if (graph[cur.x][cur.y][1]) {
				Pos curr{ cur.x - 1,cur.y };
				if (not visited[curr.x][curr.y]) {
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
					distance[curr.x][curr.y] = distance[cur.x][cur.y] + 1;
				}
				if (curr == objposition) return distance[curr.x][curr.y];
			}
			if (graph[cur.x][cur.y][2]) {
				Pos curr{ cur.x ,cur.y + 1 };
				if (not visited[curr.x][curr.y]) {
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
					distance[curr.x][curr.y] = distance[cur.x][cur.y] + 1;
				}
				if (curr == objposition) return distance[curr.x][curr.y];
			}
			if (graph[cur.x][cur.y][3]) {
				Pos curr{ cur.x ,cur.y - 1 };
				if (not visited[curr.x][curr.y]) {
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
					distance[curr.x][curr.y] = distance[cur.x][cur.y] + 1;
				}
				if (curr == objposition) return distance[curr.x][curr.y];
			}
		}
		return 255;

	}
	int MyPlayer::possibleroute(Snake* my_snake, Snake* en_snake, snake_arena::Pos curposition, int next = -1) {
		int myx = curposition.x;
		int myy = curposition.y;
		if (myx < 0 or myx>14 or myy < 0 or myy > 14) {
			return 0;
		}
		if (en_snake->hit(curposition)) {
			return 0;
		}
		if (next == -1) {
			if (my_snake->hit(curposition)) {
				return 0;
			}
		}

		int my_size = int(my_snake->getPositions().size());
		int en_size = int(en_snake->getPositions().size());

		bool graph[16][16][5];//동, 서, 남, 북 순으로!
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				for (int k = 0; k < 4; k++) {
					graph[i][j][k] = true;
				}
			}
		}
		for (int i = 0; i < 15; i++) {
			graph[0][i][1] = false;
			graph[14][i][0] = false;
			graph[i][14][2] = false;
			graph[i][0][3] = false;
		}
		for (int i = 0; i < my_size - 1; i++) {
			int rx = my_snake->getPositions()[i].x;
			int ry = my_snake->getPositions()[i].y;
			if (rx > 0) graph[rx - 1][ry][0] = false;
			if (rx < 14) graph[rx + 1][ry][1] = false;
			if (ry > 0) graph[rx][ry - 1][2] = false;
			if (ry < 14) graph[rx][ry + 1][3] = false;
		}
		if (next == -1) {
			for (int i = 0; i < en_size; i++) {
				int rx = en_snake->getPositions()[i].x;
				int ry = en_snake->getPositions()[i].y;
				if (rx > 0) graph[rx - 1][ry][0] = false;
				if (rx < 14) graph[rx + 1][ry][1] = false;
				if (ry > 0) graph[rx][ry - 1][2] = false;
				if (ry < 14) graph[rx][ry + 1][3] = false;
			}
		}
		else {
			for (int i = 0; i < en_size - 1; i++) {
				int rx = en_snake->getPositions()[i].x;
				int ry = en_snake->getPositions()[i].y;
				if (rx > 0) graph[rx - 1][ry][0] = false;
				if (rx < 14) graph[rx + 1][ry][1] = false;
				if (ry > 0) graph[rx][ry - 1][2] = false;
				if (ry < 14) graph[rx][ry + 1][3] = false;
			}
			int rx0 = en_snake->getPositions()[0].x + 1;
			int ry0 = en_snake->getPositions()[0].y;
			int rx1 = en_snake->getPositions()[0].x - 1;
			int ry1 = en_snake->getPositions()[0].y;
			int rx2 = en_snake->getPositions()[0].x;
			int ry2 = en_snake->getPositions()[0].y + 1;
			int rx3 = en_snake->getPositions()[0].x;
			int ry3 = en_snake->getPositions()[0].y - 1;
			switch (next) {
			case 0:
				if (rx0 > 0) graph[rx0 - 1][ry0][0] = false;
				if (rx0 < 14) graph[rx0 + 1][ry0][1] = false;
				if (ry0 > 0) graph[rx0][ry0 - 1][2] = false;
				if (ry0 < 14) graph[rx0][ry0 + 1][3] = false;
			case 1:

				if (rx1 > 0) graph[rx1 - 1][ry1][0] = false;
				if (rx1 < 14) graph[rx1 + 1][ry1][1] = false;
				if (ry1 > 0) graph[rx1][ry1 - 1][2] = false;
				if (ry1 < 14) graph[rx1][ry1 + 1][3] = false;
			case 2:

				if (rx2 > 0) graph[rx2 - 1][ry2][0] = false;
				if (rx2 < 14) graph[rx2 + 1][ry2][1] = false;
				if (ry2 > 0) graph[rx2][ry2 - 1][2] = false;
				if (ry2 < 14) graph[rx2][ry2 + 1][3] = false;
			case 3:

				if (rx3 > 0) graph[rx3 - 1][ry3][0] = false;
				if (rx3 < 14) graph[rx3 + 1][ry3][1] = false;
				if (ry3 > 0) graph[rx3][ry3 - 1][2] = false;
				if (ry3 < 14) graph[rx3][ry3 + 1][3] = false;

			}
		}
		Pos Q[225];
		int Qstart = 0;
		int Qend = 0;
		Q[0] = curposition;
		Qend += 1;
		bool visited[15][15]{ false };
		visited[myx][myy] = true;
		int cnt = 0;
		while (Qstart != Qend) {
			Pos  cur = Q[Qstart];
			Qstart += 1;
			if (cur.x > 14 or cur.y > 14 or cur.y < 0 or cur.x < 0) {
				continue;
			}
			if (graph[cur.x][cur.y][0]) {

				Pos curr{ cur.x + 1,cur.y };
				if (curr.x > 14 or curr.y > 14 or curr.y < 0 or curr.x < 0) {
					break;
				}
				if (not visited[curr.x][curr.y]) {
					cnt += 1;
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
				}
			}
			if (graph[cur.x][cur.y][1]) {
				Pos curr{ cur.x - 1,cur.y };
				if (curr.x > 14 or curr.y > 14 or curr.y < 0 or curr.x < 0) {
					break;
				}
				if (not visited[curr.x][curr.y]) {
					cnt += 1;
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
				}
			}
			if (graph[cur.x][cur.y][2]) {
				Pos curr{ cur.x ,cur.y + 1 };
				if (curr.x > 14 or curr.y > 14 or curr.y < 0 or curr.x < 0) {
					break;
				}
				if (not visited[curr.x][curr.y]) {
					cnt += 1;
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;
				}
			}
			if (graph[cur.x][cur.y][3]) {
				Pos curr{ cur.x ,cur.y - 1 };
				if (curr.x > 14 or curr.y > 14 or curr.y < 0 or curr.x < 0) {
					break;
				}
				if (not visited[curr.x][curr.y]) {
					cnt += 1;
					Q[Qend] = curr; Qend += 1;
					visited[curr.x][curr.y] = true;;
				}
			}
		}
		return cnt;
	}
	// Destructor
	MyPlayer::~MyPlayer() {
	}
	Pos MyPlayer::leftpos(Pos posit) {
		Pos left{ posit.x - 1, posit.y };
		return left;
	}
	Pos MyPlayer::rightpos(Pos posit) {
		Pos right{ posit.x + 1, posit.y };
		return right;
	}
	Pos MyPlayer::uppos(Pos posit) {
		Pos right{ posit.x , posit.y - 1 };
		return right;
	}
	Pos MyPlayer::downpos(Pos posit) {
		Pos right{ posit.x , posit.y + 1 };
		return right;
	}
	// Your function to primarily implement
	Direction MyPlayer::selectDirection(
		int turn, Snake* player_snake, Snake* enemy_snake,
		std::vector<Fruit*> fruits) {
		int myx = player_snake->getPositions()[0].x;
		int myy = player_snake->getPositions()[0].y;
		int enx = enemy_snake->getPositions()[0].x;
		int eny = enemy_snake->getPositions()[0].y;
		int mydirx = player_snake->getDirection().dx;
		int mydiry = player_snake->getDirection().dy;
		int endirx = enemy_snake->getDirection().dx;
		int endiry = enemy_snake->getDirection().dy;
		int mysize = player_snake->getPositions().size();
		int ensize = enemy_snake->getPositions().size();
		int f0dx = myx - int(fruits[0]->getPositions()[0].x);
		int f0dy = myy - int(fruits[0]->getPositions()[0].y);
		int f1dx = myx - int(fruits[1]->getPositions()[0].x);
		int f1dy = myy - int(fruits[1]->getPositions()[0].y);
		int dx = abs(myx - enx);
		int dy = abs(myy - eny);
		bool first = true;
		if ((dx + dy) % 2 == 1) first = false;
		Direction head{ player_snake->getDirection() };
		Pos mynext{ myx + mydirx,myy + mydiry };
		Pos mynextnext{ myx + 2 * mydirx,myy + 2 * mydiry };
		Pos ennext{ enx + endirx,eny + endiry };
		Pos ennextnext{ enx + 2 * endirx,eny + 2 * endiry };

		Pos enl{ enx - 1,eny };
		Pos enr{ enx + 1,eny };
		Pos enu{ enx,eny - 1 };
		Pos end{ enx ,eny + 1 };
		Pos myl{ myx - 1,myy };
		Pos myr{ myx + 1,myy };
		Pos myu{ myx,myy - 1 };
		Pos myd{ myx ,myy + 1 };
		bool B[4] = { true,true,true,true };//오른(E),왼(W),아래(S),위(N)
		bool jail[4] = { false,false,false,false };
		int lway = possibleroute(player_snake, enemy_snake, myl);
		int rway = possibleroute(player_snake, enemy_snake, myr);
		int dway = possibleroute(player_snake, enemy_snake, myd);
		int uway = possibleroute(player_snake, enemy_snake, myu);

		if (mysize >= 15 and !first) {
			if (lway < mysize + ensize) B[1] = false;
			if (rway < mysize + ensize) B[0] = false;
			if (uway < mysize + ensize) B[3] = false;
			if (dway < mysize + ensize) B[2] = false;
			if (not B[0] and not B[1] and not B[2] and not B[3]) {
				int max = lway;
				if (rway > max) max = rway;
				if (uway > max) max = uway;
				if (dway > max) max = dway;
				if (rway == max) {
					B[0] = true;
				}
				if (lway == max) {
					B[1] = true;
				}
				if (dway == max) {
					B[2] = true;
				}
				if (uway == max) {
					B[3] = true;
				}
			}
		}

		if (false);
			else {
			if (lway < mysize) B[1] = false;
			if (rway < mysize) B[0] = false;
			if (uway < mysize) B[3] = false;
			if (dway < mysize) B[2] = false;
			if (not B[0] and not B[1] and not B[2] and not B[3]) {
				int max = lway;
				if (rway > max) max = rway;
				if (uway > max) max = uway;
				if (dway > max) max = dway;
				if (rway == max) {
					B[0] = true;
				}
				if (lway == max) {
					B[1] = true;
				}
				if (dway == max) {
					B[2] = true;
				}
				if (uway == max) {
					B[3] = true;
				}
			}
		}

		// x가 14면 오른쪽(E)으로는 못감
		if (myx == 14) B[0] = false; if (myx == 0) B[1] = false; if (myy == 14) B[2] = false; if (myy == 0) B[3] = false;
		// 상대랑 부딪힘
		for (int i = 0; i < int(ensize); i++) {
			if (myx == enemy_snake->getPositions()[i].x - 1 and myy == enemy_snake->getPositions()[i].y) B[0] = false;
			if (myx == enemy_snake->getPositions()[i].x + 1 and myy == enemy_snake->getPositions()[i].y) B[1] = false;
			if (myx == enemy_snake->getPositions()[i].x and myy == enemy_snake->getPositions()[i].y - 1) B[2] = false;//아래
			if (myx == enemy_snake->getPositions()[i].x and myy == enemy_snake->getPositions()[i].y + 1) B[3] = false;//위
		}
		//자기 목이랑 부딪힘
		for (int i = 1; i < int(mysize); i++) {
			if (myx == player_snake->getPositions()[i].x - 1 and myy == player_snake->getPositions()[i].y) B[0] = false;
			if (myx == player_snake->getPositions()[i].x + 1 and myy == player_snake->getPositions()[i].y) B[1] = false;
			if (myx == player_snake->getPositions()[i].x and myy == player_snake->getPositions()[i].y - 1) B[2] = false;
			if (myx == player_snake->getPositions()[i].x and myy == player_snake->getPositions()[i].y + 1) B[3] = false;
		}

		bool E[4] = { true, true, true, true }; //상대방 bool
		for (int i = 0; i < int(mysize) - 1; i++) {
			if (enx == player_snake->getPositions()[i].x - 1 and eny == player_snake->getPositions()[i].y) E[0] = false;
			if (enx == player_snake->getPositions()[i].x + 1 and eny == player_snake->getPositions()[i].y) E[1] = false;
			if (enx == player_snake->getPositions()[i].x and eny == player_snake->getPositions()[i].y - 1) E[2] = false;//아래
			if (enx == player_snake->getPositions()[i].x and eny == player_snake->getPositions()[i].y + 1) E[3] = false;//위
		}
		for (int i = 1; i < int(ensize); i++) {
			if (enx == enemy_snake->getPositions()[i].x - 1 and eny == enemy_snake->getPositions()[i].y) E[0] = false;
			if (enx == enemy_snake->getPositions()[i].x + 1 and eny == enemy_snake->getPositions()[i].y) E[1] = false;
			if (enx == enemy_snake->getPositions()[i].x and eny == enemy_snake->getPositions()[i].y - 1) E[2] = false;//아래
			if (enx == enemy_snake->getPositions()[i].x and eny == enemy_snake->getPositions()[i].y + 1) E[3] = false;//위
		}

		if (mydirx == 1) B[1] = false; if (mydirx == -1) B[0] = false; if (mydiry == 1) B[3] = false; if (mydiry == -1) B[2] = false;
		if (not E[0] and not E[1] and not E[2] and E[3]) {
			if (myx == enx + 1 and myy == eny - 1 and B[1]) return DrtW();
			if (myx == enx - 1 and myy == eny - 1 and B[0]) return DrtE();
			if (myx == enx and myy == eny - 2 and B[2]) return DrtS();
		}
		//남쪽으로가는 친구..
		if (not E[0] and not E[1] and E[2] and not E[3]) {
			if (myx == enx + 1 and myy == eny + 1 and B[1]) return DrtW();
			if (myx == enx - 1 and myy == eny + 1 and B[0]) return DrtE();
			if (myx == enx and myy == eny + 2 and B[2]) return DrtN();
		}
		//서쪽으로 가는 친구..
		if (not E[0] and E[1] and not E[2] and not E[3]) {
			if (myx == enx - 1 and myy == eny + 1 and B[3]) return DrtN();
			if (myx == enx - 1 and myy == eny - 1 and B[2]) return DrtS();
			if (myx == enx - 2 and myy == eny and B[0]) return DrtE();
		}
		//동쪽으로 가는 친구..
		if (E[0] and not E[1] and not E[2] and not E[3]) {
			if (myx == enx + 1 and myy == eny + 1 and B[3]) return DrtN();
			if (myx == enx + 1 and myy == eny - 1 and B[2]) return DrtS();
			if (myx == enx + 2 and myy == eny and B[1]) return DrtW();
		}
		//월북할 예정인 녀석 저격

		if (enx == 0 and endiry == 1 and mydiry == 1 and myx == 1 and myy<eny + 3 and myy > eny and B[1]) return DrtW();
		if (enx == 0 and endiry == -1 and mydiry == -1 and myx == 1 and myy > eny - 3 and myy < eny and B[1]) return DrtW();
		if (enx == 14 and endiry == 1 and mydiry == 1 and myx == 13 and myy<eny + 3 and myy > eny and B[0]) return DrtE();
		if (enx == 14 and endiry == -1 and mydiry == -1 and myx == 13 and myy > eny - 3 and myy < eny and B[0]) return DrtE();

		if (eny == 0 and endirx == 1 and mydirx == 1 and myy == 1 and myx<enx + 3 and myx > enx and B[3]) return DrtN();
		if (eny == 0 and endirx == -1 and mydirx == -1 and myy == 1 and myx > enx - 3 and myx < enx and B[3]) return DrtN();
		if (eny == 14 and endirx == 1 and mydirx == 1 and myy == 13 and myx<enx + 3 and myx > enx and B[2]) return DrtS();
		if (eny == 14 and endirx == -1 and mydirx == -1 and myy == 13 and myx > enx - 3 and myx < enx and B[2]) return DrtS();

		//shield pattern. 후공에서만 동작함
		if (!first) {
			if (B[0]) {
				Pos myrr{ myr.x + 1,myr.y };
				Pos myru{ myr.x,myr.y - 1 };
				Pos myrd{ myr.x, myr.y + 1 };
				Pos enhead = enemy_snake->getPositions()[0];
				bool rr, ru, rd;
				rr = ru = rd = true;
				//hit부분을 길이-1까지 부딪히는 걸로 바꾸어야함.
				if (enemy_snake->hit(myrr) or player_snake->hit(myrr) or myrr.x == 15) rr = false;
				if (enemy_snake->hit(myru) or player_snake->hit(myru) or myru.y == -1) ru = false;
				if (enemy_snake->hit(myrd) or player_snake->hit(myrd) or myrd.y == 15) rd = false;
				//오른쪽으로 가면 오른쪽밖에 못감 but 상대가 거기로 올수있음
				if (enhead == myrr and not rd and not ru) B[0] = false;
				//위
				if (enhead == myru and not rr and not rd) B[0] = false;
				//아래
				if (enhead == myrd and not rr and not ru) B[0] = false;

			}
			if (B[1]) {
				Pos myll{ myl.x - 1,myl.y };
				Pos mylu{ myl.x,myl.y - 1 };
				Pos myld{ myl.x, myl.y + 1 };
				Pos enhead = enemy_snake->getPositions()[0];
				bool ll, lu, ld;
				ll = lu = ld = true;
				//hit부분을 길이-1까지 부딪히는 걸로 바꾸어야함.
				if (enemy_snake->hit(myll) or player_snake->hit(myll) or myll.x == -1) ll = false;
				if (enemy_snake->hit(mylu) or player_snake->hit(mylu) or mylu.y == -1) lu = false;
				if (enemy_snake->hit(myld) or player_snake->hit(myld) or myld.y == 15) ld = false;
				//오른쪽으로 가면 오른쪽밖에 못감 but 상대가 거기로 올수있음
				if (enhead == myll and not ld and not lu) B[1] = false;
				//위
				if (enhead == mylu and not ll and not ld) B[1] = false;
				//아래
				if (enhead == myld and not ll and not lu) B[1] = false;

			}
			if (B[2]) {
				Pos mydl{ myd.x - 1,myd.y };
				Pos mydr{ myd.x + 1,myd.y };
				Pos mydd{ myd.x, myd.y + 1 };
				Pos enhead = enemy_snake->getPositions()[0];
				bool dl, dd, dr;
				dl = dd = dr = true;
				if (enemy_snake->hit(mydl) or player_snake->hit(mydl) or mydl.x == -1) dl = false;
				if (enemy_snake->hit(mydd) or player_snake->hit(mydd) or mydd.y == 15) dd = false;
				if (enemy_snake->hit(mydr) or player_snake->hit(mydr) or mydr.x == 15) dr = false;
				if (enhead == mydl and not dd and not dr) B[2] = false;
				if (enhead == mydr and not dl and not dd) B[2] = false;
				if (enhead == mydd and not dl and not dr) B[2] = false;
			}
			if (B[3]) {
				Pos myul{ myu.x - 1,myu.y };
				Pos myur{ myu.x + 1,myu.y };
				Pos myuu{ myu.x, myu.y - 1 };
				Pos enhead = enemy_snake->getPositions()[0];
				bool ul, uu, ur;
				ul = uu = ur = true;
				if (enemy_snake->hit(myul) or player_snake->hit(myul) or myul.x == -1) ul = false;
				if (enemy_snake->hit(myuu) or player_snake->hit(myuu) or myuu.y == -1) uu = false;
				if (enemy_snake->hit(myur) or player_snake->hit(myur) or myur.x == 15) ur = false;
				if (enhead == myul and not ur and not uu) B[3] = false;
				if (enhead == myuu and not ul and not ur) B[3] = false;
				if (enhead == myuu and not ul and not uu) B[3] = false;
			}
		}

		//attack pattern 1



		if (mysize > 6) {
			//atk
			//attack
			Pos posit0{ myx - 2, myy - 2 };
			if (player_snake->hit(posit0)) {
				if (enx == myx - 1 and eny == myy - 2 and B[3]) return DrtN();
				if (enx == myx - 2 and eny == myy - 1 and B[1]) return DrtW();
			}
			Pos posit1{ myx + 2, myy - 2 };
			if (player_snake->hit(posit1)) {
				if (enx == myx + 2 and eny == myy - 1 and B[0]) return DrtE();
				if (enx == myx + 1 and eny == myy - 2 and B[3]) return DrtN();
			}
			Pos posit2{ myx + 2, myy + 2 };
			if (player_snake->hit(posit2)) {
				if (enx == myx + 1 and eny == myy + 2 and B[2]) return DrtS();
				if (enx == myx + 2 and eny == myy + 1 and B[0]) return DrtE();
			}
			Pos posit3{ myx + 2, myy - 2 };
			if (player_snake->hit(posit3)) {
				if (enx == myx + 2 and eny == myy - 1 and B[0]) return DrtE();
				if (enx == myx + 1 and eny == myy - 2 and B[3]) return DrtN();
			}
			//attack end
			//attack pattern 3
			if (mysize > 10) {
				if ((player_snake->hit(end) and enu == myr) or (player_snake->hit(enu) and end == myr) and B[0]) return DrtE();
				if ((player_snake->hit(end) and enu == myl) or (player_snake->hit(enu) and end == myl) and B[1]) return DrtW();
				if ((player_snake->hit(enl) and enr == myd) or (player_snake->hit(enr) and enl == myd) and B[2]) return DrtS();
				if ((player_snake->hit(enl) and enr == myu) or (player_snake->hit(enr) and enl == myu) and B[3]) return DrtN();
			}
			if (mydirx == 1) B[1] = false; if (mydirx == -1) B[0] = false; if (mydiry == 1) B[3] = false; if (mydiry == -1) B[2] = false;
		}

		if (myl == ennext and B[1]) return DrtW();
		if (myr == ennext and B[0]) return DrtE();
		if (myd == ennext and B[2]) return DrtS();
		if (myu == ennext and B[3]) return DrtN();
		


		int endistance0 = routedistance(enemy_snake, player_snake, fruits[0]->getPositions()[0], enemy_snake->getPositions()[0]);
		int endistance1 = routedistance(enemy_snake, player_snake, fruits[1]->getPositions()[0], enemy_snake->getPositions()[0]);
		int mydistance0 = routedistance(enemy_snake, player_snake, fruits[0]->getPositions()[0], player_snake->getPositions()[0]);
		int mydistance1 = routedistance(enemy_snake, player_snake, fruits[1]->getPositions()[0], player_snake->getPositions()[0]);
		if (mydistance0 <= endistance0 and mydistance1 <= endistance1) {
			if (endistance0 < endistance1) {
				switch (routedir(player_snake, enemy_snake, fruits[0]->getPositions()[0], player_snake->getPositions()[0], turn, first)) {
				case 0:
					if (B[0]) return DrtE();
				case 1:
					if (B[1]) return DrtW();
				case 2:
					if (B[2]) return DrtS();
				case 3:
					if (B[3]) return DrtN();
				case -1:
					int x = 1;
				}
			}
			else {
				switch (routedir(player_snake, enemy_snake, fruits[1]->getPositions()[0], player_snake->getPositions()[0], turn, first)) {
				case 0:
					if (B[0]) return DrtE();
				case 1:
					if (B[1]) return DrtW();
				case 2:
					if (B[2]) return DrtS();
				case 3:
					if (B[3]) return DrtN();
				case -1:
					int x = 1;
				}
			}
		}
		else if (mydistance0 <= endistance0) {
			switch (routedir(player_snake, enemy_snake, fruits[0]->getPositions()[0], player_snake->getPositions()[0], turn, first)) {
			case 0:
				if (B[0]) return DrtE();
			case 1:
				if (B[1]) return DrtW();
			case 2:
				if (B[2]) return DrtS();
			case 3:
				if (B[3]) return DrtN();
			case -1:
				int x = 1;
			}
		}
		else if (mydistance1 <= endistance1) {
			switch (routedir(player_snake, enemy_snake, fruits[1]->getPositions()[0], player_snake->getPositions()[0], turn, first)) {
			case 0:
				if (B[0]) return DrtE();
			case 1:
				if (B[1]) return DrtW();
			case 2:
				if (B[2]) return DrtS();
			case 3:
				if (B[3]) return DrtN();
			case -1:
				int x = 1;
			}
		}

		if (possibleroute(enemy_snake, player_snake, enemy_snake->getPositions()[0], 0) < ensize and B[0]) return DrtE();
		if (possibleroute(enemy_snake, player_snake, enemy_snake->getPositions()[0], 1) < ensize and B[1]) return DrtW();
		if (possibleroute(enemy_snake, player_snake, enemy_snake->getPositions()[0], 2) < ensize and B[2]) return DrtS();
		if (possibleroute(enemy_snake, player_snake, enemy_snake->getPositions()[0], 3) < ensize and B[3]) return DrtN();


		if (true) {
			snake_arena::Pos midium{ 7,7 };
			int middistance = routedistance(player_snake, enemy_snake, midium, player_snake->getPositions()[0]);
			if (middistance != 255) {
				switch (routedir(player_snake, enemy_snake, midium, player_snake->getPositions()[0], turn, first)) {
				case 0:
					if (B[0]) return DrtE();
				case 1:
					if (B[1]) return DrtW();
				case 2:
					if (B[2]) return DrtS();
				case 3:
					if (B[3]) return DrtN();
				case -1:
					int x = 1;
				}
			}
		}
		//attack pattern
		if (mynext == ennext and not player_snake->hit(mynext) and not enemy_snake->hit(mynext)) return head;
		//방해 코드
		if (true) {
			bool east{ false };
			bool west{ false };
			bool north{ false };
			bool south{ false };
			if ((myx < 6)) east = true;
			if ((myx > 6)) west = true;
			if ((myy < 7)) south = true;
			if ((myy > 7)) north = true;
			switch (turn % 5) {
			case 0:
				if (east and B[0]) return DrtE();
				if (west and B[1]) return DrtW();
				if (south and B[2]) return DrtS();
				if (north and B[3]) return DrtN();
			case 1:
				if (east and B[0]) return DrtE();
				if (west and B[1]) return DrtW();
				if (south and B[2]) return DrtS();
				if (north and B[3]) return DrtN();
			case 2:
				if (north and B[3]) return DrtN();
				if (east and B[0]) return DrtE();
				if (west and B[1]) return DrtW();
				if (south and B[2]) return DrtS();
			case 3:
				if (south and B[2]) return DrtS();
				if (north and B[3]) return DrtN();
				if (east and B[0]) return DrtE();
				if (west and B[1]) return DrtW();
			case 4:
				if (east and B[0]) return DrtE();
				if (west and B[1]) return DrtW();
				if (south and B[2]) return DrtS();
				if (north and B[3]) return DrtN();
			}
		}				//갈수있는 길
		if (!first) {
			if (B[1] and int(mydirx) != 1) return DrtW();
			if (B[0] and int(mydirx) != -1) return DrtE();
			if (B[2] and int(mydiry) != -1) return DrtS();
			if (B[3] and int(mydiry) != -1) return DrtN();
		}
		if (first) {
			switch (turn % 4) {
			case 0:
				if (B[0] and int(mydirx) != -1) return DrtE();
				if (B[1] and int(mydirx) != 1) return DrtW();
				if (B[2] and int(mydiry) != -1) return DrtS();
				if (B[3] and int(mydiry) != -1) return DrtN();
			case 1:
				if (B[3] and int(mydiry) != -1) return DrtN();
				if (B[0] and int(mydirx) != -1) return DrtE();
				if (B[1] and int(mydirx) != 1) return DrtW();
				if (B[2] and int(mydiry) != -1) return DrtS();

			case 2:
				if (B[2] and int(mydiry) != -1) return DrtS();
				if (B[3] and int(mydiry) != -1) return DrtN();
				if (B[0] and int(mydirx) != -1) return DrtE();
				if (B[1] and int(mydirx) != 1) return DrtW();
			case 3:
				if (B[1] and int(mydirx) != 1) return DrtW();
				if (B[2] and int(mydiry) != -1) return DrtS();
				if (B[3] and int(mydiry) != -1) return DrtN();
				if (B[0] and int(mydirx) != -1) return DrtE();
			}
		}



		//돌리기 실패했을때. 비참하게 처음으로 돌아가서 해야한다..
		B[0] = B[1] = B[2] = B[3] = true;
		if (myx == 14) B[0] = false;
		if (myx == 0) B[1] = false;
		if (myy == 14) B[2] = false;
		if (myy == 0) B[3] = false; // y가 0이면 위쪽(N) 못감
		// 부딪히지 말자
		// 상대랑 부딪힘
		for (int i = 0; i < int(ensize); i++) {
			if (myx == enemy_snake->getPositions()[i].x - 1 and myy == enemy_snake->getPositions()[i].y) B[0] = false;
			if (myx == enemy_snake->getPositions()[i].x + 1 and myy == enemy_snake->getPositions()[i].y) B[1] = false;
			if (myx == enemy_snake->getPositions()[i].x and myy == enemy_snake->getPositions()[i].y - 1) B[2] = false;//아래
			if (myx == enemy_snake->getPositions()[i].x and myy == enemy_snake->getPositions()[i].y + 1) B[3] = false;//위
		}
		for (int i = 1; i < int(mysize); i++) {
			if (myx == player_snake->getPositions()[i].x - 1 and myy == player_snake->getPositions()[i].y) B[0] = false;
			if (myx == player_snake->getPositions()[i].x + 1 and myy == player_snake->getPositions()[i].y) B[1] = false;
			if (myx == player_snake->getPositions()[i].x and myy == player_snake->getPositions()[i].y - 1) B[2] = false;
			if (myx == player_snake->getPositions()[i].x and myy == player_snake->getPositions()[i].y + 1) B[3] = false;
		}
		if (mydirx == 1) B[1] = false; if (mydirx == -1) B[0] = false; if (mydiry == 1) B[3] = false; if (mydiry == -1) B[2] = false;
		if (B[1] and int(mydirx) != 1) return DrtW(); if (B[0] and int(mydirx) != -1) return DrtE(); if (B[2] and int(mydiry) != -1) return DrtS(); if (B[3] and int(mydiry) != -1) return DrtN();
		return DrtN();
	}
}