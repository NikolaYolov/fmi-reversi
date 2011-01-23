#include <cassert>
#include <QHeaderView>

#include "trn_lst.h"

#include "trn_mdl.h"

trn_lst::trn_lst(QWidget *prt, int pos_x, int pos_y, int len_y)
	: QTableView(prt)
	, mdl_(0)
{
	setGeometry(pos_x, pos_y, get_hz_sz(), len_y);
	setSelectionBehavior(SelectItems);
	setSelectionMode(SingleSelection);
	verticalHeader()->hide();
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(dcd_idx(const QModelIndex &)));

	horizontalHeader()->setClickable(false);
	horizontalHeader()->setHighlightSections(false);
	horizontalHeader()->setMovable(false);
}

//virtual
void trn_lst::setModel(QAbstractItemModel *m)
{
	QTableView::setModel(m);
	mdl_ = static_cast<trn_mdl*>(m);
}

void trn_lst::dcd_idx(const QModelIndex& i)
{
	int idx = i.row() * 2 + i.column();
	assert(idx <= mdl_->trns() + 1);
	if (idx != mdl_->trns() + 1)
		emit(d_cl(idx));
}

/**
  * Static.
  */
int trn_lst::get_hz_sz()
{
	return 220;
}
