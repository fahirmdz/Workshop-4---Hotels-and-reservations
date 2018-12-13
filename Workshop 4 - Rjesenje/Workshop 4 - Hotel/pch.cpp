// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
// In general, ignore this file, but keep it around if you are using pre-compiled headers.
