#include <QMenuBar>
#include <QMenu>
#include <QApplication>

#include "mn_bar.h"

mn_bar::mn_bar(QWidget *wnd, QApplication *app, opts &opt)
	: opts_(opt)
{
	QMenuBar *main = new QMenuBar(wnd);

	{
		QMenu *fl_m = new QMenu(QObject::tr("File"), main);
		QAction *a_new = fl_m->addAction(QObject::tr("New"));
		QAction *a_sv = fl_m->addAction(QObject::tr("Save"));
		QAction *a_ld = fl_m->addAction(QObject::tr("Load"));
		QAction *a_qt = fl_m->addAction(QObject::tr("Quit"));
		QObject::connect(a_qt, SIGNAL(triggered()), app, SLOT(quit()));
		main->addMenu(fl_m);
	}

	{
		QMenu *opt_m = new QMenu(QObject::tr("Options"), main);
		QAction *a_go = opt_m->addAction(QObject::tr("Game Options"));
		QAction *a_ao = opt_m->addAction(QObject::tr("Ai Options"));
		main->addMenu(opt_m);
	}
}

