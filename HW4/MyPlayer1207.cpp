////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "MyPlayer1207.h"

#include "Commons.h"
#include "Snake.h"
#include "Fruit.h"

#include <queue>
#include "config.h"

namespace snake_arena {
	// Constructor
	MyPlayer2::MyPlayer(int map_size) :
		Player(map_size) {
		MAPSIZE = map_size;
	}

	// Destructor
	MyPlayer2::~MyPlayer() {

	}

	// ---------------- 구현 시작 ----------------
	/// 용어#####
	/// 1. 포지션이나 위치, 지점, 좌표 등의 용어는 모두 클래스 Pos를 의미한다.
	/// 2. 지렁이는 Snake클래스를 뜻한다. 여기서는 player_snake와 enemy_snake가 있다.
	/// 3. 과일은 Fruit 클래스를 뜻한다.
	/// 4. 머리는 Snake 오브젝트의 머리를 의미한다.
	/// 머리위치는 지렁이 객체의 선두 위치를 뜻한다. 즉, getPositions()[0]를 의미한다.
	/// player_snake는 내 지렁이, enemy_snake는 적 지렁이를 의미하며, 
	/// myHeadPos는 내 지렁이의 머리 좌표의 변수명, 
	/// myPos, enemyPos는 각각 나와 적의 지렁이의 위치를 담은 벡터 컨테이너를 뜻한다.
	/// 용어 끝###

	// Your function to primarily implement
	Direction MyPlayer2::selectDirection(
		int turn, Snake* player_snake, Snake* enemy_snake,
		std::vector<Fruit*> fruits) {

		/// ## Plan3 ##///////////////////////////////
		/// 매턴 BFS하여 가장 가까운 과일까지 경로를 찾는다.
		/// 경로에 포함되는 방향을 리턴한다.
		/// ####//////////////////////////////////////
		
		return findDirection(*player_snake, *enemy_snake, fruits);

	}

	// 매턴 적절힌 방향을 찾는다.
	Direction MyPlayer2::findDirection(const Snake& player_snake, const Snake& enemy_snake,
		const std::vector<Fruit*> fruits) {

		Direction resultDrt;
		
		// findPath()함수는 머리에서 과일까지의 경로를 뒤집어서 리턴한다.
		std::vector<Pos> reversed_path = findPath(player_snake, enemy_snake, fruits);

		// 만약 reversed_path가 비었다면, 과일을 찾지 못했다는 뜻이다.(머리가 닫힌 공간 안이라는 뜻.)
		if (reversed_path.empty() == true) {
			// 장애물의 오른쪽을 따라서 움직인다.
			resultDrt = follow_right_obstacle(player_snake, enemy_snake);
		}
		// 만약 reversed_path가 비어있지 않다면, 과일을 찾는데 성공했다는 뜻이다.
		else {
			// 수정 어떻게 사이즈가 1인 경로가 리턴되는 거지?
			if (reversed_path.size() == 1) {
				return DrtN();
			}
			// 경로의 시작점은 머리이고, 그 인덱스는 size - 1이다.
			// 인덱스가 size - 2인 위치는 머리 바로 다음 지점이다. 따라서 다음 턴에 내 지렁이 머리는 거기에 있다.
			Pos destination = reversed_path.at(reversed_path.size() - 2);	// 벡터 범위 에러난다.
			Pos myHeadPos = player_snake.getPositions()[0];

			// 목적지 위치에 현재 머리 위치를 빼서 방향을 구한다.
			resultDrt.dx = destination.x - myHeadPos.x;
			resultDrt.dy = destination.y - myHeadPos.y;
		}

		return resultDrt;
	}

	// 장애물의 오른쪽을 따라가는 방향을 리턴한다.
	Direction MyPlayer2::follow_right_obstacle(const Snake& player_snake, const Snake& enemy_snake) {
		std::vector<Pos> myPos = player_snake.getPositions();
		std::vector<Pos> enemyPos = enemy_snake.getPositions();
		Direction currentDrt = player_snake.getDirection();

		// 현재 머리 방향의 오른쪽을 구한다.
		Direction rightDrt = getRightDrt(currentDrt);

		// 최대 3개의 방향을 검사한다.		myPos[0]는 머리의 좌표이다.
		if (is_safePos(myPos, enemyPos, myPos[0] + rightDrt) == true) return rightDrt;
		if (is_safePos(myPos, enemyPos, myPos[0] + currentDrt) == true) return currentDrt;
		// 오른쪽 방향을 두번 구해서 leftDrt를 얻는다. 별도의 함수를 구현하지 않기 위함.
		Direction backDrt = getRightDrt(rightDrt);
		Direction leftDrt = getRightDrt(backDrt);
		if (is_safePos(myPos, enemyPos, myPos[0] + leftDrt) == true) return leftDrt;

		// 위의 조건문 뭉치를 지나왔다면, 안전한 방향이 없다는 뜻이다. 아무 방향이나 택해서 죽는다.
		// Keep calm and die.
		return DrtE(); // I like east.
	}

	// 입력된 방향의 오른쪽 방향을 리턴한다.
	Direction MyPlayer2::getRightDrt(const Direction& currentDrt) {
		// if문 덩어리를 사용해서 구현했다.
		if (currentDrt == DrtN())		return DrtE();
		else if (currentDrt == DrtW())	return DrtN();
		else if (currentDrt == DrtS())	return DrtW();
		else							return DrtS();
	}

	// 입력된 위치가 벽 그리고 지렁이와 겹치지 않는(안전한) 위치인지 판단한다.
	// 안전하면 true, 위험하면(벽이나 지렁이에게 막혔다면) false를 리턴한다.
	bool MyPlayer2::is_safePos(const std::vector<Pos>& myPos, const std::vector<Pos>& enemyPos, const Pos& pos) {
		
		// boundary check, 벽 검사.
		if (pos.x < 0) return false;
		if (pos.y < 0) return false;
		if (pos.x >= MAPSIZE) return false;
		if (pos.y >= MAPSIZE) return false;

		// snake check, 지렁이 검사
		for (auto& posSnake : myPos) {
			// 지렁이 위치 posSnake와 인수 pos가 같은지 검사한다.
			// 만약 같다면 false를 리턴한다.
			if (pos == posSnake) return false;
		}
		for (auto& posSnake : enemyPos) {
			// 내 지렁이에 이어서, 적 지렁이도 검사한다.
			if (pos == posSnake) return false;
		}

		// 모든 검사 조건을 충족하면 true를 리턴한다.
		return true;
	}

	
	// BFS를 시행하여 머리에서 과일까지의 경로를 찾고 또 리턴한다.
	// 찾지 못한다면 함수 follow_right_obstacle를 실행하여 오른쪽 장애물을 따라간다.
	std::vector<Pos> MyPlayer2::findPath(const Snake& player_snake, const Snake& enemy_snake,
		const std::vector<Fruit*> fruits) {
		std::vector<Pos> myPos = player_snake.getPositions();
		std::vector<Pos> enemyPos = enemy_snake.getPositions();

		std::vector<Pos> reversed_path;


		// 벽을 위해서 사이즈를 +2한다.
		bool is_accessible[MAP_SIZE + 2][MAP_SIZE + 2];

		// befoPos는 벽설정 필요없으므로 MAPSIZE * MAPSIZE 사이즈의 이중배열을 사용한다.
		Pos befoPos[MAP_SIZE][MAP_SIZE];

		// 자료구조 queue를 사용한다.
		std::queue<Pos> q;


		// ---------------- is_accessible 초기화 과정. ----------------
		// 효율적이지 않아보인다. 느릴 것 같다.

		// 맵 외부는 접근불가로 설정한다. (벽설정)W 부분
		// 맵 내부는 접근가능으로 설정한다. 0 부분.
		/* ┌  MAPSIZE  ┐
		  0 1 2 3 4 ~~~ M M+
		0 W W W W W W W W W
		1 W 0 0 0 0 0 ~ 0 W
		2 W 0 0 0 0 0 ~ 0 W 
		3 W 0 0 0 0 0 ~ 0 W 
		4 W 0 0 0 0 0 ~ 0 W
		~ W 0 0 0 0 0 0 0 W
		~ W 0 0 0 0 0 0 0 W
		~ W 0 0 0 0 0 0 0 W
		M W 0 0 0 0 0 0 0 W   
	   M+ W W W W W W W W W
	   */

		// i = 0 to MAPSIZE+1
		for (int i = 0; i < MAPSIZE + 2; ++i) {
			for (int j = 0; j < MAPSIZE + 2; ++j) {

				// 벽 조건 검사
				if ((i == 0) || (j == 0) || (i == MAPSIZE + 1) || (j == MAPSIZE + 1)) {
					is_accessible[i][j] = false;	// 벽이면 접근 불가
				}
				else {
					is_accessible[i][j] = true;		// 벽이 아니면 접근 가능.
				}
			}
		}

		// 지렁이 위치를 접근불가로 설정한다.
		// 좌표에 x+1, y+1해서 인덱스를 사용한다.
		for (auto& posSnake : myPos) {
			is_accessible[posSnake.x + 1][posSnake.y + 1] = false;
		}
		for (auto& posSnake : enemyPos) {
			is_accessible[posSnake.x + 1][posSnake.y + 1] = false;
		}
		// ---------------- is_accessible 초기화 끝 ----------------
		
		// ---------------- befoPos 초기화 시작 ----------------
		// ---------------- befoPos 초기화 끝 ----------------
		Pos myHeadPos = myPos[0];
		Pos curPos;
		
		// 머리의 befoPos를 Pos(-1, -1)로 설정한다.
		// 경로를 구하는 루프의 종료조건으로 하기 위함이다.
		befoPos[myHeadPos.x][myHeadPos.y] = Pos(-1, -1);
		// 수정
		is_accessible[myHeadPos.x + 1][myHeadPos.y + 1] = false;


		// 머리 위치를 큐에 넣는다.
		q.push(myHeadPos);
		// 과일 탐색 성공 여부를 저장하는 변수.
		bool success = false;

		// 과일 위치 저장
		Pos posFruit1 = fruits[0]->getPositions()[0];
		Pos posFruit2 = fruits[1]->getPositions()[0];

		// BFS 본체 부분이다.
		while (q.empty() != true) {
			
			// 큐에서 하나 빼서 현재 위치로 지정한다.
			curPos = q.front();
			q.pop();		// 한 번 사용한 위치는 큐에서 버린다.

			// 만약 현재 위치가 과일이라면 성공 여부를 기록하고 루프를 종료한다.
			if ((curPos == posFruit1) || (curPos == posFruit2)) {
				success = true;
				break;
			}

			// 현재 위치의 이웃들의 접근가능성을 검사한다.
			for (auto nei : neibors(curPos)) {

				// 만약 접근가능한 이웃이라면 큐에 넣고 접근불가로 바꾼다.
				// 그리고 그 이웃의 befoPos를 curPos로 설정한다.
				if (is_accessible[nei.x + 1][nei.y + 1] == true) {
					q.push(nei);
					is_accessible[nei.x + 1][nei.y + 1] = false;
					befoPos[nei.x][nei.y] = curPos;
				}
			}
		} // end while

		// 과일 탐색이 성공하면 curPos는 과일 위치와 같다.
		if (success == true) {
			reversed_path.push_back(curPos);	// 과일 위치를 경로에 넣는다.

			// befoPos를 이터레이션하면서 reversed_path에 넣는다.
			// 종료조건은 앞서서 언급한, befoPos가 Pos(-1, -1)일 때이다. x값만 검사.
			while ((befoPos[curPos.x][curPos.y]).x != -1) {
				reversed_path.push_back(befoPos[curPos.x][curPos.y]);
				curPos = befoPos[curPos.x][curPos.y];
			}
		}
		// 만약 과일 탐색에 실패했다면 빈 벡터 revered_path를 리턴해야 하므로 아무것도 하지 않는다.
		else {
			// do nothing
		}

		return reversed_path;

	} // end func findPath()

	// 입력된 위치인수의 이웃 위치들의 벡터를 리턴한다.
	std::vector<Pos> MyPlayer2::neibors(const Pos& pos) {
		std::vector<Pos> new_vector;

		new_vector.push_back(pos + DrtN());
		new_vector.push_back(pos + DrtW());
		new_vector.push_back(pos + DrtS());
		new_vector.push_back(pos + DrtE());

		return new_vector;
	}
}
