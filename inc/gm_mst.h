#if !defined(_GAME_MASTER_H_)
#define _GAME_MASTER_H_

#include <vector>
#include <QObject>

#include "player.h"
#include "opts.h"
#include "turn.h"
#include "gm_brd.h"

class QFile;

class gm_brd;
class opts;
class vis_brd;
class gm_rdr;
class gm_wrtr; 

class gm_mst
	: public QObject
{
	Q_OBJECT

public:
	typedef std::vector<turn> hstr_t;
/**
  * Ctor, Dtor
  */
	gm_mst();
	gm_mst(const opts &);
	gm_mst(vis_brd *, const opts &);
	~gm_mst();

/**
  * Initializers
  */
	void set_vb(vis_brd *);
	void set_opt(const opts *);

public:
/**
  * New, Save and Load
  */
	void nw();
	void sv(gm_wrtr &);
	void ld(gm_rdr &);
	void srt();

public slots:
	void go_to_tr(int );

public:
/**
  * Accept Move method should be called when a player makes a move to notify the game master.
  */
	void acpt_trn(turn );

	vis_brd *get_vbrd();
	const hstr_t &get_hstr() const;

signals:
	void nw_trn();
	void smb_sc(int w, int b); /* This signal is used to emit the score to the turns list. */

private:
	void _clr();
	void _init();
	void _asgn_trn();
	void _end_gm();
	void _get_sc(int &w, int &b); /* This memeber is used to get the number of white and black fields in c_brd_ */

	player *plrs_[2];
	int trn_n_;
	plr_clr c_plr_;
	hstr_t hstr_;
	gm_brd c_brd_;
	opts opts_;
	vis_brd *vis_brd_;
	bool lst_skp_;
};

/* inlines */

inline void gm_mst::srt()
{
	_asgn_trn();
}

#endif //_GAME_MASTER_H_i

