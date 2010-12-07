#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QLine>

#include "vis_brd.h"
#include "mn_bar.h"
#include "opts.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget window;
	window.setFixedSize(1000, 1000);
	window.setPalette(QPalette(QColor(250, 250, 200)));
	window.setAutoFillBackground(true);

	opts opt;
	new mn_bar(&window, &app, opt);

	new vis_brd(&window, 6, 8, 45, 30);

	window.show();
	return app.exec();
}

