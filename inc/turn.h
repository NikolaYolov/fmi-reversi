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
		m_srnd,
		m_draw,
	} msg_;
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

#endif //_TURN_H__

