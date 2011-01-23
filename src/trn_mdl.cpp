#include <cassert>

#include "trn_mdl.h"

trn_mdl::trn_mdl(QObject *p, const std::vector<turn> &h, int w)
	: QAbstractTableModel(p)
	, hstr_(h)
	, rw_cnt_(0)
	, wdg_(w)
	, w_sc_(2)
	, b_sc_(2)
{
	beginInsertRows(QModelIndex(), 0, 10);
	endInsertRows();
}

/*
static int n2r(int n)
{
	return n / 2 + (n % 2 == 1);
}
*/

static int rc2n(int r, int c)
{
	return r * 2 + (c % 2 == 1);
}

int trn_mdl::rowCount(const QModelIndex &) const
{
	return rw_cnt_;
}


int trn_mdl::columnCount(const QModelIndex &) const
{
	return 2;
}

QVariant trn_mdl::data(const QModelIndex &i, int r) const
{
	int idx = rc2n(i.row(), i.column());
	if (i.isValid() && 0 <= i.row() && idx < static_cast<int>(hstr_.size()) && r == Qt::DisplayRole)
	{
		turn t = hstr_[idx];
		if (t.mesg_.msg_ == mesg::m_skip)
			return QString('-');
		return QString("(%1, %2)").arg(t.move_.xy_ % wdg_ + 1).arg(t.move_.xy_ / wdg_ + 1);
	}
	else
		return QString();
}

QVariant trn_mdl::headerData(int sct, Qt::Orientation o, int r) const
{
	if (r == Qt::DisplayRole && o == Qt::Horizontal)
	{
		if (sct == 0)
			return QString(QObject::tr("Red - %1").arg(w_sc_));
		else if (sct == 1)
			return QString(QObject::tr("Black - %2").arg(b_sc_));
		else
			assert(false);
	}
	else
		return QVariant();
}

void trn_mdl::rsz()
{
	int c_rws = hstr_.size() / 2;
	//c_rws = std::max(c_rws, 1);
	
	if (c_rws == rw_cnt_ - 1) /* no need to insert or remove rows */
	{
		emit(dataChanged(createIndex(c_rws, 0), createIndex(c_rws, 1)));
	}
	else if (c_rws > rw_cnt_ - 1) /* we have to insert some rows */
	{
		beginInsertRows(QModelIndex(), rw_cnt_, c_rws);
		endInsertRows();
		emit(dataChanged(createIndex(rw_cnt_ - 1, 0), createIndex(c_rws, 1)));
	}
	else /* we have to remove some rows */
	{
		beginRemoveRows(QModelIndex(), c_rws + 1, rw_cnt_ -1);
		endRemoveRows();
		emit(dataChanged(createIndex(rw_cnt_ - 1, 0), createIndex(c_rws, 1)));
	}
 
	rw_cnt_ = c_rws + 1;
}

int trn_mdl::trns() const
{
	return hstr_.size();
}

void trn_mdl::set_sc(int w, int b)
{
	w_sc_ = w;
	b_sc_ = b;
	headerDataChanged(Qt::Horizontal, 0, 1);
}

