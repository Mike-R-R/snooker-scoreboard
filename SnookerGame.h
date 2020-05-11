
#ifndef SNOOKER_GAME
#define SNOOKER_GAME

#include "Player.h"

class SnookerGame {
    public:
        SnookerGame();
        SnookerGame(bool, bool);
        ~SnookerGame();
        SnookerGame& operator= (const SnookerGame& g);
        int remaining_reds();
        int remaining_points();
        void get_player_scores(int *);
        void get_player_breaks(int *);
        int point_spread();
        void receive_point_input(int);
	bool player_fouled();
	void foul_occurred();
        void add_foul_points(int);
        void free_ball();
        void end_frame();
        void end_break();
        void lost_red();
        int shooting_player();
        bool player_shooting_red();
        
	private:
		Player* player1;
		Player* player2;
		int reds;
		int pointsOnTable;
		bool freeBall;
		bool foul;
		
		Player* player_at_table();
		Player* player_not_at_table();
};

#endif
