#include <cassert>
#include <algorithm>
#include <QPainter>
#include <QMouseEvent>

#include "vis_brd.h"
#include "hmn_plr.h"

static const int fld_sz = 50;
static const int wdt = 2;

vis_brd::vis_brd(QWidget *pnt, int pos_x, int pos_y, const gm_brd &brd)
	: QWidget(pnt)
	, snpsht_(brd)
	, hlght_x_(-1)
	, hlght_y_(-1)
	, plr_(0)
{
	setMouseTracking(false);
	setGeometry(pos_x, pos_y, get_hz_sz(), get_vt_sz());
}

static bool mvs_cmp(const move &m1, const move &m2)
{
	return m1.xy_ < m2.xy_;
}

void vis_brd::sort_mvs()
{
	assert(!pos_mvs_.empty());
	std::sort(pos_mvs_.begin(), pos_mvs_.end(), mvs_cmp);
}

void vis_brd::set_plr_brd(hmn_plr &p, const gm_brd &b)
{
	assert((snpsht_.get_wdth() == b.get_wdth()) && snpsht_.get_hght() == b.get_hght());
	setMouseTracking(true);
	plr_ = &p;
	snpsht_ = b;
	snpsht_.gen_all_mvs(plr_->get_clr(), pos_mvs_);

	repaint();
	if (pos_mvs_.empty())
	{
		turn t;
		t.mesg_.msg_ = mesg::m_skip;
		p.do_mv(t);
	}
}

int vis_brd::get_hz_sz() const
{
	return fld_sz * snpsht_.get_wdth() + wdt;
}

int vis_brd::get_vt_sz() const
{
	return fld_sz * snpsht_.get_hght() + wdt;
}

void vis_brd::dctv()
{
	pos_mvs_.clear();
	setMouseTracking(false);
	hlght_x_ = hlght_y_ = -1;
	plr_ = 0;
}

bool vis_brd::_is_actv()
{
	return plr_ != 0;
}

void vis_brd::_drw_fld(int i, int j, bool hlght)
{
	assert(0 <= i && 0 <= j);
	assert(i < snpsht_.get_wdth() && j < snpsht_.get_hght());
	plr_clr p = snpsht_.get_cell(i + j * snpsht_.get_wdth());
	static const int spc = fld_sz / 8;

	QPainter pnt(this);
	
	/**
	 * Step 1: Draw the bounding rectangle.
	 */
	if (hlght == false)
	{
		QPen pn(Qt::black);
		pn.setWidth(wdt);
		pnt.setBrush(QColor(250, 250, 200));
		pnt.setPen(pn);
	}
	else
	{
		QPen pn(Qt::red);
		pn.setWidth(wdt);
		pnt.setBrush(QColor(250, 250, 225));
		pnt.setPen(pn);
	}

	int fr_x = i * fld_sz + wdt / 2;
	int fr_y = j * fld_sz + wdt / 2;

	pnt.drawRect(fr_x, fr_y, fld_sz, fld_sz);
	
	/**
	 * Step 2: Draw the circle.
	 */
	{
		QPen pn(Qt::black);
		pn.setWidth(wdt);
		if (p == pc_wht)
			pnt.setBrush(QBrush(Qt::red));
		else if (p == pc_blc)
			pnt.setBrush(QBrush(Qt::black));
		pnt.setPen(pn);
	}

	if (p != pc_free)
		pnt.drawEllipse(fr_x + spc, fr_y + spc, fld_sz - 2 * spc, fld_sz - 2 * spc);
}

/*virtual*/
void vis_brd::paintEvent(QPaintEvent *)
{
	for (int i = 0; i < snpsht_.get_wdth(); ++i)
		for (int j = 0; j < snpsht_.get_hght(); ++j)
			_drw_fld(i, j, false);
	
	if (hlght_x_ != -1)
		_drw_fld(hlght_x_, hlght_y_, true);
}

int vis_brd::_clc_idx_x(int x) const
{
	int res = (x - (wdt / 2)) / fld_sz;
	assert(res <= snpsht_.get_wdth());
	if (res >= snpsht_.get_wdth())
		res = snpsht_.get_wdth() - 1;
	return res;
}

int vis_brd::_clc_idx_y(int y) const
{
	int res = (y - (wdt / 2)) / fld_sz;
	assert(res <= snpsht_.get_hght());
	if (res >= snpsht_.get_hght())
		res = snpsht_.get_hght() - 1;
	return res;
}

/*virtual*/
void vis_brd::mousePressEvent(QMouseEvent *ev)
{
	if (_is_actv())
	{
		assert(plr_ != 0);
		const QPoint& pnt = ev->pos();
		turn t;
		t.move_.xy_ = _clc_idx_x(pnt.x()) + _clc_idx_y(pnt.y()) * snpsht_.get_wdth(); 
		if (std::binary_search(pos_mvs_.begin(), pos_mvs_.end(), t.move_, mvs_cmp))
		{
			hlght_x_ = hlght_y_ = -1;
			plr_->do_mv(t);
		}
	}
}

/*virtual*/
void vis_brd::mouseMoveEvent(QMouseEvent *ev)
{
	if (_is_actv())
	{
		assert(plr_ != 0);
		const QPoint& pnt = ev->pos();
		hlght_x_ = _clc_idx_x(pnt.x());
		hlght_y_ = _clc_idx_y(pnt.y());
		
		struct move mv(hlght_x_ + hlght_y_ * snpsht_.get_wdth());
		if (std::binary_search(pos_mvs_.begin(), pos_mvs_.end(), mv, mvs_cmp) == false)
			hlght_x_ = hlght_y_ = -1;
		repaint();
	}
}

/*virtual*/
void vis_brd::leaveEvent(QEvent	*)
{
	if (_is_actv())
	{
		hlght_x_ = hlght_y_ = -1;
		repaint();
	}
}

