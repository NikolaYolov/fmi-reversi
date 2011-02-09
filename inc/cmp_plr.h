#if !defined(_COMPUTER_PLAYER_H__)
#define _COMPUTER_PLAYER_H__

#include <QThread>
#include "player.h"
#include "gm_brd.h"

class wrk_thrd
	: public QThread
{
public:
	turn des_;
	wrk_thrd(QObject *, plr_clr );
	void set_brd(const gm_brd &);
	virtual ~wrk_thrd();

protected:
	void run();

private:
	int a_b(int a, int b, plr_clr c, int lvl, bool skp);
	
private:
	std::vector<gm_brd> brd_stck_;
	plr_clr clr_;
};

/**
  *	This class in the interface for the algorithms.
  */
class cmp_plr
	: public QObject
	, public player
{
	Q_OBJECT
public:
	cmp_plr(gm_mst &, plr_clr );
/**
  *	This method makes one move using mix-max algorithm.
  */
	virtual void mk_mv(const /*in*/ gm_brd &, /*in*/ time_t );

private slots:
/**
  * This informs the game master that the human has make their move.
  */
	void do_mv();

protected:
	wrk_thrd worker_;
};

#endif //_COMPUTER_PLAYER_H__

