#include "trn_lst.h"

trn_lst::trn_lst(QWidget *prt, int pos_x, int pos_y)
	: QTableView(prt)
{
	setGeometry(pos_x, pos_y, 200, 400);
	verticalHeader();
	showColumn(0);
	showColumn(1);
	//addColumn(QObject::tr("red"));
	//addColumn(QObject::tr("black"));
}
