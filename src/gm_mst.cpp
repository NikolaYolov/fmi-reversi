#include <cassert>
#include <QMessageBox>

#include "gm_mst.h"
#include "hmn_plr.h"
#include "cmp_plr.h"
#include "vis_brd.h"
#include "binio.h"

gm_mst::gm_mst()
	: trn_n_(0)
	, vis_brd_(0)
	, c_plr_(pc_wht)
	, c_brd_()
	, lst_skp_(false)
{
	plrs_[0] = plrs_[1] = 0;
}

gm_mst::gm_mst(const opts &o)
	: trn_n_(0)
	, vis_brd_(0)
	, c_plr_(pc_wht)
	, c_brd_(o)
	, lst_skp_(false)
	, opts_(o)
{
	plrs_[0] = plrs_[1] = 0;
}

gm_mst::gm_mst(vis_brd *vb, const opts &o)
	: trn_n_(0)
	, vis_brd_(vb)
	, c_plr_(pc_wht)
	, c_brd_(o)
	, lst_skp_(false)
	, opts_(o)
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
}

void gm_mst::sv(gm_wrtr &w)
{
	w._wrt_mvs(hstr_);
}

void gm_mst::ld(gm_rdr &r)
{
	_init();
	if (!r._rd_mvs(hstr_))
	{
		QMessageBox(QMessageBox::Critical, tr("Error!"), tr("File damaged!"), QMessageBox::Ok).exec();
		return;
	}

	go_to_tr(hstr_.size());
	emit nw_trn();	
	{
		int ww, bb;
		_get_sc(ww, bb);
		emit smb_sc(ww, bb);
	}
}

void gm_mst::set_vb(vis_brd *v)
{
	vis_brd_ = v;	
}

void gm_mst::set_opt(const opts *o)
{
	opts_ = *o;
}

void gm_mst::acpt_trn(turn t)
{
	if (t.mesg_.msg_ != mesg::m_skip)
	{
		assert(c_brd_.get_cell(t.move_) == pc_free);
		c_brd_.do_mv(t.move_, c_plr_);
		lst_skp_ = false;
	}
	else
	{
		if (lst_skp_ == true)
		{
			_end_gm();
			return;
		}
		else
			lst_skp_ = true;
	}

	hstr_.resize(trn_n_); /* Notice that this will remove all turns after the current, if the user has decided to rollback some turns. */
	hstr_.push_back(t);
	c_plr_ = (c_plr_ == pc_wht)? pc_blc : pc_wht;
	++trn_n_;
	emit nw_trn();
	
	{
		int ww, bb;
		_get_sc(ww, bb);
		emit smb_sc(ww, bb);
	}

	_asgn_trn();
}

void gm_mst::_end_gm()
{
	vis_brd_->dctv();

	int ww, bb;
	_get_sc(ww, bb);
	emit smb_sc(ww, bb);

	QMessageBox(QMessageBox::Information, 
		QObject::tr("Game Over!"),
		ww == bb? tr("The game has ended in a draw.") :
			tr("%1 player has won!\nFinal score: %2 - %3").arg((ww > bb)? "Red" : "Black").arg(ww).arg(bb),
		QMessageBox::Ok)
	.exec();
}

vis_brd *gm_mst::get_vbrd()
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

	c_brd_.stp(opts_);
	assert(opts_.hght_ > 1 && opts_.wdth_ > 1);
	c_brd_.rst();

	plrs_[0] = (opts_.pl1_ == opts::pt_hmn) ? dynamic_cast<player*>(new hmn_plr(*this, pc_wht)) : dynamic_cast<player*>(new cmp_plr(*this, pc_wht));
	plrs_[1] = (opts_.pl2_ == opts::pt_hmn) ? dynamic_cast<player*>(new hmn_plr(*this, pc_blc)) : dynamic_cast<player*>(new cmp_plr(*this, pc_blc));

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

const gm_mst::hstr_t& gm_mst::get_hstr() const
{
	return hstr_;
}

void gm_mst::go_to_tr(int i)
{
	/* We cant go to turns, which must be skipped */
	for (; i < static_cast<int>(hstr_.size()); ++i)
		if (hstr_[i].mesg_.msg_ != mesg::m_skip)
			break;

	if (i != trn_n_)
	{
		assert(0 <= i && i <= static_cast<int>(hstr_.size()));
		int skp_cnt = 0; /* A counter to maintain how many skips in a row have been met. */
		for (trn_n_ = 0, c_plr_ = pc_wht, c_brd_.rst(); trn_n_ < i; ++trn_n_, (c_plr_ = ((c_plr_ == pc_wht)? pc_blc : pc_wht)))
		{
			turn t = hstr_[trn_n_];
			bool skp = t.mesg_.msg_ == mesg::m_skip;
			skp_cnt = (skp_cnt + skp) * skp; /* If skp is 1 we inc skp_cnt, otherwise we make skp_cnt zero. */

			if (skp_cnt == 2)
			{
				_end_gm();
				return;
			}
		
			if (skp == false)	
				c_brd_.do_mv(t.move_, c_plr_);
		}
		assert(skp_cnt != 2);
		lst_skp_ = skp_cnt == 1;
		{
			int ww, bb;
			_get_sc(ww, bb);
			emit smb_sc(ww, bb);
		}
		_asgn_trn();
	}
}

void gm_mst::_get_sc(int &w, int &b)
{
	w = b = 0;
	for (int i = 0; i < c_brd_.get_size(); ++i)
		if (c_brd_.get_cell(i) == pc_wht)
			++w;
		else if (c_brd_.get_cell(i) == pc_blc)
			++b;
}

