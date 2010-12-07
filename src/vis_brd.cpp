#include <cassert>
#include <QPainter>

#include "vis_brd.h"

static const int fld_sz = 50;
static const int wdt = 3;

vis_brd::vis_brd(QWidget *pnt, int hz_flds, int vt_flds, int pos_x, int pos_y)

	: QWidget(pnt)
	, hz_flds_(hz_flds)
	, vt_flds_(vt_flds)
{
	setGeometry(pos_x, pos_y, get_hz_sz(), get_vt_sz());
	setPalette(QPalette(QColor(250, 250, 200)));
	setAutoFillBackground(true);
}

int vis_brd::get_hz_sz() const
{
	return fld_sz * hz_flds_ + wdt;
}

int vis_brd::get_vt_sz() const
{
	return fld_sz * vt_flds_ + wdt;
}

void vis_brd::_drw_crcl(int i, int j, plr_clr p)
{
	assert(i < hz_flds_ && j < vt_flds_);
	static const int spc = fld_sz / 8;

	QPainter pnt(this);
	
	{
		QPen pn(Qt::black);
		pn.setWidth(wdt);
		pnt.setPen(pn);
	}
	
	if (p == pc_white)
		pnt.setBrush(QBrush(Qt::red));
	else if (p == pc_black)
		pnt.setBrush(QBrush(Qt::black));
	else	
		pnt.setBrush(QColor(250, 250, 200));
	/*
	QRadialGradient grd(50, 50, 50, 50, 50);
	grd.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
	grd.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
	pnt.setBrush(grd);
	*/
	pnt.drawEllipse(i * fld_sz + spc, j * fld_sz + spc, fld_sz - 2 * spc, fld_sz - 2 * spc);
}

void vis_brd::paintEvent(QPaintEvent* )
{
	QPainter pnt(this);

	{
		QPen pn(Qt::black);
		pn.setWidth(wdt);
		pnt.setPen(pn);
	}

	int hz_sz = get_hz_sz();
	int vt_sz = get_vt_sz();

	for (int c_x = 0; c_x <= hz_sz; c_x += fld_sz)
		pnt.drawLine(QLine(c_x, 0, c_x, vt_sz));

	for (int c_y = 0; c_y <= vt_sz; c_y += fld_sz)
		pnt.drawLine(QLine(0, c_y, hz_sz, c_y));

	_drw_crcl(3, 2, pc_white);
	_drw_crcl(2, 3, pc_black);
}

