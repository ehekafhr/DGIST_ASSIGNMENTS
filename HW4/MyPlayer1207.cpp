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

	// ---------------- ���� ���� ----------------
	/// ���#####
	/// 1. �������̳� ��ġ, ����, ��ǥ ���� ���� ��� Ŭ���� Pos�� �ǹ��Ѵ�.
	/// 2. �����̴� SnakeŬ������ ���Ѵ�. ���⼭�� player_snake�� enemy_snake�� �ִ�.
	/// 3. ������ Fruit Ŭ������ ���Ѵ�.
	/// 4. �Ӹ��� Snake ������Ʈ�� �Ӹ��� �ǹ��Ѵ�.
	/// �Ӹ���ġ�� ������ ��ü�� ���� ��ġ�� ���Ѵ�. ��, getPositions()[0]�� �ǹ��Ѵ�.
	/// player_snake�� �� ������, enemy_snake�� �� �����̸� �ǹ��ϸ�, 
	/// myHeadPos�� �� �������� �Ӹ� ��ǥ�� ������, 
	/// myPos, enemyPos�� ���� ���� ���� �������� ��ġ�� ���� ���� �����̳ʸ� ���Ѵ�.
	/// ��� ��###

	// Your function to primarily implement
	Direction MyPlayer2::selectDirection(
		int turn, Snake* player_snake, Snake* enemy_snake,
		std::vector<Fruit*> fruits) {

		/// ## Plan3 ##///////////////////////////////
		/// ���� BFS�Ͽ� ���� ����� ���ϱ��� ��θ� ã�´�.
		/// ��ο� ���ԵǴ� ������ �����Ѵ�.
		/// ####//////////////////////////////////////
		
		return findDirection(*player_snake, *enemy_snake, fruits);

	}

	// ���� ������ ������ ã�´�.
	Direction MyPlayer2::findDirection(const Snake& player_snake, const Snake& enemy_snake,
		const std::vector<Fruit*> fruits) {

		Direction resultDrt;
		
		// findPath()�Լ��� �Ӹ����� ���ϱ����� ��θ� ����� �����Ѵ�.
		std::vector<Pos> reversed_path = findPath(player_snake, enemy_snake, fruits);

		// ���� reversed_path�� ����ٸ�, ������ ã�� ���ߴٴ� ���̴�.(�Ӹ��� ���� ���� ���̶�� ��.)
		if (reversed_path.empty() == true) {
			// ��ֹ��� �������� ���� �����δ�.
			resultDrt = follow_right_obstacle(player_snake, enemy_snake);
		}
		// ���� reversed_path�� ������� �ʴٸ�, ������ ã�µ� �����ߴٴ� ���̴�.
		else {
			// ���� ��� ����� 1�� ��ΰ� ���ϵǴ� ����?
			if (reversed_path.size() == 1) {
				return DrtN();
			}
			// ����� �������� �Ӹ��̰�, �� �ε����� size - 1�̴�.
			// �ε����� size - 2�� ��ġ�� �Ӹ� �ٷ� ���� �����̴�. ���� ���� �Ͽ� �� ������ �Ӹ��� �ű⿡ �ִ�.
			Pos destination = reversed_path.at(reversed_path.size() - 2);	// ���� ���� ��������.
			Pos myHeadPos = player_snake.getPositions()[0];

			// ������ ��ġ�� ���� �Ӹ� ��ġ�� ���� ������ ���Ѵ�.
			resultDrt.dx = destination.x - myHeadPos.x;
			resultDrt.dy = destination.y - myHeadPos.y;
		}

		return resultDrt;
	}

	// ��ֹ��� �������� ���󰡴� ������ �����Ѵ�.
	Direction MyPlayer2::follow_right_obstacle(const Snake& player_snake, const Snake& enemy_snake) {
		std::vector<Pos> myPos = player_snake.getPositions();
		std::vector<Pos> enemyPos = enemy_snake.getPositions();
		Direction currentDrt = player_snake.getDirection();

		// ���� �Ӹ� ������ �������� ���Ѵ�.
		Direction rightDrt = getRightDrt(currentDrt);

		// �ִ� 3���� ������ �˻��Ѵ�.		myPos[0]�� �Ӹ��� ��ǥ�̴�.
		if (is_safePos(myPos, enemyPos, myPos[0] + rightDrt) == true) return rightDrt;
		if (is_safePos(myPos, enemyPos, myPos[0] + currentDrt) == true) return currentDrt;
		// ������ ������ �ι� ���ؼ� leftDrt�� ��´�. ������ �Լ��� �������� �ʱ� ����.
		Direction backDrt = getRightDrt(rightDrt);
		Direction leftDrt = getRightDrt(backDrt);
		if (is_safePos(myPos, enemyPos, myPos[0] + leftDrt) == true) return leftDrt;

		// ���� ���ǹ� ��ġ�� �����Դٸ�, ������ ������ ���ٴ� ���̴�. �ƹ� �����̳� ���ؼ� �״´�.
		// Keep calm and die.
		return DrtE(); // I like east.
	}

	// �Էµ� ������ ������ ������ �����Ѵ�.
	Direction MyPlayer2::getRightDrt(const Direction& currentDrt) {
		// if�� ����� ����ؼ� �����ߴ�.
		if (currentDrt == DrtN())		return DrtE();
		else if (currentDrt == DrtW())	return DrtN();
		else if (currentDrt == DrtS())	return DrtW();
		else							return DrtS();
	}

	// �Էµ� ��ġ�� �� �׸��� �����̿� ��ġ�� �ʴ�(������) ��ġ���� �Ǵ��Ѵ�.
	// �����ϸ� true, �����ϸ�(���̳� �����̿��� �����ٸ�) false�� �����Ѵ�.
	bool MyPlayer2::is_safePos(const std::vector<Pos>& myPos, const std::vector<Pos>& enemyPos, const Pos& pos) {
		
		// boundary check, �� �˻�.
		if (pos.x < 0) return false;
		if (pos.y < 0) return false;
		if (pos.x >= MAPSIZE) return false;
		if (pos.y >= MAPSIZE) return false;

		// snake check, ������ �˻�
		for (auto& posSnake : myPos) {
			// ������ ��ġ posSnake�� �μ� pos�� ������ �˻��Ѵ�.
			// ���� ���ٸ� false�� �����Ѵ�.
			if (pos == posSnake) return false;
		}
		for (auto& posSnake : enemyPos) {
			// �� �����̿� �̾, �� �����̵� �˻��Ѵ�.
			if (pos == posSnake) return false;
		}

		// ��� �˻� ������ �����ϸ� true�� �����Ѵ�.
		return true;
	}

	
	// BFS�� �����Ͽ� �Ӹ����� ���ϱ����� ��θ� ã�� �� �����Ѵ�.
	// ã�� ���Ѵٸ� �Լ� follow_right_obstacle�� �����Ͽ� ������ ��ֹ��� ���󰣴�.
	std::vector<Pos> MyPlayer2::findPath(const Snake& player_snake, const Snake& enemy_snake,
		const std::vector<Fruit*> fruits) {
		std::vector<Pos> myPos = player_snake.getPositions();
		std::vector<Pos> enemyPos = enemy_snake.getPositions();

		std::vector<Pos> reversed_path;


		// ���� ���ؼ� ����� +2�Ѵ�.
		bool is_accessible[MAP_SIZE + 2][MAP_SIZE + 2];

		// befoPos�� ������ �ʿ�����Ƿ� MAPSIZE * MAPSIZE �������� ���߹迭�� ����Ѵ�.
		Pos befoPos[MAP_SIZE][MAP_SIZE];

		// �ڷᱸ�� queue�� ����Ѵ�.
		std::queue<Pos> q;


		// ---------------- is_accessible �ʱ�ȭ ����. ----------------
		// ȿ�������� �ʾƺ��δ�. ���� �� ����.

		// �� �ܺδ� ���ٺҰ��� �����Ѵ�. (������)W �κ�
		// �� ���δ� ���ٰ������� �����Ѵ�. 0 �κ�.
		/* ��  MAPSIZE  ��
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

				// �� ���� �˻�
				if ((i == 0) || (j == 0) || (i == MAPSIZE + 1) || (j == MAPSIZE + 1)) {
					is_accessible[i][j] = false;	// ���̸� ���� �Ұ�
				}
				else {
					is_accessible[i][j] = true;		// ���� �ƴϸ� ���� ����.
				}
			}
		}

		// ������ ��ġ�� ���ٺҰ��� �����Ѵ�.
		// ��ǥ�� x+1, y+1�ؼ� �ε����� ����Ѵ�.
		for (auto& posSnake : myPos) {
			is_accessible[posSnake.x + 1][posSnake.y + 1] = false;
		}
		for (auto& posSnake : enemyPos) {
			is_accessible[posSnake.x + 1][posSnake.y + 1] = false;
		}
		// ---------------- is_accessible �ʱ�ȭ �� ----------------
		
		// ---------------- befoPos �ʱ�ȭ ���� ----------------
		// ---------------- befoPos �ʱ�ȭ �� ----------------
		Pos myHeadPos = myPos[0];
		Pos curPos;
		
		// �Ӹ��� befoPos�� Pos(-1, -1)�� �����Ѵ�.
		// ��θ� ���ϴ� ������ ������������ �ϱ� �����̴�.
		befoPos[myHeadPos.x][myHeadPos.y] = Pos(-1, -1);
		// ����
		is_accessible[myHeadPos.x + 1][myHeadPos.y + 1] = false;


		// �Ӹ� ��ġ�� ť�� �ִ´�.
		q.push(myHeadPos);
		// ���� Ž�� ���� ���θ� �����ϴ� ����.
		bool success = false;

		// ���� ��ġ ����
		Pos posFruit1 = fruits[0]->getPositions()[0];
		Pos posFruit2 = fruits[1]->getPositions()[0];

		// BFS ��ü �κ��̴�.
		while (q.empty() != true) {
			
			// ť���� �ϳ� ���� ���� ��ġ�� �����Ѵ�.
			curPos = q.front();
			q.pop();		// �� �� ����� ��ġ�� ť���� ������.

			// ���� ���� ��ġ�� �����̶�� ���� ���θ� ����ϰ� ������ �����Ѵ�.
			if ((curPos == posFruit1) || (curPos == posFruit2)) {
				success = true;
				break;
			}

			// ���� ��ġ�� �̿����� ���ٰ��ɼ��� �˻��Ѵ�.
			for (auto nei : neibors(curPos)) {

				// ���� ���ٰ����� �̿��̶�� ť�� �ְ� ���ٺҰ��� �ٲ۴�.
				// �׸��� �� �̿��� befoPos�� curPos�� �����Ѵ�.
				if (is_accessible[nei.x + 1][nei.y + 1] == true) {
					q.push(nei);
					is_accessible[nei.x + 1][nei.y + 1] = false;
					befoPos[nei.x][nei.y] = curPos;
				}
			}
		} // end while

		// ���� Ž���� �����ϸ� curPos�� ���� ��ġ�� ����.
		if (success == true) {
			reversed_path.push_back(curPos);	// ���� ��ġ�� ��ο� �ִ´�.

			// befoPos�� ���ͷ��̼��ϸ鼭 reversed_path�� �ִ´�.
			// ���������� �ռ��� �����, befoPos�� Pos(-1, -1)�� ���̴�. x���� �˻�.
			while ((befoPos[curPos.x][curPos.y]).x != -1) {
				reversed_path.push_back(befoPos[curPos.x][curPos.y]);
				curPos = befoPos[curPos.x][curPos.y];
			}
		}
		// ���� ���� Ž���� �����ߴٸ� �� ���� revered_path�� �����ؾ� �ϹǷ� �ƹ��͵� ���� �ʴ´�.
		else {
			// do nothing
		}

		return reversed_path;

	} // end func findPath()

	// �Էµ� ��ġ�μ��� �̿� ��ġ���� ���͸� �����Ѵ�.
	std::vector<Pos> MyPlayer2::neibors(const Pos& pos) {
		std::vector<Pos> new_vector;

		new_vector.push_back(pos + DrtN());
		new_vector.push_back(pos + DrtW());
		new_vector.push_back(pos + DrtS());
		new_vector.push_back(pos + DrtE());

		return new_vector;
	}
}
