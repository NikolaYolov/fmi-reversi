#if !defined(_GAME_MANAGER_H_)
#define _GAME_MANAGER_H_

#include <QObject>

class QApplication;
class QWidget;
class gm_mst;
class opts;
class vis_brd;
class trn_lst;
class trn_mdl;

class gm_mgr
	: public QObject
{
	Q_OBJECT
public:
	gm_mgr(QApplication *);
	void rsz();

public slots:
	void do_nw();

private:
	QWidget *m_wnd_;
	opts *opt_;
	gm_mst *gm_;
	vis_brd *vb_;
	trn_lst *tl_;
	trn_mdl *tm_;
};

#endif /* _GAME_MANAGER_H_ */
