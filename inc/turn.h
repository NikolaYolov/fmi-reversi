#if !defined(_TURN_H__)
#define _TURN_H__

#include "defs.h"

struct move
{
	int x_;
	int y_;
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

#endif //_TURN_H__

