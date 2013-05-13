#include "StdAfx.h"
#include "DicomDictionary.h"


CDicomDictionary::CDicomDictionary(void)
{
}


CDicomDictionary::~CDicomDictionary(void)
{
}


map<unsigned int, string> CDicomDictionary::InitTagMap()
{
	map<unsigned int, string> mp;
	mp[0x00020000] = "ULFile Meta Information Group Length";
	mp[0x00020001] = "OBFile Meta Information Version";
	mp[0x00020002] = "UIMedia Storage SOP Class UID";
	mp[0x00020003] ="UIMedia Storage SOP Inst UID";

	mp[0x00080008] = "CSImage type";


	// image data

	return mp;
}
