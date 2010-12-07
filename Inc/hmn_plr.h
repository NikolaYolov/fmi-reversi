#if !defined(_HUMAN_PLAYER_H__)
#define _HUMAN_PLAYER_H__

#include "player.h"

/**
  *	This class in the interface for the interface.
  */
class hmn_plr
	: public player
{

/**
  *	This method makes one move using the graphical interface.
  */
	virtual turn mk_mv(/*in*/ gm_brd &, /*in*/ time_t );
};

#endif //_HUMAN_PLAYER_H__

