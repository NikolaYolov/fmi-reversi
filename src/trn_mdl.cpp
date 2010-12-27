#include <cassert>

#include "trn_mdl.h"

trn_mdl::trn_mdl(QObject *p, const std::vector<turn> &h)
	: QAbstractTableModel(p)
	, hstr_(h)
{
}

static int n2r(int n)
{
	return n / 2 + (n % 2 == 1);
}

static int rc2n(int r, int c)
{
	return 2 * r + (c % 2 == 1);
}

int trn_mdl::rowCount(const QModelIndex &) const
{
	return n2r(hstr_.size());
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
		return QString("(%d, %d)").arg(t.move_.xy_).arg(t.move_.xy_);
	}
	else
		return QString();
}

QVariant trn_mdl::headerData(int sct, Qt::Orientation o, int r) const
{
	if (r == Qt::DisplayRole && o == Qt::Horizontal)
	{
		if (sct == 0)
			return QString(QObject::tr("Red"));
		else if (sct == 1)
			return QString(QObject::tr("Black"));
		else
			assert(false);
	}
	else
		return QVariant();
}

