#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "nw_dlg.h"
 
#include "opts.h"

nw_dlg::nw_dlg(const opts &o, QWidget *p)
	: QDialog(p)
	, pl_1_chs_(new QComboBox(this))
	, pl_2_chs_(new QComboBox(this))
	, wdth_(new QLineEdit(QString(o.wdth_), this))
	, hght_(new QLineEdit(QString(o.hght_), this))
	, pl_1_t_(new QLabel(tr("First player:"), this))
	, pl_2_t_(new QLabel(tr("Second player:"), this))
	, w_t_(new QLabel(tr("Width of the board:"), this))
	, h_t_(new QLabel(tr("Height of the board:"), this))
	, ok_bn_(new QPushButton(tr("Ok"), this))
	, cn_bn_(new QPushButton(tr("Cancel"), this))
{
	pl_1_chs_->addItem("Human", true); /* true indicates that the player is human */
	pl_1_chs_->addItem("Computer", false); /* false is computer */

	pl_2_chs_->addItem("Human", true); /* true indicates that the player is human */
	pl_2_chs_->addItem("Computer", false); /* false is computer */
	
	/* wdth_->insert(QString(o.wdth_)); */
	wdth_->setValidator(new QIntValidator(4, 12, wdth_));

	/* hght_->insert(QString(o.hght_)); */
	hght_->setValidator(new QIntValidator(4, 12, hght_));

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
}

