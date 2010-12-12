#include <vector>
#include <cassert>

#include "gm_brd.h"

#include "defs.h"
#include "turn.h"
#include "player.h"

gm_brd::gm_brd(index_t x_len, index_t y_len)
	: brd_(x_len * y_len)
	, wdth_(x_len)
{
	assert(0 == pc_free);
}

void gm_brd::do_mv(move mv, plr_clr plr, gm_brd &res) const
{

}

bool gm_brd::vld_mv(move mv, plr_clr plr) const
{
	return true;
}

void gm_brd::gen_all_mvs(plr_clr plr, std::vector<move>& res) const
{

}

plr_clr gm_brd::get_cell(int i, int j)
{
	return brd_[i + j * get_wdth()];
}

void gm_brd::set_cell(int i, int j, plr_clr clr)
{
	brd_[i + j * get_wdth()] = clr;
}

int gm_brd::get_wdth() const
{
	return wdth_;
}

int gm_brd::get_hgth() const
{
	assert(brd_.size() % get_wdth() == 0);
	return brd_.size() / get_wdth();
}

