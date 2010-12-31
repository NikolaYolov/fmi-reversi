#if !defined(_TURN_H__)
#define _TURN_H__

#include "defs.h"

struct move
{
	int xy_;

	move(int = 0);
};

struct mesg
{
	enum message
	{
		m_nmsg,
		m_srnd,
		m_draw,
		m_skip,
	} msg_;

	mesg();
};

struct turn
{
	move move_;
	mesg mesg_;	
};

// inlines

inline move::move(int xy)
	: xy_(xy)
{
	;
}

inline mesg::mesg()
	: msg_(m_nmsg)
{
	;
}

#endif //_TURN_H__

