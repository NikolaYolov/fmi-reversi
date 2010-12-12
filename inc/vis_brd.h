#if !defined(_VISUAL_BOARD_H__)
#define _VISUAL_BOARD_H__

#include <QWidget>

#include "gm_brd.h"

class hmn_plr;

class vis_brd
	: public QWidget
{
public:
	vis_brd(QWidget *, int pos_x, int pos_y, const gm_brd &);

	int get_hz_sz() const;
	int get_vt_sz() const;
	void set_brd(const gm_brd &);
	void set_plr(hmn_plr &);
	void dactv();

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);
	virtual void leaveEvent(QEvent *);

private:
	bool _is_actv();
	void _drw_fld(int i, int j, bool hlght);
	
	
	int _clc_idx_x(int ) const;
	int _clc_idx_y(int ) const;
	
	gm_brd snpsht_;

	int hlght_x_;
	int hlght_y_;

	hmn_plr *plr_;
};

#endif //_VISUAL_BOARD_H__
