
#ifndef SNOOKER_QUEUE
#define SNOOKER_QUEUE

#include <stack>

struct GameState{
	int p1Points;
	int p2Points;
	int pointsOnTable;
	int reds;
	int shootingPlayer;
	bool onRed;
	bool foul;
	bool freeBall;
};

class SnookerStack{
	public:
		SnookerStack();
		~SnookerStack();
		void add_new_state(GameState);
		void add_new_state(int,int,int,int,int,bool,bool,bool);
		GameState* previous_game_state();
	
	private:
		std::stack<GameState> gameStack;

};

#endif
