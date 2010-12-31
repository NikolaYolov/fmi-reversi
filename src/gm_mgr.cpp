#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QLine>
#include <QHeaderView>
#include <QApplication>

#include "gm_mgr.h"

#include "vis_brd.h"
#include "mn_bar.h"
#include "opts.h"
#include "gm_mst.h"
#include "trn_lst.h"
#include "trn_mdl.h"
#include "nw_dlg.h"

gm_mgr::gm_mgr(QApplication *app)
	: m_wnd_(new QWidget)
	, opt_(new opts)
	, gm_(new gm_mst)
{
	m_wnd_->setFixedSize(750, 500);
	m_wnd_->setPalette(QPalette(QColor(255, 255, 255)));
	m_wnd_->setAutoFillBackground(true);

	opt_->wdth_ = 8;
	opt_->hght_ = 8;

	vis_brd *vb = new vis_brd(m_wnd_, 45, 30, gm_brd(opt_->wdth_, opt_->hght_));
	gm_->set_vb(vb);
	gm_->set_opt(opt_);

	trn_lst *tlst = new trn_lst(m_wnd_, 500, 30);
	trn_mdl *tmdl = new trn_mdl(m_wnd_, gm_->get_hstr(), opt_->wdth_);
	tlst->setModel(tmdl);

	QObject::connect(gm_, SIGNAL(nw_trn()), tmdl, SLOT(rsz()));
	QObject::connect(tlst, SIGNAL(d_cl(int )), gm_, SLOT(go_to_tr(int )));
	QObject::connect(gm_, SIGNAL(smb_sc(int , int )), tmdl, SLOT(set_sc(int , int )));

	new mn_bar(m_wnd_, app, this);

	gm_->nw();

	m_wnd_->show();
}

void gm_mgr::do_nw()
{
	nw_dlg a(*opt_, m_wnd_);
	a.exec();
}

