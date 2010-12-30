#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QLine>
#include <QHeaderView>

#include "vis_brd.h"
#include "mn_bar.h"
#include "opts.h"
#include "gm_mst.h"
#include "trn_lst.h"
#include "trn_mdl.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget window;
	window.setFixedSize(750, 500);
	window.setPalette(QPalette(QColor(255, 255, 255)));
	window.setAutoFillBackground(true);

	opts opt;
	opt.wdth_ = 8;
	opt.hght_ = 8;
	
	vis_brd *vb = new vis_brd(&window, 45, 30, gm_brd(opt.wdth_, opt.hght_));
	gm_mst gm(*vb, opt);
	
	gm.nw();

	trn_lst *tlst = new trn_lst(&window, 500, 30);
	tlst->verticalHeader()->setClickable(false);
	tlst->verticalHeader()->setHighlightSections(false);
	tlst->verticalHeader()->setMovable(false);

	trn_mdl *tmdl = new trn_mdl(&window, gm.get_hstr(), opt.wdth_);

	tlst->setModel(tmdl);

	QObject::connect(&gm, SIGNAL(nw_trn()), tmdl, SLOT(rsz()));
	QObject::connect(tlst, SIGNAL(d_cl(int )), &gm, SLOT(go_to_tr(int )));

	new mn_bar(&window, &app, gm, opt);	

	window.show();
	return app.exec();
}

