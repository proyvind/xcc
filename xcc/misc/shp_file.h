// shp_file.h: interface for the Cshp_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHP_FILE_H__F9704D71_D4BF_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_SHP_FILE_H__F9704D71_D4BF_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

const int shp_o_mask = 0x0fffffff;

class Cshp_file: public Cvideo_file<t_shp_header>  
{
public:
	void decode(void* d) const;
	Cvideo_decoder* decoder(const t_palet_entry*);
	int extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet palet) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cf() const
	{
		return get_header()->c_images;
	}

	int cx() const
	{
		return get_header()->cx;
	}

	int cy() const
	{
		return get_header()->cy;
	}

	int get_c_images() const
	{
		return get_header()->c_images;
	}

	int get_cx() const
	{
		return get_header()->cx;
	}

	int get_cy() const
	{
		return get_header()->cy;
	}

    int get_format(int i) const
	{
        return static_cast<unsigned int>(get_index()[i << 1]) >> 28;
	}

	const byte* get_image(int i) const
	{
		return get_data() + get_offset(i);
	}

	const int* get_index() const
    {
        return reinterpret_cast<const int*>(get_data() + sizeof(t_shp_header));
    }

    int get_offset(int i) const
    {
        return get_index()[i << 1] & shp_o_mask;
    }

    int get_ref_offset(int i) const
    {
        return get_index()[(i << 1) + 1] & shp_o_mask;
    }
};

Cvirtual_binary shp_file_write(const byte* s, int cx, int cy, int c_images);

#endif // !defined(AFX_SHP_FILE_H__F9704D71_D4BF_11D3_A718_0000F81AF8CC__INCLUDED_)