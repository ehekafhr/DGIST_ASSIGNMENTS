#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "Commons.h"

#include <string>

#define MyPlayer2		Player201911047		// CHANGE THIS: Your StudentID 
#define PLAYER_NAME2		"baby snake :p"	// CHANGE THIS: Name your player

namespace snake_arena {
	class MyPlayer2 final : public Player {
	public:
		MyPlayer2(int map_size);
		virtual ~MyPlayer2() override;

		virtual std::string getName() const { return PLAYER_NAME2; }
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits);

	private:
		int MAPSIZE;

		Direction findDirection(const Snake& player_snake, const Snake& enemy_snake,
			const std::vector<Fruit*> fruits);
		Direction follow_right_obstacle(const Snake& player_snake, const Snake& enemy_snake);
		Direction getRightDrt(const Direction& currentDrt);
		bool is_safePos(const std::vector<Pos>& myPos, const std::vector<Pos>& enemyPos, const Pos& pos);
		std::vector<Pos> findPath(const Snake& player_snake, const Snake& enemy_snake,
			const std::vector<Fruit*> fruits);
		std::vector<Pos> neibors(const Pos& pos);
	};
	
}