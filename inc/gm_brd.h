#if !defined(_GAME_BOARD_H__)
#define _GAME_BOARD_H__

#include <vector>

#include "defs.h"
#include "turn.h"
#include "player.h"


class opts;
/**
  *	This class represents the state of the game in one.
  */
class gm_brd
{
public:
/**
  *	Constructors, initializing the size of the board.
  */
	gm_brd();
	gm_brd(/*in*/ int x_len, /*in*/ int y_wdt);
	gm_brd(const opts& o);

/**
  *	This method changes the board acording the given move.
  */
	void do_mv(/*in*/ move , /*in*/ plr_clr );

/**
  *	This method returns true if the given move is valid and false otherwise.
  */
	bool vld_mv(/*in*/ move , /*in*/ plr_clr) const;

/**
  *	This method generates all moves for a given player
  */
	void gen_all_mvs(/*in*/ plr_clr , /*out*/ std::vector<move>& ) const;

	plr_clr get_cell(move );
	plr_clr get_cell(int );

	void set_cell(move , plr_clr );
	void set_cell(int , plr_clr );

	int get_wdth() const;
	int get_hght() const;
	int get_size() const;

	void rst();

/**
  *	Setups the board acoarding to the options.
  */
	void stp(const opts &);

private:
/**
  *	This array is the main board.
  */
	std::vector<plr_clr> brd_;
	int wdth_;
};

#endif //_GAME_BOARD_H__

