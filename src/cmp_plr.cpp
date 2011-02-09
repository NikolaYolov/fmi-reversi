#include <cassert>
#include <vector>
#include <QDebug>

#include "gm_mst.h"
#include "cmp_plr.h"
#include "vis_brd.h"

const int max_lvl = 8;

cmp_plr::cmp_plr(gm_mst &o, plr_clr c)
	: player(o, c)
	, worker_(0, c)
{
	connect(&worker_, SIGNAL(finished()), this, SLOT(do_mv()));
}

//virtual
void cmp_plr::mk_mv(const gm_brd &brd, time_t )
{
	vis_brd* vb = ownr_.get_vbrd();
	assert(vb);
	vb->set_cmp_brd(brd);
	worker_.set_brd(brd);
	worker_.start(QThread::LowestPriority);
}

void cmp_plr::do_mv()
{
	assert(worker_.isFinished());
	ownr_.acpt_trn(worker_.des_);
}

wrk_thrd::wrk_thrd(QObject *o, plr_clr c)
	: QThread(o)
	, clr_(c)
	, brd_stck_(max_lvl + 1)
{
	;
}

int on_hrst(plr_clr c, const gm_brd &b)
{
	int scr_tbl[pc_cnt];
	scr_tbl[pc_free] = 0;
	scr_tbl[c] = 1;
	scr_tbl[(c == pc_wht)? pc_blc : pc_wht] = -1;

	int d = 0;
	const int c00 = 0;
	const int c0x = b.get_wdth() - 1;
	const int cy0 = b.get_size() - b.get_wdth();
	const int cyx = b.get_size() - 1;

	for (index_t i = c00; i <= c0x; ++i)
		d += 10 * scr_tbl[b.get_cell(i)];

	for (index_t i = c0x; i <= cyx; i += b.get_wdth())
		d += 10 * scr_tbl[b.get_cell(i)];
	
	for (index_t i = c00; i <= cy0; i += b.get_wdth())
		d += 10 * scr_tbl[b.get_cell(i)];
	
	for (index_t i = cy0; i <= cyx; ++i)
		d += 10 * scr_tbl[b.get_cell(i)];
	
	for (index_t i = c00; i <= cyx; ++i)
		d += scr_tbl[b.get_cell(i)];
	
	return d;
}

int off_hrst(plr_clr c, const gm_brd &b)
{
	int scr_tbl[pc_cnt];
	scr_tbl[pc_free] = 0;
	scr_tbl[c] = 100;
	scr_tbl[(c == pc_wht)? pc_blc : pc_wht] = -100;

	int d = 0;
	const int c00 = 0;
	const int c0x = b.get_wdth() - 1;
	const int cy0 = b.get_size() - b.get_wdth();
	const int cyx = b.get_size() - 1;

	for (index_t i = c00; i <= cyx; ++i)
		d += scr_tbl[b.get_cell(i)];

	return d;	
}

void wrk_thrd::set_brd(const gm_brd &b)
{
	brd_stck_[0] = b;
}

char *t1 = "\t";
char *t2 = "\t\t";
char *t3 = "\t\t\t";
char *t4 = "\t\t\t\t";
char *t5 = "\t\t\t\t\t";
char *t6 = "\t\t\t\t\t\t";
char *t7 = "\t\t\t\t\t\t\t";
char *t8 = "\t\t\t\t\t\t\t\t";
char *ts[8] = { t1, t2, t3, t4, t5, t6, t7, t8 };

int wrk_thrd::a_b(int a, int b, plr_clr c, int lvl, bool skp)
{
	if (lvl == max_lvl)
	{
		int res = on_hrst(c, brd_stck_[lvl]);
		return (clr_ == c)? res : - res;
	}

	std::vector<move> mvs;
	brd_stck_[lvl].gen_all_mvs(c, mvs);
	plr_clr opp_c = (c == pc_wht)? pc_blc : pc_wht;

	if (mvs.empty())
	{
		if (skp)
		{
			int res = off_hrst(c, brd_stck_[lvl]);
			return (clr_ == c)? res : - res;
		}
		else
		{
			brd_stck_[lvl + 1] = brd_stck_[lvl];
			return -a_b(-b, -a, opp_c, lvl + 1, true);
		}
	}

	for (int i = 0; i < static_cast<int>(mvs.size()); ++i)
	{
		brd_stck_[lvl + 1] = brd_stck_[lvl];
		brd_stck_[lvl + 1].do_mv(mvs[i], c);
		a = std::max(a, -a_b(-b, -a, opp_c, lvl + 1, false));
//		qDebug() << ts[lvl] << a;
		if (b <= a)
			break;
	}
	return a;
}

void wrk_thrd::run()
{
	std::vector<move> mvs;
	brd_stck_[0].gen_all_mvs(clr_, mvs);

	if (!mvs.empty())
	{
		plr_clr opp_c = (clr_ == pc_wht)? pc_blc : pc_wht;
		int besti = -1;
		int bestsc = -0x7fffffff;

		for (int i = 0; i < static_cast<int>(mvs.size()); ++i)
		{
			brd_stck_[1] = brd_stck_[0];
			brd_stck_[1].do_mv(mvs[i], clr_);
			int a = -a_b(-0x7fffffff, -bestsc, opp_c, 1, false);
			if (a > bestsc)
			{
				bestsc = a;
				besti = i;
			}
//			qDebug() << bestsc;
		}
		des_ = { mvs[besti], mesg() };
	}
	else
		des_.mesg_.msg_ = mesg::m_skip;
//	qDebug() << "-----------------------------------------------------------------";
}

wrk_thrd::~wrk_thrd()
{
	assert(isFinished());
}

