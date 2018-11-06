#pragma once
#include "Map.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

class Dungeon
{
private:
	Map * map;
	int rooms, roomMax, roomMin, corrMax, corrMin;

	// generates a number within a certain range
	int randomNumberRange(int min, int max)
	{
		int num = min + (rand() % (max - min + 1));
		return num;
	}

	// values to create rooms and corridors
	struct values
	{
		int topLx;
		int topLy;
		int botRx;
		int botRy;
	};

	values create_room(values val)
	{
		for (int i = val.topLy; i < val.botRy; i++) {
			for (int j = val.topLx; j < val.botRx; j++) {
				map->add(i, j, 0);
			}
		}

		return val;
	}

	values create_corridor(values val)
	{
		int dir = randomNumberRange(0, 3);
		values new_val;

		switch (dir)
		{
		case 0: { // north
			//cout << "north" << endl;
			int X = randomNumberRange(val.topLx + 1, val.botRx - 1);
			int startY = val.topLy;
			int corr_length = randomNumberRange(corrMin, corrMax);
			
			// draw corridor
			for (int i = 0; i < corr_length + roomMin; i++) {
				map->add(startY - i - 1, X, 0);
			}

			// generate new coords for next room
			int new_len = randomNumberRange(roomMin, roomMax);
			int new_hght = randomNumberRange(roomMin, roomMax);
			int entry_offset = randomNumberRange(0, new_len - 1);

			new_val = { X - entry_offset, startY - corr_length - new_hght, X - entry_offset + new_len, startY - corr_length };
			break;
		}
		case 1: { // east
			//cout << "east" << endl;
			int Y = randomNumberRange(val.topLy + 1, val.botRy - 1);
			int startX = val.botRx;
			int corr_length = randomNumberRange(corrMin, corrMax);

			// draw corridor
			for (int i = 0; i < corr_length + roomMin; i++) {
				map->add(Y, startX + i, 0);
			}

			// generate new coords for next room
			int new_len = randomNumberRange(roomMin, roomMax);
			int new_hght = randomNumberRange(roomMin, roomMax);
			int entry_offset = randomNumberRange(0, new_len - 1);

			new_val = { startX + corr_length, Y + entry_offset - new_hght, startX + corr_length + new_len, Y + entry_offset };
			break;
		}
		case 2: { // south
			//cout << "south" << endl;
			int X = randomNumberRange(val.topLx + 1, val.botRx - 1);
			int startY = val.botRy;
			int corr_length = randomNumberRange(corrMin, corrMax);

			// draw corridor
			for (int i = 0; i < corr_length + roomMin; i++) {
				map->add(startY + i, X, 0);
			}

			// generate new coords for next room
			int new_len = randomNumberRange(roomMin, roomMax);
			int new_hght = randomNumberRange(roomMin, roomMax);
			int entry_offset = randomNumberRange(0, new_len - 1);

			new_val = { X - entry_offset, startY + corr_length, X - entry_offset + new_len, startY + corr_length + new_hght };
			break;
		}
		case 3: { // west
			//cout << "west" << endl;
			int Y = randomNumberRange(val.topLy + 1, val.botRy - 1);
			int startX = val.topLx;
			int corr_length = randomNumberRange(corrMin, corrMax);

			// draw corridor
			for (int i = 0; i < corr_length + roomMin; i++) {
				map->add(Y, startX - i - 1, 0);
			}

			// generate new coords for next room
			int new_len = randomNumberRange(roomMin, roomMax);
			int new_hght = randomNumberRange(roomMin, roomMax);
			int entry_offset = randomNumberRange(0, new_len - 1);

			new_val = { startX - corr_length - new_len, Y + entry_offset - new_hght, startX - corr_length, Y + entry_offset };
			break;
		}
		}

		return new_val;
	}

public:
	Dungeon(Map * m, int num_rooms, int max_room_len, int min_room_len, int max_corr_len, int min_corr_len )
	{
		srand(time(NULL));
		map = m;
		rooms = num_rooms;
		roomMax = max_room_len;
		roomMin = min_room_len;
		corrMax = max_corr_len;
		corrMin = min_corr_len;
	}

	void generate()
	{
		map->reset();

		// choose start location
		int a = map->w() / 2 - randomNumberRange(roomMin, roomMax);
		int b = map->h() / 2 - randomNumberRange(roomMin, roomMax);
		int offset = randomNumberRange(roomMin, roomMax);
		values val = { a, b, a + offset, b + offset };

		// create rooms
		for (int i = 0; i < rooms; i++) {
			val = create_room(val);
			if (i != rooms - 1)
				val = create_corridor(val);
		}
	}
};
