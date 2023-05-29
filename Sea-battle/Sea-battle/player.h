#pragma once

#include "defines.h"
using namespace std;

struct Player {

	int x = 0; // ��������� ����
	int temp_x = 0;
	
	int y = 0; // ��������� ����
	int temp_y = 0;

	int dir = 0; // �����������
	int temp_dir = dir;

	int map_player[N][N] = { 0 }; // ���� ������

	int mask_player[N][N] = { 0 };// ����� ����� ������

	int ships_player[Num_Ships + 1] = { 0 }; // ������� ������

	int semm_player = 0; // �������� �� � ������ �������

	bool player = 1; // ������� �� �����

	bool win_player = 0; // �������� �� ������ �������

	string  gamer_name;
};