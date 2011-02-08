#include <cassert>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QLine>
#include <QHeaderView>
#include <QApplication>
#include <QMessageBox>

#include "gm_mgr.h"

#include "vis_brd.h"
#include "mn_bar.h"
#include "opts.h"
#include "gm_mst.h"
#include "trn_lst.h"
#include "trn_mdl.h"
#include "nw_dlg.h"
#include "sv_dlg.h"
#include "ld_dlg.h"
#include "binio.h"

gm_mgr::gm_mgr(QApplication *app)
	: m_wnd_(new QWidget)
	, opt_(new opts)
	, gm_(new gm_mst)
	, vb_(0)
	, tl_(0)
{
	m_wnd_->setPalette(QPalette(QColor(255, 255, 255)));
	m_wnd_->setAutoFillBackground(true);

	opt_->wdth_ = 8;
	opt_->hght_ = 8;

	vb_ = new vis_brd(m_wnd_, 45, 45, gm_brd(opt_->wdth_, opt_->hght_));

	gm_->set_vb(vb_);
	gm_->set_opt(opt_);

	tl_ = new trn_lst(m_wnd_, vb_->get_hz_sz() + 90, 45, vb_->get_vt_sz());
	tm_ = new trn_mdl(m_wnd_, gm_->get_hstr(), opt_->wdth_);
	tl_->setModel(tm_);

	m_wnd_->setFixedSize(45 + vb_->get_hz_sz() + 45 + tl_->get_hz_sz() + 45, 45 + vb_->get_vt_sz() + 30);

	QObject::connect(gm_, SIGNAL(nw_trn()), tm_, SLOT(rsz()));
	QObject::connect(tl_, SIGNAL(d_cl(int )), gm_, SLOT(go_to_tr(int )));
	QObject::connect(gm_, SIGNAL(smb_sc(int , int )), tm_, SLOT(set_sc(int , int )));

	new mn_bar(m_wnd_, app, this);

	gm_->nw();
	gm_->srt();
	m_wnd_->show();
}

void gm_mgr::rsz()
{
	vb_->init(45, 45, gm_brd(opt_->wdth_, opt_->hght_));
	tl_->setGeometry(vb_->get_hz_sz() + 90, 45, tl_->get_hz_sz(), vb_->get_vt_sz());
	tl_->repaint();
	m_wnd_->setFixedSize(45 + vb_->get_hz_sz() + 45 + tl_->get_hz_sz() + 45, 45 + vb_->get_vt_sz() + 30);
}

void gm_mgr::do_nw()
{
	nw_dlg a(*opt_, m_wnd_);
	if (a.exec() == QDialog::Accepted)
	{
		rsz();
		gm_->set_opt(opt_);
		gm_->nw();
		tm_->rsz();
		gm_->srt();
	}
}

void gm_mgr::do_sv()
{
	sv_dlg dlg(m_wnd_);
	if (dlg.exec() == QDialog::Accepted)
	{
		QStringList ll = dlg.selectedFiles();
		assert(ll.size() == 1);
		gm_wrtr w(ll.first());

		if (!w.open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			QMessageBox(QMessageBox::Critical, tr("Error!"), tr("Unable to write in the file!"), QMessageBox::Ok, m_wnd_).exec();
			return;
		}
		w._wrt_opts(*opt_);

		gm_->sv(w);
	}
}

void gm_mgr::do_ld()
{
	ld_dlg dlg(m_wnd_);
	if (dlg.exec() == QDialog::Accepted)
	{
		QStringList ll = dlg.selectedFiles();
		assert(ll.size() == 1);

		gm_rdr r(ll.first());

		if (!r.open(QIODevice::ReadOnly))
		{
			QMessageBox(QMessageBox::Critical, tr("Error!"), tr("Unable to open the file!"), QMessageBox::Ok).exec();
			return;
		}

		if (!r._rd_opts(*opt_))
		{
			QMessageBox(QMessageBox::Critical, tr("Error!"), tr("File damaged!"), QMessageBox::Ok).exec();
			return;
		}

		rsz();
		gm_->set_opt(opt_);
		gm_->ld(r);
		rsz();
		tm_->rsz();
		gm_->srt();
	}
}

