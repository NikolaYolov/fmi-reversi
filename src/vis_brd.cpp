#include <cassert>
#include <QPainter>

#include "vis_brd.h"

static const int fld_sz = 50;
static const int wdt = 2;

vis_brd::vis_brd(QWidget *pnt, int hz_flds, int vt_flds, int pos_x, int pos_y)
	: QWidget(pnt)
	, hz_flds_(hz_flds)
	, vt_flds_(vt_flds)
{
	setGeometry(pos_x, pos_y, get_hz_sz(), get_vt_sz());
	//setPalette(QPalette(QColor(250, 250, 200)));
	//setAutoFillBackground(true);
}

int vis_brd::get_hz_sz() const
{
	return fld_sz * hz_flds_ + wdt;
}

int vis_brd::get_vt_sz() const
{
	return fld_sz * vt_flds_ + wdt;
}

void vis_brd::_drw_fld(int i, int j, plr_clr p, bool hlght)
{
	assert(i < hz_flds_ && j < vt_flds_);
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

void vis_brd::paintEvent(QPaintEvent* )
{
	for (int i = 0; i < hz_flds_; ++i)
		for (int j = 0; j < vt_flds_; ++j)
			_drw_fld(i, j, pc_free, false);

	_drw_fld(3, 2, pc_white, false);
	_drw_fld(2, 3, pc_black, true);
}

