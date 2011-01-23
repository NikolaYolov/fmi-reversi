#include <cassert>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>

#include "nw_dlg.h"
 
#include "opts.h"

nw_dlg::nw_dlg(opts &o, QWidget *p)
	: QDialog(p)
	, pl_1_chs_(new QComboBox(this))
	, pl_2_chs_(new QComboBox(this))
	, wdth_(new QLineEdit(this))
	, hght_(new QLineEdit(this))
	, pl_1_t_(new QLabel(tr("First player:"), this))
	, pl_2_t_(new QLabel(tr("Second player:"), this))
	, w_t_(new QLabel(tr("Width of the board:"), this))
	, h_t_(new QLabel(tr("Height of the board:"), this))
	, ok_bn_(new QPushButton(tr("Ok"), this))
	, cn_bn_(new QPushButton(tr("Cancel"), this))
	, opts_(o)
{
	pl_1_chs_->insertItem(pi_hmn, tr("Human")); /* true indicates that the player is human */
	pl_1_chs_->insertItem(pi_cmp, tr("Computer")); /* false is computer */
	pl_1_chs_->setCurrentIndex(o.pl1_ == opts::pt_cmp? pi_cmp : pi_hmn);

	pl_2_chs_->insertItem(pi_hmn, tr("Human")); /* true indicates that the player is human */
	pl_2_chs_->insertItem(pi_cmp, tr("Computer")); /* false is computer */
	pl_2_chs_->setCurrentIndex(o.pl2_ == opts::pt_cmp? pi_cmp : pi_hmn);

	wdth_->insert(QString().setNum(o.wdth_));
	wdth_->setValidator(new QIntValidator(4, 12, this));

	hght_->setText(QString().setNum(o.hght_));
	hght_->setValidator(new QIntValidator(4, 12, this));

	pl_1_t_->setGeometry(30, 30, 150, 30);
	pl_1_chs_->setGeometry(210, 30, 150, 30);

	pl_2_t_->setGeometry(30, 90, 150, 30);
	pl_2_chs_->setGeometry(210, 90, 150, 30);

	w_t_->setGeometry(30, 150, 150, 30);
	wdth_->setGeometry(210, 150, 150, 30);

	h_t_->setGeometry(30, 210, 150, 30);
	hght_->setGeometry(210, 210, 150, 30);

	ok_bn_->setGeometry(180, 290, 80, 28);
	cn_bn_->setGeometry(280, 290, 80, 28);

	setFixedSize(390, 350);
	setWindowTitle(tr("New game"));

	connect(ok_bn_, SIGNAL(clicked()), this, SLOT(cm_ok()));
	connect(cn_bn_, SIGNAL(clicked()), this, SLOT(reject()));
}

void nw_dlg::cm_ok()
{
	{ /* We have to chech if the width is ok. */
		QString wdth = wdth_->text();
		int pos = 0;
		if (wdth_->validator()->validate(wdth, pos) != QValidator::Acceptable)
		{
			QMessageBox(QMessageBox::Warning,
				QObject::tr("Invalid Selection!"),
				QObject::tr("The given value of the width is invalid!\nPlease select a value from 4 to 12."),
				QMessageBox::Ok)
				.exec();
			wdth_->setFocus();
			return;
		}
	}
	{ /* Same with the height. */
		QString hght = hght_->text();
		int pos = 0;
		if (hght_->validator()->validate(hght, pos) != QValidator::Acceptable)
		{
			QMessageBox(QMessageBox::Warning,
				QObject::tr("Invalid Selection!"),
				QObject::tr("The given value of the height is invalid!\nPlease select a value from 4 to 12."),
				QMessageBox::Ok)
				.exec();
			hght_->setFocus();
			return;
		}
	}

	/* All data is valid. Lets copy it to the output options and get the fuck out of here. */
	assert(pl_1_chs_->currentIndex() == pi_cmp || pl_1_chs_->currentIndex() == pi_hmn);
	opts_.pl1_ = pl_1_chs_->currentIndex() == pi_cmp? opts::pt_cmp : opts::pt_hmn;

	assert(pl_2_chs_->currentIndex() == pi_cmp || pl_2_chs_->currentIndex() == pi_hmn);
	opts_.pl2_ = pl_2_chs_->currentIndex() == pi_cmp? opts::pt_cmp : opts::pt_hmn;

	opts_.wdth_ = wdth_->text().toInt();
	opts_.hght_ = hght_->text().toInt();

	assert(4 <= opts_.wdth_ && opts_.wdth_ <= 12);
	assert(4 <= opts_.hght_ && opts_.hght_ <= 12);

	accept();
}

