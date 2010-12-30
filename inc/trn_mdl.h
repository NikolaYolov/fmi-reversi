#if !defined(_TURNS_MODEL_H_)
#define _TURNS_MODEL_H_

#include <QAbstractTableModel>
#include <vector>

#include "turn.h"

class trn_mdl
	: public QAbstractTableModel
{
	Q_OBJECT
public:
	trn_mdl(QObject *, const std::vector<turn> &, int wdg);

	virtual int rowCount(const QModelIndex &) const;
	virtual int columnCount(const QModelIndex &parent) const;
	virtual QVariant data(const QModelIndex &, int role) const;
	virtual QVariant headerData(int sct, Qt::Orientation , int role) const;

	int trns() const;

public slots:
	void rsz();

private:
	const std::vector<turn> &hstr_;
	int rw_cnt_;
	int wdg_;
};

#endif //_TURNS_MODEL_H_

