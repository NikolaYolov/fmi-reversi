#if !defined(_GAME_BOARD_H__)
#define _GAME_BOARD_H__

#include <vector>

#include "defs.h"
#include "turn.h"
#include "player.h"

/**
  *	This class represents the state of the game in one.
  */
class gm_brd
{
/**
  *	This array is the main board.
  */
	std::vector<plr_clr> brd_;

public:
/**
  *	Constructor, initializing the size of the board.
  */
	gm_brd(/*in*/ index_t x_len, /*in*/ index_t y_wdt);

/**
  *	This method changes the board acording the given move.
  */
	void do_mv(/*in*/ move , /*in*/ plr_clr , /*out*/ gm_brd &) const;

/**
  *	This method returns true if the given move is valid and false otherwise.
  */
	bool vld_mv(/*in*/ move , /*in*/ plr_clr) const;

/**
  *	This method generates all moves for a given player
  */
	void gen_all_mvs(/*in*/ plr_clr , /*out*/ std::vector<move>& ) const;
};

#endif //_GAME_BOARD_H__

