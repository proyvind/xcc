// ogg_file.h: interface for the Cogg_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGG_FILE_H__3FD21862_D8E9_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_OGG_FILE_H__3FD21862_D8E9_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "virtual_audio.h"

#pragma comment(lib, "ogg_static.lib")
#pragma comment(lib, "vorbis_static.lib")
#pragma comment(lib, "vorbisfile_static.lib")

class Cogg_file: public Ccc_file_sh<t_ogg_header>
{
public:
	Cogg_file();
	~Cogg_file();

	bool is_valid() const
	{
		return !(get_size() < sizeof(t_ogg_header) || memcmp(get_header()->id, ogg_id, 4));
	}

	int decode(Cvirtual_audio& audio);
	int get_c_channels();
	int get_c_samples();
	int get_samplerate();
};

#endif // !defined(AFX_OGG_FILE_H__3FD21862_D8E9_11D4_A95D_0050042229FC__INCLUDED_)