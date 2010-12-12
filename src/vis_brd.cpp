#include <cassert>
#include <QPainter>
#include <QMouseEvent>

#include "vis_brd.h"

static const int fld_sz = 50;
static const int wdt = 2;

vis_brd::vis_brd(QWidget *pnt, int pos_x, int pos_y, const gm_brd &brd)
	: QWidget(pnt)
	, snpsht_(brd)
	, hlght_x_(-1)
	, hlght_y_(-1)
{
	setGeometry(pos_x, pos_y, get_hz_sz(), get_vt_sz());
	setMouseTracking(true);
	//setPalette(QPalette(QColor(250, 250, 200)));
	//setAutoFillBackground(true);
}

int vis_brd::get_hz_sz() const
{
	return fld_sz * snpsht_.get_wdth() + wdt;
}

int vis_brd::get_vt_sz() const
{
	return fld_sz * snpsht_.get_hgth() + wdt;
}

#include <cstdio>
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
		if (p == pc_white)
			pnt.setBrush(QBrush(Qt::red));
		else if (p == pc_black)
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

static int clc_idx(int x)
{
	return (x - (wdt / 1))/ fld_sz;
}

/*virtual*/
void vis_brd::mousePressEvent(QMouseEvent *ev)
{
	const QPoint& pnt = ev->pos();
	int x = clc_idx(pnt.x());
	int y = clc_idx(pnt.y());
	snpsht_.set_cell(x, y, pc_white);
	repaint();
}

/*virtual*/
void vis_brd::mouseMoveEvent(QMouseEvent *ev)
{
	const QPoint& pnt = ev->pos();
	hlght_x_ = clc_idx(pnt.x());
	hlght_y_ = clc_idx(pnt.y());
	repaint();
}

/*virtual*/
void vis_brd::leaveEvent(QEvent	*)
{
	hlght_x_ = hlght_y_ = -1;
	repaint();
}

