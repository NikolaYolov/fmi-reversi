#include "binio.h"

#include <cassert>

static const int fl_mkr = 0xfefe7676;

gm_wrtr::gm_wrtr(const QString &fnm)
	: QFile(fnm)
{
	;
}

void gm_wrtr::_wrt_opts(opts &o)
{
	writeData((const char *)&fl_mkr, sizeof(fl_mkr));
	writeData((const char *)&o.wdth_, sizeof(o.wdth_));
	writeData((const char *)&o.hght_, sizeof(o.hght_));	
	{
		bool pl1 = (o.pl1_ == opts::pt_hmn);
		writeData((const char *)&pl1, sizeof(bool));
	}
	{
		bool pl2 = (o.pl2_ == opts::pt_hmn);
		writeData((const char *)&pl2, sizeof(bool));
	}
}

void gm_wrtr::_wrt_mvs(const gm_mst::hstr_t &h)
{
	writeData((const char *)&fl_mkr, sizeof(fl_mkr));

	int sz = static_cast<int>(h.size());
	writeData((const char *)&sz, sizeof(int));
	for (int i = 0; i < sz; ++i)
	{
		writeData((const char *)&h[i].move_.xy_, sizeof(int));
		int msg = static_cast<int>(h[i].mesg_.msg_);
		writeData((const char *)&msg, sizeof(int));
	}
}

gm_rdr::gm_rdr(const QString &fnm)
	:QFile(fnm)
{
	;
}

bool gm_rdr::_rd_opts(opts &o)
{
	int mkr;
	readData((char *)&mkr, sizeof(mkr));
	if (mkr != fl_mkr)
		return false;

	readData((char *)&o.wdth_, sizeof(o.wdth_));
	readData((char *)&o.hght_, sizeof(o.hght_));
	{
		bool pl1;
		readData((char *)&pl1, sizeof(bool));
		o.pl1_ = pl1? opts::pt_hmn : opts::pt_cmp;
	}
	{
		bool pl2;
		readData((char *)&pl2, sizeof(bool));
		o.pl2_ = pl2? opts::pt_hmn : opts::pt_cmp;
	}
	return true;
}

bool gm_rdr::_rd_mvs(gm_mst::hstr_t &h)
{
	assert(h.empty());

	int mkr;
	readData((char *)&mkr, sizeof(mkr));
	if (mkr != fl_mkr)
		return false;

	int sz;
	readData((char *)&sz, sizeof(sz));
	assert(0 <= sz && sz < 300);
	h.reserve(sz);
	
	for (int i = 0; i < sz; ++i)
	{
		turn t;
		readData((char *)&t.move_.xy_, sizeof(int));
		readData((char *)&t.mesg_.msg_, sizeof(int));
		h.push_back(t);
	}
	return true;
}

