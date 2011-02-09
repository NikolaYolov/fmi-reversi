#if !defined(_VISUAL_BOARD_H__)
#define _VISUAL_BOARD_H__

#include <QWidget>

#include "turn.h"
#include "gm_brd.h"

class hmn_plr;
class gm_brd;

class vis_brd
	: public QWidget
{
public:
	vis_brd(QWidget *, int pos_x, int pos_y, const gm_brd &);

	void init(int pos_x, int pos_y, const gm_brd &b);
	int get_hz_sz() const;
	int get_vt_sz() const;
	void set_plr_brd(hmn_plr &, const gm_brd &);
	void set_cmp_brd(const gm_brd &b);
	void dctv();

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);
	virtual void leaveEvent(QEvent *);

private:
	bool _is_actv();
	void _drw_fld(int i, int j, bool hlght);
	void sort_mvs();	
	
	int _clc_idx_x(int ) const;
	int _clc_idx_y(int ) const;
	
	gm_brd snpsht_;

	int hlght_x_;
	int hlght_y_;

	std::vector<struct move> pos_mvs_;

	hmn_plr *plr_;
};

#endif //_VISUAL_BOARD_H__

