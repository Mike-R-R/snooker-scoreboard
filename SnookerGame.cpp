
#include "SnookerGame.h"


/**
 * Default constructor for a game of snooker
 */
SnookerGame::SnookerGame(){
    player1 = new Player(true);
    player2 = new Player(false);
    reds = 15;
    pointsOnTable = 147;
}

/**
 * Constructor for a game of snooker where p1 and p2 are
 *  true if the player is breaking and false if not.
 */
SnookerGame::SnookerGame(bool p1, bool p2){
    player1 = new Player(p1);
    player2 = new Player(p2);
    reds = 15;
    pointsOnTable = 147;
}

/**
 * Default destructor
 */
SnookerGame::~SnookerGame(){

}

/**
 * Copy assignment for a game of snooker
 */
SnookerGame& SnookerGame::operator= (const SnookerGame& g) {
    this->player1 = g.player1;
    this->player2 = g.player2;
    this->reds = g.reds;
    return *this;
}

int SnookerGame::remaining_reds(){
    return reds;
}


int SnookerGame::remaining_points(){
	return pointsOnTable;
}

/**
 * Returns the players scores in an array where the
 *  first integer is player 1 and the second is
 *  player 2
 */
void SnookerGame::get_player_scores(int * scores){
    *scores = player1->get_score();
    *(scores + 1) = player2->get_score();
}


/**
 * Returns the players breaks in an array where the
 *  first integer is player 1 and the second is
 *  player 2
 */
void SnookerGame::get_player_breaks(int * breaks){
    *breaks = player1->get_current_break();
    *(breaks + 1) = player2->get_current_break();
}


/**
 * Returns the spread of points between players where
 *  the first integer is player 1 spread and the
 *  second is player 2
 */
void SnookerGame::point_spread(int * arr){
    int scores[2];
    get_player_scores(scores);
    
    *arr = scores[0] - scores[1];
    *(arr + 1) = *arr * (-1);
}


/**
 * Player potted a ball
 */
void SnookerGame::potted_ball(int points){
	Player* playerAtTable = player_at_table();
	bool valid_shot = false
	
	switch(points){
		case 1:
			if(reds > 0){
				valid_shot = true;
				reds--;
			}
			break;
		case 2:
			if(pointsOnTable == 27){
				valid_shot = true;
			}
			break;
		case 3:
			if(pointsOnTable == 25){
				valid_shot = true;
			}
			break;
		case 4:
			if(pointsOnTable == 22){
				valid_shot = true;
			}
			break;
		case 5:
			if(pointsOnTable == 18){
				valid_shot = true;
			}
			break;
		case 6:
			if(pointsOnTable == 13){
				valid_shot = true;
			}
			break;
		case 7:
			if(pointsOnTable == 7){
				valid_shot = true;
			}
			break;
	}
	
	if(points > 1 && !playerAtTable->get_on_red()){
		valid_shot = true;
	}
	
	if(valid_shot && reds == 0){
		playerAtTable->ball_potted(points);
		playerAtTable->set_on_red(false);
		pointsOnTable -= points;
	} else if (valid_shot){
		playerAtTable->ball_potted(points);
		pointsOnTable -= points;
	}
}


/*
 * Add foul points to the player not at the table
 */
void SnookerGame::foul(int points)
{
	Player* playerAtTable = player_at_table();
	Player* playerNotAtTable = player_not_at_table();
	
	playerNotAtTable->add_points(points);
	playerAtTable->end_break();
	playerNotAtTable->begin_break();
}


/**
 * Shooting player made a free ball
 */
void SnookerGame::free_ball()
{
	Player* playerAtTable = player_at_table();

    playerAtTable->add_points(1);
    playerAtTable->set_on_red(false);
}


/**
 * This function awards a frame to the player with the
 *  highest score and resets for the next frame
 */
void SnookerGame::end_frame()
{
    int scores[2];
    get_player_scores(scores);
    
    if(scores[0] > scores[1])
    {
        player1->won_frame();
        player2->lost_frame();
    }
    else
    {
        player2->won_frame();
        player1->lost_frame();
    }
    
    reds = 15;
    pointsOnTable = 147;
}


/**
 * This function ends the break of the player at the
 *  table and begins the next players break
 */
void SnookerGame::end_break()
{
	Player* playerAtTable = player_at_table();
	Player* playerNotAtTable = player_not_at_table();
	
	playerAtTable->end_break();
	playerNotAtTable->begin_break();
}


/**
 * This function accounts for a red lost during the
 *  course of play
 */
void SnookerGame::lost_red()
{
    reds--;
    pointsOnTable -= 8;
}


/**
 * Gets the player at the table and returns a 1 for player
 *  1 and a 2 for player 2.
 */
int SnookerGame::shooting_player(){
	if(player1->get_player_at_table())
    {
        return 1;
    }
    else
    {
        return 2;
    }
}


bool SnookerGame::player_shooting_red(){
	return player_at_table()->get_on_red();
}


/**
 * Private helper method to get player at table.
 */
Player* SnookerGame::player_at_table(){
	 if(player1->get_player_at_table())
    {
        return player1;
    }
    else
    {
        return player2;
    }
}


/**
 * Private helper method to get player not at table.
 */
Player* SnookerGame::player_not_at_table(){
	 if(player1->get_player_at_table())
    {
        return player2;
    }
    else
    {
        return player1;
    }
}

