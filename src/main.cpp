#include <QApplication>

#include "gm_mgr.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	gm_mgr mgr(&app);
	return app.exec();
}

