#include <vector>
#include <cassert>

#include "gm_brd.h"

#include "defs.h"
#include "turn.h"
#include "player.h"

gm_brd::gm_brd(int x_len, int y_len)
	: brd_(x_len * y_len)
	, wdth_(x_len)
{
	assert(0 == pc_free);
}

void gm_brd::do_mv(move mv, plr_clr plr)
{
	assert(brd_[mv.xy_] == pc_free);
	plr_clr enm = (plr == pc_wht)? pc_blc : pc_wht;
	const int wdth = get_wdth();
	
	int ds[8] = { 1, wdth + 1, wdth, wdth - 1, -1, - wdth - 1, - wdth, - wdth + 1 };
	int mvs[8];
	mvs[4] = mv.xy_ % wdth;
	mvs[6] = mv.xy_ / wdth;
	mvs[0] = wdth - mvs[4] - 1;
	mvs[2] = get_hght() - mvs[6] - 1;
	mvs[1] = std::min(mvs[0], mvs[2]);
	mvs[3] = std::min(mvs[2], mvs[4]);
	mvs[5] = std::min(mvs[4], mvs[6]);
	mvs[7] = std::min(mvs[6], mvs[0]);

	for (int d = 0; d < 8; ++d)
	{
		if (mvs[d] < 2)
			continue;

		int m = mv.xy_ + ds[d];
		if (brd_[m] != enm)
			continue;

		int k;
		for (k = 2; k <= mvs[d]; ++k)
		{
			m += ds[d];
			if (brd_[m] != enm)
				break;
		}

		if (k <= mvs[d] && brd_[m] == plr)
		{
			for (int i = 0, pos = mv.xy_; i < k; ++i, pos += ds[d])
				brd_[pos] = plr;
		}
	}
}

bool gm_brd::vld_mv(move mv, plr_clr plr) const
{
	return true;
}

void gm_brd::gen_all_mvs(plr_clr plr, std::vector<move>& res) const
{
	assert(plr != pc_free);
	
	const int wdth = get_wdth();
	
	plr_clr enm = (plr == pc_wht)? pc_blc : pc_wht;

	int ds[8] = { 1, wdth + 1, wdth, wdth - 1, -1, - wdth - 1, - wdth, - wdth + 1 };

	int mvs[8];
	res.clear();
	for (int i = 0; i < static_cast<int>(brd_.size()); ++i)
		if (brd_[i] == pc_free)
		{
			mvs[4] = i % wdth;
			mvs[6] = i / wdth;
			mvs[0] = wdth - mvs[4] - 1;
			mvs[2] = get_hght() - mvs[6] - 1;
			mvs[1] = std::min(mvs[0], mvs[2]);
			mvs[3] = std::min(mvs[2], mvs[4]);
			mvs[5] = std::min(mvs[4], mvs[6]);
			mvs[7] = std::min(mvs[6], mvs[0]);

			for (int d = 0; d < 8; ++d)
			{
				if (mvs[d] < 2)
					continue;

				int m = i + ds[d];
				if (brd_[m] != enm)
					continue;

				int k;
				for (k = 2; k <= mvs[d]; ++k)
				{
					m += ds[d];
					if (brd_[m] != enm)
						break;
				}

				if (k <= mvs[d] && brd_[m] == plr)
				{
					res.push_back(i);
					break;
				}
			}
		}

}


plr_clr gm_brd::get_cell(move m)
{
	return brd_[m.xy_];
}

plr_clr gm_brd::get_cell(int m)
{
	return brd_[m];
}

void gm_brd::set_cell(move m, plr_clr clr)
{
	brd_[m.xy_] = clr;
}

void gm_brd::set_cell(int m, plr_clr clr)
{
	brd_[m] = clr;
}

int gm_brd::get_wdth() const
{
	return wdth_;
}

int gm_brd::get_hght() const
{
	assert(brd_.size() % get_wdth() == 0);
	assert((get_wdth() == 0) == (brd_.size() == 0));
	return (get_wdth() != 0)? brd_.size() / get_wdth() : 0;
}

