#pragma once

class game
{
private:
	static game Game;

public:
	//Constructor
	game();

	// Delete assignment and copy constructors
	game(const game&) = delete;
	game& operator=(const game&) = delete;

	//Getter
	static game getGame();
};
