// object.h: interface for the Cobject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_H__4EA6B6A8_2DFE_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_OBJECT_H__4EA6B6A8_2DFE_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "location.h"
#include "object_type.h"
#include "player.h"

struct t_object_data
{
	int health;
	int x;
	int y;
	Cplayer* p;
	Cobject_type* t;
};

class Cobject  
{
public:
	Clocation l() const
	{
		return m_l;
	}

	const Cplayer& p() const
	{
		return *m_p;
	}

	const Cobject_type& t() const
	{
		return *m_t;
	}

	bool valid() const
	{
		return m_p && m_t;
	}

	void dump(ostream& os);
	void load(t_object_data d);
	void tick();
	Cobject();
	virtual ~Cobject();
private:
	Clocation m_destination;
	int m_health;
	Clocation m_l;
	Cplayer* m_p;
	Cobject_type* m_t;
	Cobject* m_target;
};

#endif // !defined(AFX_OBJECT_H__4EA6B6A8_2DFE_11D6_B861_0000B4936994__INCLUDED_)