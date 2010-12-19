#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QLine>

#include "vis_brd.h"
#include "mn_bar.h"
#include "opts.h"
#include "gm_mst.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget window;
	window.setFixedSize(450, 500);
	window.setPalette(QPalette(QColor(255, 255, 255)));
	window.setAutoFillBackground(true);

	opts opt;
	opt.wdth_ = 6;
	opt.hght_ = 8;
	
	vis_brd *vb = new vis_brd(&window, 45, 30, gm_brd(opt.wdth_, opt.hght_));
	gm_mst gm(*vb, opt);
	
	gm.nw();

	new mn_bar(&window, &app, gm, opt);	

	window.show();
	return app.exec();
}

