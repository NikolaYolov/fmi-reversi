#if !defined(_GAME_MASTER_H_)
#define _GAME_MASTER_H_

#include <vector>

#include "player.h"
#include "opts.h"
#include "turn.h"

class gm_brd;
class opts;
class vis_brd;

class gm_mst
{
public:
/**
  * Ctor, Dtor
  */
	gm_mst(vis_brd &, const opts &);
	~gm_mst();

/**
  * New, Save and Load
  */
	void nw();
	void sv();
	void ld();

/**
  * Accept Move method should be called when a player makes a move to notify the game master.
  */
	void acpt_trn(turn );

	vis_brd &get_vbrd(); 

private:
	void _clr();
	void _init();
	void _asgn_trn();

	player *plrs_[2];
	int trn_n_;
	std::vector<gm_brd *> hstr_;
	opts opts_;
	vis_brd &vis_brd_;
};

#endif //_GAME_MASTER_H_i

