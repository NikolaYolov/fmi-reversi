#include <cassert>
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

void vis_brd::set_brd(const gm_brd &b)
{
	assert((snpsht_.get_wdth() == b.get_wdth()) && snpsht_.get_hgth() == b.get_hgth());
	snpsht_ = b;
	repaint();
}

void vis_brd::set_plr(hmn_plr &p)
{
	setMouseTracking(true);
	plr_ = &p;
}

int vis_brd::get_hz_sz() const
{
	return fld_sz * snpsht_.get_wdth() + wdt;
}

int vis_brd::get_vt_sz() const
{
	return fld_sz * snpsht_.get_hgth() + wdt;
}

void vis_brd::dactv()
{
	setMouseTracking(false);
	hlght_x_ = hlght_y_ = 0;
	plr_ = 0;
}

bool vis_brd::_is_actv()
{
	return plr_ != 0;
}

void vis_brd::_drw_fld(int i, int j, bool hlght)
{
	assert(0 <= i && 0 <= j);
	assert(i < snpsht_.get_wdth() && j < snpsht_.get_hgth());
	plr_clr p = snpsht_.get_cell(i, j);
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
		for (int j = 0; j < snpsht_.get_hgth(); ++j)
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
	assert(res <= snpsht_.get_hgth());
	if (res >= snpsht_.get_hgth())
		res = snpsht_.get_hgth() - 1;
	return res;
}

/*virtual*/
void vis_brd::mousePressEvent(QMouseEvent *ev)
{
	if (_is_actv())
	{
		const QPoint& pnt = ev->pos();
		turn t;
		t.move_.x_ = _clc_idx_x(pnt.x());
		t.move_.y_ = _clc_idx_y(pnt.y());
		if (snpsht_.get_cell(t.move_.x_, t.move_.y_) == pc_free)
			plr_->do_mv(t);
	}
}

/*virtual*/
void vis_brd::mouseMoveEvent(QMouseEvent *ev)
{
	if (_is_actv())
	{
		const QPoint& pnt = ev->pos();
		hlght_x_ = _clc_idx_x(pnt.x());
		hlght_y_ = _clc_idx_y(pnt.y());
		if (!snpsht_.get_cell(hlght_x_, hlght_y_) == pc_free)
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

