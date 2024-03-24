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
#include<iostream>
#include<vector>
#include<queue>
namespace snake_arena {
	// Constructor
	MyPlayer::MyPlayer(int map_size) :
		Player(map_size) {

	}

	// Destructor
	MyPlayer::~MyPlayer() {

	}
	// Your function to primarily implement
	int route(Snake* my_snake, Snake* enemy_snake, Fruit* fruit) {
		int map[225] = { 0 };
		for (int i = 0; i<int(my_snake->getPositions().size()); i++) {
			map[my_snake->getPositions()[i].x+15*my_snake->getPositions()[i].y] = 1;
		}
		for (int i = 0; i<int(enemy_snake->getPositions().size()); i++) {
			map[enemy_snake->getPositions()[i].x+15*enemy_snake->getPositions()[i].y] = 1;
		}
		int fruitx = fruit->getPositions()[0].x;
		int fruity = fruit->getPositions()[0].y;
		int distance[225] = { 0 };
		return 0;
	}
	bool MyPlayer::isthere(Snake* snake, int x, int y) {
		if (x == -1 or x == 15 or y == -1 or y == 15) {
			return true;
		}
		for (int i = 0; i<int(snake->getPositions().size()); i++) {
			if (int(snake->getPositions()[i].x) == x and int(snake->getPositions()[i].y) == y) {
				return true;
			}
		}
		return false;
	}
	bool upleftclose(Snake* snake, Direction dir) {
		return true;
	}
	Direction MyPlayer::turnleft( Snake* player_snake) {
		if (player_snake->getDirection().dx ==1) {
			return DrtN();
		}
		if (player_snake->getDirection().dx == -1) {
			return DrtS();
		}
		if (player_snake->getDirection().dy == 1) {
			return DrtE();
		}
		else {
			return DrtW();
		}
	}
	Direction MyPlayer::turnright(Snake* player_snake) {
		if (player_snake->getDirection().dx == 1) {
			return DrtS();
		}
		if (player_snake->getDirection().dx == -1) {
			return DrtN();
		}
		if (player_snake->getDirection().dy == 1) {
			return DrtW();
		}
		else {
			return DrtE();
		}
	}




	Direction MyPlayer::selectDirection(
	int turn, Snake* player_snake, Snake* enemy_snake,
	std::vector<Fruit*> fruits)  {

		bool B[4] = { true,true,true,true };//오른(E),왼(W),아래(S),위(N)
		Direction head = DrtE();
		// x가 14면 오른쪽(E)으로는 못감
		if (player_snake->getPositions()[0].x == 14) {
			B[0] = false; 
		}
		if (player_snake->getPositions()[0].x == 0) {
			B[1] = false; // x가 0이면 왼쪽(W) 못감
		}
		if (player_snake->getPositions()[0].y == 14) {
			B[2] = false; // y가 14면 아래쪽(S) 못감
		}
		if (player_snake->getPositions()[0].y == 0) {
			B[3] = false; // y가 0이면 위쪽(N) 못감
		}
		// 부딪히지 말자
		// 상대랑 부딪힘
		for (int i = 0; i < int(enemy_snake->getPositions().size()); i++) {
			if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x - 1 and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y) {
				B[0] = false;
			}
			if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x + 1 and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y) {
				B[1] = false;
			}
			if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y - 1) {
				B[2] = false;//아래
			}
			if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y + 1) {
				B[3] = false;//위
			}
		}
		
		//자기 목이랑 부딪힘
		for (int i = 1; i < int(player_snake->getPositions().size()); i++) {
			if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x-1  and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y) {
				B[0] = false;
			}
			if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x + 1 and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y) {
				B[1] = false;
			}
			if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x  and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y - 1) {
				B[2] = false;
			}
			if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y + 1) {
				B[3] = false;
			}
		}
		if (player_snake->getDirection().dx == 1) {
			B[1] = false;
		}
		if (player_snake->getDirection().dx == -1) {
			B[0] = false;
		}
		if (player_snake->getDirection().dy == 1) {
			B[3] = false;
		}
		if (player_snake->getDirection().dy == -1) {
			B[2] = false;
		}
		//loop
		if (true) {
			bool cleft = false;
			bool cright = false;
			bool cup = false;
			bool cdown = false;
			int centerx = player_snake->getPositions()[0].x + 1;
			int centery = player_snake->getPositions()[0].y;
			if (centerx <= 0) {
				cleft = true;
			}

			if (centerx >= 14) {
				cright = true;
			}
			if (centery <= 0) {
				cdown = true;
			}
			if (centery >= 14) {
				cup = true;
			}
			for (int i = 0; i< int(player_snake->getPositions().size())-1; i++) {
				if (centerx == player_snake->getPositions()[i].x) {
					if (centery > player_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == player_snake->getPositions()[i].y) {
					if (centerx > player_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			for (int i = 0; i< int(enemy_snake->getPositions().size()) - 1; i++) {
				if (centerx == enemy_snake->getPositions()[i].x) {
					if (centery > enemy_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == enemy_snake->getPositions()[i].y) {
					if (centerx > enemy_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			if (cleft and cright and cup and cdown) {
				B[0] = false;
			}
		}
		if (true) {
			bool cleft = false;
			bool cright = false;
			bool cup = false;
			bool cdown = false;
			int centerx = player_snake->getPositions()[0].x - 1;
			int centery = player_snake->getPositions()[0].y;
			if (centerx <= 0) {
				cleft = true;
			}
			if (centerx >= 14) {
				cright = true;
			}
			if (centery <= 0) {
				cdown = true;
			}
			if (centery >= 14) {
				cup = true;
			}
			for (int i = 0; i< int(player_snake->getPositions().size())-1; i++) {
				if (centerx == player_snake->getPositions()[i].x) {
					if (centery > player_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == player_snake->getPositions()[i].y) {
					if (centerx > player_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			for (int i = 0; i< int(enemy_snake->getPositions().size()) - 1; i++) {
				if (centerx == enemy_snake->getPositions()[i].x) {
					if (centery > enemy_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == enemy_snake->getPositions()[i].y) {
					if (centerx > enemy_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			if (cleft and cright and cup and cdown) {
				B[1] = false;
			}
		}
		if (true) {
			bool cleft = false;
			bool cright = false;
			bool cup = false;
			bool cdown = false;
			int centerx = player_snake->getPositions()[0].x;
			int centery = player_snake->getPositions()[0].y+1;
			if (centerx <= 0) {
				cleft = true;
			}
			if (centerx >= 14) {
				cright = true;
			}
			if (centery <= 0) {
				cdown = true;
			}
			if (centery >= 14) {
				cup = true;
			}
			for (int i = 0; i< int(player_snake->getPositions().size())-1; i++) {
				if (centerx == int(player_snake->getPositions()[i].x)) {
					if (centery > int(player_snake->getPositions()[i].y)) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == int(player_snake->getPositions()[i].y)) {
					if (centerx > int(player_snake->getPositions()[i].x)) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			for (int i = 0; i< int(enemy_snake->getPositions().size())-1; i++) {
				if (centerx == enemy_snake->getPositions()[i].x) {
					if (centery > enemy_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == enemy_snake->getPositions()[i].y) {
					if (centerx > enemy_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			if (cleft and cright and cup and cdown) {
				B[2] = false;
			}
		}
		if (true) {
			bool cleft = false;
			bool cright = false;
			bool cup = false;
			bool cdown = false;
			int centerx = player_snake->getPositions()[0].x ;
			int centery = player_snake->getPositions()[0].y-1;
			if (centerx <= 0) {
				cleft = true;
			}
			if (centerx >= 14) {
				cright = true;
			}
			if (centery <= 0) {
				cdown = true;
			}
			if (centery >= 14) {
				cup = true;
			}
			for (int i = 0; i< int(player_snake->getPositions().size())-1; i++) {
				if (centerx == player_snake->getPositions()[i].x) {
					if (centery > player_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == player_snake->getPositions()[i].y) {
					if (centerx > player_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			for (int i = 0; i< int(enemy_snake->getPositions().size()) - 1; i++) {
				if (centerx == enemy_snake->getPositions()[i].x) {
					if (centery > enemy_snake->getPositions()[i].y) {
						cup = true;
					}
					else {
						cdown = true;
					}
				}
				if (centery == enemy_snake->getPositions()[i].y) {
					if (centerx > enemy_snake->getPositions()[i].x) {
						cleft = true;
					}
					else {
						cright = true;
					}
				}
			}
			if (cleft and cright and cup and cdown) {
				B[3] = false;
			}
		}
		
		bool loopup = false;
		bool loopdown = false;
		bool loopright = false;
		bool loopleft = false;

		for (int i = 1; i < int(player_snake->getPositions().size())-1; i++) {
			if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x) {
				if (player_snake->getPositions()[0].y > player_snake->getPositions()[i].y) {
					loopup = true;
				}
				else {
					loopdown = true;
				}
			}
		}
		for (int i = 1; i < int(player_snake->getPositions().size())-1; i++) {
			if (player_snake->getPositions()[0].y == player_snake->getPositions()[i].y) {
				if (player_snake->getPositions()[0].x > player_snake->getPositions()[i].x) {
					loopleft = true;
				}
				else {
					loopright = true;
				}
			}
		}
		//직진금지
		if (B[0] == false and player_snake->getDirection().dx == 1) {
			if (loopup) {
				return DrtS();
			}
			if (loopdown) {
				return DrtN();
			}
			if (player_snake->getPositions()[0].y > 6) {
				if (B[3]) {
					return DrtN();
				}
				else {
					return DrtS();
				}
			}
			else {
				if (B[2]) {
					return DrtS();
				}
				else {
					return DrtN();
				}
			}
		}
		if (B[1] == false and player_snake->getDirection().dx == -1) {
			if (loopup) {
				return DrtS();
			}
			if (loopdown) {
				return DrtN();
			}
			if (player_snake->getPositions()[0].y > 6) {
				if (B[3]) {
					return DrtN();
				}
				else {
					return DrtS();
				}
			}
			else {
				if (B[2]) {
					return DrtS();
				}
				else {
					return DrtN();
				}
			}
		}
		if (B[2] == false and player_snake->getDirection().dy == 1) {

			if (loopleft) {
				return DrtE();
			}
			if (loopright) {
				return DrtW();
			}
			if (player_snake->getPositions()[0].x < 7){
				if (B[0]) {
					return DrtE();
				}
				else {
					return DrtW();
				}
			}
			else {
				if (B[1]) {
					return DrtW();
				}
				else {
					return DrtE();
				}
			}
		}
		if (B[3] == false and player_snake->getDirection().dy == -1) {
			if (loopleft) {
				return DrtE();
			}
			if (loopright) {
				return DrtW();
			}
			if (player_snake->getPositions()[0].x < 7){
				if (B[0]) {
					return DrtE();
				}
				else {
					return DrtW();
				}
			}
			else {
				if (B[1]) {
					return DrtW();
				}
				else {
					return DrtE();
				}
			}
		}
		// 과일과 거리 계산
		int my_Distance1 = abs(player_snake->getPositions()[0].x - fruits[0]->getPositions()[0].x) + abs(player_snake->getPositions()[0].y - fruits[0]->getPositions()[0].y);
		int my_Distance2 = abs(player_snake->getPositions()[0].x - fruits[1]->getPositions()[0].x) + abs(player_snake->getPositions()[0].y - fruits[1]->getPositions()[0].y);
		int enemy_Distance1 = abs(enemy_snake->getPositions()[0].x - fruits[0]->getPositions()[0].x) + abs(enemy_snake->getPositions()[0].y - fruits[0]->getPositions()[0].y);
		int enemy_Distance2 = abs(enemy_snake->getPositions()[0].x - fruits[1]->getPositions()[0].x) + abs(enemy_snake->getPositions()[0].y - fruits[1]->getPositions()[0].y);//distance 계산

		if (my_Distance1 <= enemy_Distance1) {
			bool east{ false };
			bool west{ false };
			bool north{ false };
			bool south{ false };
			if ((player_snake->getPositions()[0].x < fruits[0]->getPositions()[0].x)) {
				east = true;
			}
			if ((player_snake->getPositions()[0].x > fruits[0]->getPositions()[0].x)) {
				west = true;
			}
			if ((player_snake->getPositions()[0].y < fruits[0]->getPositions()[0].y)) {
				south = true;
			}
			if ((player_snake->getPositions()[0].y > fruits[0]->getPositions()[0].y)) {
				north = true;
			}
			switch (turn % 5) {
			case 0:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
			case 1:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
			case 2:
				if (north and B[3]) {
					return DrtN();
				}
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
			case 3:
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
			case 4:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}


			}
		}
		if (my_Distance2 <= enemy_Distance2) {
			bool east{ false };
			bool west{ false };
			bool south{ false };
			bool north{ false };
			if ((player_snake->getPositions()[0].x - fruits[1]->getPositions()[0].x) < 0) {
				east = true;
			}
			if ((player_snake->getPositions()[0].x - fruits[1]->getPositions()[0].x) > 0) {
				west = true;
			}
			if ((player_snake->getPositions()[0].y - fruits[1]->getPositions()[0].y) < 0) {
				south = true;
			}
			if ((player_snake->getPositions()[0].y - fruits[1]->getPositions()[0].y) > 0) {
				north = true;
			}

			switch (turn % 5) {
			case 0:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
			case 1:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
			case 2:
				if (north and B[3]) {
					return DrtN();
				}
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
			case 3:
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
			case 4:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}


			}
		}
		if (true) {
			bool east{ false };
			bool west{ false };
			bool north{ false };
			bool south{ false };
			if ((player_snake->getPositions()[0].x < 6)) {
				east = true;
			}
			if ((player_snake->getPositions()[0].x > 6)) {
				west = true;
			}
			if ((player_snake->getPositions()[0].y < 7)) {
				south = true;
			}
			if ((player_snake->getPositions()[0].y > 7)) {
				north = true;
			}

			switch (turn % 5) {
			case 0:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
			case 1:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
			case 2:
				if (north and B[3]) {
					return DrtN();
				}
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
			case 3:
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
			case 4:
				if (east and B[0]) {
					return DrtE();
				}
				if (west and B[1]) {
					return DrtW();
				}
				if (south and B[2]) {
					return DrtS();
				}
				if (north and B[3]) {
					return DrtN();
				}

			}
		}
		//갈수있는 길

		if (B[1] and int(player_snake->getDirection().dx) != 1) {
			return DrtW();
		}
		if (B[0] and int(player_snake->getDirection().dx) != -1) {
			return DrtE();
		}
		if (B[2] and int(player_snake->getDirection().dy) !=-1) { 
			return DrtS();
		}
		if (B[3] and int(player_snake->getDirection().dy) != -1) {
			return DrtN();
		}
		B[0] = B[1] = B[2] = B[3] = true;
		if (true) {
			if (player_snake->getPositions()[0].x == 14) {
				B[0] = false;
			}
			if (player_snake->getPositions()[0].x == 0) {
				B[1] = false; // x가 0이면 왼쪽(W) 못감
			}
			if (player_snake->getPositions()[0].y == 14) {
				B[2] = false; // y가 14면 아래쪽(S) 못감
			}
			if (player_snake->getPositions()[0].y == 0) {
				B[3] = false; // y가 0이면 위쪽(N) 못감
			}
			// 부딪히지 말자
			// 상대랑 부딪힘
			for (int i = 0; i < int(enemy_snake->getPositions().size()); i++) {
				if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x - 1 and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y) {
					B[0] = false;
				}
				if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x + 1 and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y) {
					B[1] = false;
				}
				if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y - 1) {
					B[2] = false;//아래
				}
				if (player_snake->getPositions()[0].x == enemy_snake->getPositions()[i].x and player_snake->getPositions()[0].y == enemy_snake->getPositions()[i].y + 1) {
					B[3] = false;//위
				}
			}

			//자기 목이랑 부딪힘
			for (int i = 1; i < int(player_snake->getPositions().size()); i++) {
				if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x - 1 and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y) {
					B[0] = false;
				}
				if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x + 1 and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y) {
					B[1] = false;
				}
				if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y - 1) {
					B[2] = false;
				}
				if (player_snake->getPositions()[0].x == player_snake->getPositions()[i].x and player_snake->getPositions()[0].y == player_snake->getPositions()[i].y + 1) {
					B[3] = false;
				}
			}
			if (player_snake->getDirection().dx == 1) {
				B[1] = false;
			}
			if (player_snake->getDirection().dx == -1) {
				B[0] = false;
			}
			if (player_snake->getDirection().dy == 1) {
				B[3] = false;
			}
			if (player_snake->getDirection().dy == -1) {
				B[2] = false;
			}
		}
		if (B[1] and int(player_snake->getDirection().dx) != 1) {
			return DrtW();
		}
		if (B[0] and int(player_snake->getDirection().dx) != -1) {
			return DrtE();
		}
		if (B[2] and int(player_snake->getDirection().dy) != -1) {
			return DrtS();
		}
		if (B[3] and int(player_snake->getDirection().dy) != -1) {
			return DrtN();
		}
		return DrtN();

		/*
	Direction MyPlayer::selectDirection(
		int turn, Snake* player_snake, Snake* enemy_snake, std::vector<Fruit*> fruits){

	}
	*/
	}
}