#if !defined(_PLAYER_H__)
#define _PLAYER_H__

#include "defs.h"
#include "turn.h"

class gm_brd;
class gm_mst;

/**
  * This enum is used to give us information about the field or a move. Notice that pc_free is not required when we 
  * describe a move, so assertion, disallowing it, is required each time we check it.
  */
enum plr_clr : char
{
	pc_free,
	pc_wht,
	pc_blc,
};

/**
  *	This class is an abstraction of the players. The player may be both a computer or a human.
  */
class player
{
public:
	player(gm_mst &, plr_clr );

/**
  *	This virtual method represents the main interface for the human and cumputer players.
  *	It is called when the caller asks the player to move and the player starts 'thinking'.
  */
	virtual void mk_mv(/*in*/ gm_brd &, /*in*/ time_t ) = 0;
	plr_clr get_clr();

protected:
	gm_mst &ownr_;
	plr_clr clr_;
};

/* inlines */

inline plr_clr player::get_clr()
{
	return clr_;
}

#endif //_PLAYER_H__

