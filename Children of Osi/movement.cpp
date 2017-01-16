#pragma comment(lib, "user32.lib")
#include "common.h"
#include "Player.h"
#include <Windows.h>

using namespace std;

void movePlayer(Player player) {
	if (GetAsyncKeyState(VK_UP)) {
		player.shiftY(-.01);
		cout << "\nX: " << player.getX() << " Y: " << player.getY();
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		player.shiftY(.1);
		cout << "\nX: " << player.getX() << " Y: " << player.getY();
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		player.shiftX(-.1);
		cout << "\nX: " << player.getX() << " Y: " << player.getY();
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		player.shiftX(.1);
		cout << "\nX: " << player.getX() << " Y: " << player.getY();
	}
}
