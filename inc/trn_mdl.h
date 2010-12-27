#if !defined(_TURNS_MODEL_H_)
#define _TURNS_MODEL_H_

#include <QAbstractTableModel>
#include <vector>

#include "turn.h"

class trn_mdl
	: private QAbstractTableModel
{
	trn_mdl(QObject *, const std::vector<turn> &);

	int rowCount(const QModelIndex &) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &, int role) const;
	QVariant headerData(int sct, Qt::Orientation , int role) const;

private:
	const std::vector<turn> &hstr_;
};

#endif //_TURNS_MODEL_H_
