#if !defined(_COMPUTER_PLAYER_H__)
#define _COMPUTER_PLAYER_H__

#include "player.h"

/**
  *	This class in the interface for the algorithms.
  */
class cmp_plr
	: public player
{
public:
	cmp_plr(gm_mst &, plr_clr );
/**
  *	This method makes one move using mix-max algorithm.
  */
	virtual void mk_mv(/*in*/ gm_brd &, /*in*/ time_t );
};

#endif //_COMPUTER_PLAYER_H__

