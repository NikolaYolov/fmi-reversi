#include "cassert"

#include "cmp_plr.h"

cmp_plr::cmp_plr(gm_mst &o, plr_clr c)
	: player(o, c)
{
}

//virtual
void cmp_plr::mk_mv(gm_brd &brd, time_t tm_lft)
{
	/**
	  * Unimplemented!
	  */
	assert(false);
}

