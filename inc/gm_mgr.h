#if !defined(_GAME_MANAGER_H_)
#define _GAME_MANAGER_H_

#include <QObject>

class QApplication;
class QWidget;
class gm_mst;
class opts;

class gm_mgr
	: public QObject
{
	Q_OBJECT
public:
	gm_mgr(QApplication *);

public slots:
	void do_nw();

private:
	QWidget *m_wnd_;
	opts *opt_;
	gm_mst *gm_;
};

#endif /* _GAME_MANAGER_H_ */
