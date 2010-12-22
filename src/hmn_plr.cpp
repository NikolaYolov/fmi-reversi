#include "hmn_plr.h"

#include "gm_mst.h"
#include "vis_brd.h"

hmn_plr::hmn_plr(gm_mst& o, plr_clr c)
	: player(o, c)
{
}

//virtual
void hmn_plr::mk_mv(gm_brd &brd, time_t tm_lft)
{
	ownr_.get_vbrd().set_plr_brd(*this, brd);
}

void hmn_plr::do_mv(turn t)
{
	ownr_.acpt_trn(t);
}

