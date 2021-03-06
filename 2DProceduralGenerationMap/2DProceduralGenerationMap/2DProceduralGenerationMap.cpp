#include "stdafx.h"
#include "Map.h"
#include "Dungeon.h"
#include <stdlib.h>
#include <string>


int main()
{
	cout << flush;
	system("CLS");

	Map Tilemap(100, 100);
	Dungeon dungeon(&Tilemap, 50, 10, 2, 10, 1);
	bool repeat = true;

	while (repeat) {
		dungeon.generate();
		Tilemap.draw();

		cout << "Enter any key to generate a new dungeon." << endl;
		cout << "Enter 'exit' to leave application." << endl;
		string input;
		cin >> input;
		if (input == "exit")
			repeat = false;
		cout << flush;
		system("CLS");
	}
	
    return 0;
}

