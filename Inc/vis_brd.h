#if !defined(_VISUAL_BOARD_H__)
#define _VISUAL_BOARD_H__

#include <QWidget>

#include "player.h"

class vis_brd
	: public QWidget
{
public:
	vis_brd(QWidget *, int hz_flds, int vt_flds, int pos_x, int pos_y);

	void paintEvent(QPaintEvent* );

	int get_hz_sz() const;
	int get_vt_sz() const;

private:
	void _drw_crcl(int i, int j, plr_clr );

	int hz_flds_;
	int vt_flds_;
};

#endif //_VISUAL_BOARD_H__
