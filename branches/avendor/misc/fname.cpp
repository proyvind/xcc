// fname.cpp: implementation of the Cfname class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fname.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cfname::Cfname()
{
}

Cfname::Cfname(const string &s)
{
	operator=(s);
}

string Cfname::get_fname() const
{
	return title + ext;
}

string Cfname::get_ftitle() const
{
	return title;
}

string Cfname::get_fext() const
{
	return ext;
}

string Cfname::get_path() const
{
	return path;
}

string Cfname::get_all() const
{
	return path + title + ext;
}

void Cfname::expand()
{
	char t[MAX_PATH];
	_fullpath(t, get_all().c_str(), MAX_PATH);
	Cfname(static_cast<string>(t));
}

Cfname GetModuleFileName(HMODULE hModule)
{
	char s[MAX_PATH];
	if (GetModuleFileName(hModule, s, MAX_PATH))
		return s;
	else
		return "";
}

void Cfname::set_title(const string &s)
{
	title = s;
}

void Cfname::set_ext(const string &s)
{
	ext = s;
}

void Cfname::use_default_ext(const string &s)
{
	if (ext == "")
		ext = s;
}

void Cfname::set_path(const string &s)
{
	path = s;
	if (!path.empty() && path[path.length() - 1] != '\\')
		path += '\\';	
}

void Cfname::use_default_path(const string &s)
{
	if (path.empty())
		set_path(s);
}

void Cfname::make_path()
{
	if ((title + ext).empty())
		return;
	path += title + ext + '\\';
	title = ext = "";
}

bool Cfname::exists() const
{
	HANDLE h;
	WIN32_FIND_DATA d;
	h = FindFirstFile(static_cast<string>(get_all()).c_str(), &d);
	if (h == INVALID_HANDLE_VALUE)
		return false;
	FindClose(h);
	return true;
}

Cfname Cfname::operator=(const string &s)
{
	long p1 = s.rfind('\\');
	long p2 = s.rfind('.');
	char t[MAX_PATH];
	if (p1 != s.npos)
	{	
		//copy last \ also
		t[s.copy(t, p1 + 1)] = 0;
		path = t;
	}
	t[s.copy(t, p2 - p1 - 1, p1 + 1)] = 0;
	title = t;
	if (p2 != s.npos && p1 < p2)
	{
		t[s.copy(t, s.npos, p2)] = 0;
		ext = t;
	}
	return *this;
}