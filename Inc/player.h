#if !defined(_PLAYER_H__)
#define _PLAYER_H__

#include "defs.h"
#include "turn.h"

class gm_brd;

/**
  * This enum is used to give us information about the field or a move. Notice that pc_free is not required when we 
  * describe a move, so assertion, disallowing it, is required each time we check it.
  */
enum plr_clr : char
{
	pc_white,
	pc_black,
	pc_free,
};

/**
  *	This class is an abstraction of the players. The player may be both a computer or a human.
  */
class player
{
/**
  *	This virtual method represents the main interface for the human and cumputer players.
  */
	virtual turn mk_mv(/*in*/ gm_brd &, /*in*/ time_t ) =0;
};

#endif //_PLAYER_H__
