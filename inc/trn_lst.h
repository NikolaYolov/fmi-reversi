#if !defined(_TURNS_LIST_H_)
#define _TURNS_LIST_H_

#include <QTableView>

class QAbstractItemModel;
class trn_mdl;

class QWidget;

class trn_lst
	: public QTableView
{
	Q_OBJECT
public:
	trn_lst(QWidget *, int pox_x, int pox_y);
	virtual void setModel(QAbstractItemModel *);

signals:
	void d_cl(int );

private slots:
	void dcd_idx(const QModelIndex& ); /* this emits goto after the decode */

private:
	trn_mdl *mdl_;
	
};

#endif //_TURNS_LIST_H_

