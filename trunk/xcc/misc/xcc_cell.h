#pragma once

#include <math.h>
#include "cassert"
#include "string_conversion.h"
#include "vartypes.h"

class Cxcc_cell  
{
public:
	Cxcc_cell()
	{
		x = y = 0;
	}

	/*
	Cxcc_cell(unsigned int v)
	{
		set_cc(v);
	}
	*/

	Cxcc_cell(int x, int y):
		x(x), y(y)
	{
	}

	unsigned int get_cc() const
	{
		return x >> 8 | y >> 8 << 6;
	} 
	
	void set_cc(unsigned int v)
	{
		x = (v & 0x3f) << 8 | 0x80;
		y = v >> 6 << 8 | 0x80;
	}

	unsigned int get_xcc() const
	{
		return x >> 8 | y & 0xff00;
	}
	
	void set_xcc(unsigned int v)
	{
		x = (v & 0xff) << 8 | 0x80;
		y = v & 0xff00 | 0x80;
	}

	int get_x() const
	{
		return x;
	}

	int get_y() const
	{
		return y;
	}

	void set_x(int _x)
	{
		x = _x;
	}

	void set_y(int _y)
	{
		y = _y;
	}

#ifdef __AFX_H__
	CPoint pixel() const
	{
		return CPoint(24 * x >> 8, 24 * y >> 8);
	}

	void pixel(const CPoint& p) 
	{
		x = (p.x << 8) / 24;
		y = (p.y << 8) / 24;
	}
#endif

	void force_center()
	{
		x = x & ~0xff | 0x80;
		y = y & ~0xff | 0x80;
	}

	Cxcc_cell center() const
	{
		return Cxcc_cell(x & ~0xff | 0x80, y & ~0xff | 0x80);
	}
	
	Cxcc_cell topleft() const
	{
		return Cxcc_cell(x & ~0xff, y & ~0xff);
	}

	Cxcc_cell bottomright() const
	{
		return Cxcc_cell(x | 0xff, y | 0xff);
	}
	
	void force_subcell()
	{
		subcell(subcell());
	}

	int subcell() const
	{
		static int subcell_mask[24][24];
		static bool subcell_mask_created = false;
		if (!subcell_mask_created)
		{
			for (int y = 0; y < 12; y++)
			{
				for (int x = 0; x < 12; x++)
				{
					int rx = 23 - x;
					int ry = 23 - y;
					int dx0 = x - 12;
					int dy0 = y - 12;
					int dx1 = x - 6;
					int dy1 = y - 6;
					if (dx0 * dx0 + dy0 * dy0 > dx1 * dx1 + dy1 * dy1)
					{
						subcell_mask[y][x] = 1;
						subcell_mask[y][rx] = 2;
						subcell_mask[ry][x] = 3;
						subcell_mask[ry][rx] = 4;
					}
				}
			}
			subcell_mask_created = true;
		}
		return subcell_mask[24 * (y & 0xff) >> 8][24 * (x & 0xff) >> 8];
	}

	void subcell(int v)
	{
		x = x & ~0xff;
		y = y & ~0xff;
		switch (v)
		{
		case 0:
			x |= 0x80;
			y |= 0x80;
			break;
		case 1:
			x |= 0x40;
			y |= 0x40;
			break;
		case 2:
			x |= 0xc0;
			y |= 0x40;
			break;
		case 3:
			x |= 0x40;
			y |= 0xc0;
			break;
		case 4:
			x |= 0xc0;
			y |= 0xc0;
			break;
		default:
			assert(false);
		}
	}

	unsigned int distance() const
	{
		return static_cast<unsigned int>(sqrt(static_cast<float>(x * x + y * y)));
	}

	Cxcc_cell operator*(int v) const
	{
		return Cxcc_cell(x * v, y * v);
	}

	const Cxcc_cell& operator*=(int v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	Cxcc_cell operator+(const Cxcc_cell& v) const
	{
		return Cxcc_cell(x + v.x, y + v.y);
	}

	const Cxcc_cell& operator+=(const Cxcc_cell& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Cxcc_cell operator-(const Cxcc_cell& v) const
	{
		return Cxcc_cell(x - v.x, y - v.y);
	}

	const Cxcc_cell& operator-=(const Cxcc_cell& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	bool operator==(const Cxcc_cell& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator!=(const Cxcc_cell& v) const
	{
		return (x != v.x || y != v.y);
	}

	static unsigned int distance(const Cxcc_cell& a, const Cxcc_cell& b)
	{
		return (a - b).distance();
	}

	operator string() const
	{
		int a = 100 * x >> 8;
		int b = 100 * y >> 8;
		return nwzl(3, a / 100) + ',' + nwzl(2, a % 100) + ";" + nwzl(3, b / 100) + ',' + nwzl(2, b % 100);
	}
private:
	int x;
	int y;
};
