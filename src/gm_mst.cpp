#include <cassert>

#include "gm_mst.h"
#include "hmn_plr.h"
#include "cmp_plr.h"
#include "vis_brd.h"

gm_mst::gm_mst(vis_brd &vb, const opts &o)
	: trn_n_(0)
	, opts_(o)
	, vis_brd_(vb)
	, c_plr_(pc_wht)
	, c_brd_(o)
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
	assert(c_brd_.get_cell(t.move_) == pc_free);
	c_brd_.do_mv(t.move_, c_plr_);

	hstr_.resize(trn_n_); /* Notice that this will remove all turns after the current, if the user has decided to rollback some turns. */
	hstr_.push_back(t);
	c_plr_ = (c_plr_ == pc_wht)? pc_blc : pc_wht;
	++trn_n_;
	emit nw_trn();
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

	hstr_.clear();
}

void gm_mst::_init()
{
	_clr();

	assert(opts_.hght_ > 1 && opts_.wdth_ > 1);
	c_brd_.rst();

	plrs_[0] = (opts_.pl1_ == opts::pt_hmn) ? static_cast<player*>(new hmn_plr(*this, pc_wht)) : static_cast<player*>(new cmp_plr(*this, pc_wht));
	plrs_[1] = (opts_.pl2_ == opts::pt_hmn) ? static_cast<player*>(new hmn_plr(*this, pc_blc)) : static_cast<player*>(new cmp_plr(*this, pc_blc));

	trn_n_ = 0;
	c_plr_ = pc_wht;
}

void gm_mst::_asgn_trn()
{
	assert(0 <= trn_n_);
	player *p = plrs_[(c_plr_ == pc_wht)? 0 : 1];
	assert(p);
	p->mk_mv(c_brd_, 0.);
}

const std::vector<turn>& gm_mst::get_hstr() const
{
	return hstr_;
}

void gm_mst::go_to_tr(int i)
{
	if (i != trn_n_)
	{
		assert(0 <= i && i <= hstr_.size());
		for (trn_n_ = 0, c_plr_ = pc_wht, c_brd_.rst(); trn_n_ < i; ++trn_n_, (c_plr_ = ((c_plr_ == pc_wht)? pc_blc : pc_wht)))
			c_brd_.do_mv(hstr_[trn_n_].move_, c_plr_);
	}
	_asgn_trn();
}

