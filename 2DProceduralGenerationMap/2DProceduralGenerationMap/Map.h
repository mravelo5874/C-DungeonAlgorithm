#pragma once
#include <iostream>
using namespace std;

class Map
{
private:
	int width;
	int height;
	int ** Tiles;

public:
	Map(int w, int h)
	{
		width = w;
		height = h;

		Tiles = new int * [height];
		for (int i = 0; i < height; i++) {
			Tiles[i] = new int[width];
		}

		reset();
	}

	Map()
	{
	}

	~Map()
	{
		for (int i = 0; i < height; i++) {
			delete[] Tiles[i];
		}
		delete[] Tiles;
	}

	void draw()
	{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (Tiles[i][j] == 1) {
					cout << "X";
				}
				else {
					cout << " ";
				}
			}
			cout << endl; // new line 
		}
	}

	void add(int y, int x, int i)
	{
		if (y >= height)
			y = y - height;
		if (x >= width)
			x = x - width;
		if (y < 0)
			y = y + height;
		if (x < 0)
			x = x + width;
		Tiles[y][x] = i;
	}

	int h()
	{
		return height;
	}

	int w()
	{
		return width;
	}

	void reset()
	{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Tiles[i][j] = 1;
			}
		}
	}

};
