#pragma once

#include "defines.h"
using namespace std;

struct Player {

	int x = 0; // кординаты цели
	int temp_x = 0;
	
	int y = 0; // кординаты цели
	int temp_y = 0;

	int dir = 0; // направление
	int temp_dir = dir;

	int map_player[N][N] = { 0 }; // поле игрока

	int mask_player[N][N] = { 0 };// туман войны игрока

	int ships_player[Num_Ships + 1] = { 0 }; // коробли игрока

	int semm_player = 0; // остались ли у игрока корабли

	bool player = 1; // выйграл ли игрок

	bool win_player = 0; // остались ли игрока корабли

	string  gamer_name;
};