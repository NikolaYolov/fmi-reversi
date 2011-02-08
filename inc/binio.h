#if !defined(_BINIO_H_)
#define _BINIO_H_

#include <QFile>

#include "gm_mst.h"

class gm_wrtr
	: public QFile
{
public:
	gm_wrtr(const QString &);
	void _wrt_opts(opts &);
	void _wrt_mvs(const gm_mst::hstr_t &);
};

class gm_rdr
	: public QFile
{
public:
	gm_rdr(const QString &);
	bool _rd_opts(opts &);
	bool _rd_mvs(gm_mst::hstr_t &);
};

#endif // endif _BINIO_H_i

