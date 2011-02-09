#if !defined(_HUMAN_PLAYER_H__)
#define _HUMAN_PLAYER_H__

#include "player.h"

/**
  * This class in the interface for the interface.
  */
class hmn_plr
	: public player
{
public:
	hmn_plr(gm_mst &, plr_clr );

/**
  * This method makes one move using the graphical interface.
  */
	virtual void mk_mv(const /*in*/ gm_brd &, /*in*/ time_t );

/**
  * This informs the game master that the human has make their move.
  */
	void do_mv(turn );
};

#endif //_HUMAN_PLAYER_H__

