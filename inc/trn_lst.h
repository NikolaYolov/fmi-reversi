#if !defined(_TURNS_LIST_H_)
#define _TURNS_LIST_H_

#include <QTableView>

class QWidget;

class trn_lst
	: private QTableView
{
public:
	trn_lst(QWidget *, int pox_x, int pox_y);	
};

#endif //_TURNS_LIST_H_
