#if !defined(_VISUAL_BOARD_H__)
#define _VISUAL_BOARD_H__

#include <QWidget>

#include "gm_brd.h"
#include "player.h"

class vis_brd
	: public QWidget
{
public:
	vis_brd(QWidget *, int pos_x, int pos_y, const gm_brd &);


	int get_hz_sz() const;
	int get_vt_sz() const;

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);
	virtual void leaveEvent(QEvent *);

private:
	void _drw_fld(int i, int j, bool hlght);
	
	gm_brd snpsht_;

	int hlght_x_;
	int hlght_y_;
};

#endif //_VISUAL_BOARD_H__
