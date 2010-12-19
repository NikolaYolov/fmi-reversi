#include <cassert>

#include "gm_mst.h"
#include "gm_brd.h"
#include "hmn_plr.h"
#include "cmp_plr.h"
#include "vis_brd.h"

gm_mst::gm_mst(vis_brd &vb, const opts &o)
	: trn_n_(0)
	, opts_(o)
	, vis_brd_(vb)
{
	plrs_[0] = plrs_[1] = 0;
}

gm_mst::~gm_mst()
{
	_clr();
}

void gm_mst::nw()
{
	_init();
	_asgn_trn();		
}

void gm_mst::sv()
{
	/**
	  * Not implemented!
	  */
	assert(false);
}

void gm_mst::ld()
{
	/**
	  * Not implemented!
	  */
	assert(false);
}

void gm_mst::acpt_trn(turn t)
{
	gm_brd *nbrd = new gm_brd(*hstr_.back());
	assert(nbrd->get_cell(t.move_.x_, t.move_.y_) == pc_free);
	nbrd->set_cell(t.move_.x_, t.move_.y_, ((trn_n_ % 2) == 0)? pc_wht : pc_blc);
	hstr_.push_back(nbrd);
	++trn_n_;
	_asgn_trn();
}

vis_brd &gm_mst::get_vbrd()
{
	return vis_brd_;
}
 
void gm_mst::_clr()
{
	delete plrs_[0];
	delete plrs_[1];

	for (int i = 0; i < static_cast<int>(hstr_.size()); ++i)
		delete hstr_[i];

	hstr_.clear();
}

void gm_mst::_init()
{
	_clr();

	assert(opts_.hght_ > 1 && opts_.wdth_ > 1);
	gm_brd *brd = new gm_brd(opts_.wdth_, opts_.hght_);
	{
		int mx = (opts_.wdth_ / 2) - 1;
		int my = (opts_.hght_ / 2) - 1;

		brd->set_cell(mx, my, pc_wht);
		brd->set_cell(mx + 1, my, pc_blc);
		brd->set_cell(mx, my + 1, pc_blc);
		brd->set_cell(mx + 1, my + 1, pc_wht);
	}

	hstr_.push_back(brd);

	plrs_[0] = (opts_.pl1_ == opts::pt_hmn) ? static_cast<player*>(new hmn_plr(*this, pc_wht)) : static_cast<player*>(new cmp_plr(*this, pc_wht));
	plrs_[1] = (opts_.pl2_ == opts::pt_hmn) ? static_cast<player*>(new hmn_plr(*this, pc_blc)) : static_cast<player*>(new cmp_plr(*this, pc_blc));

	trn_n_ = 0;	
}

void gm_mst::_asgn_trn()
{
	assert(0 <= trn_n_);
	player *p = plrs_[trn_n_ % 2];
	assert(p);
	p->mk_mv(*hstr_.back(), 0.);
}

