#pragma once

#include <map>
#include <string>

namespace command
{

enum commandKeys 
{
	eNOP = 0,
	eBREAK, 
	eEND, 
	eJUMP,
	eCALL,
	eRET,
	eGFLR,
	eSFLR,
	eLOAD,
	eSTORE,
	eLDREL,
	eSTREL,
	ePUSHSF,
	ePOPSF,
	ePUSHA,
	ePOP,
	eASSIGN,
	eSET,
	eMOVE,
	eSWAP,
	eINC,
	eDEC,
	eTEST,
	eCMP,
	eIN,
	eOUT,
	eAND,
	eOR,
	eXOR,
	eNAND,
	eNOR,
	eNOT,
	eSHL,
	eSHR,
	eROL,
	eROR,
	eSAL,
	eSAR,
	eRCL,
	eRCR,
	eADD,
	eADC,
	eSUB,
	eSBB,
	eMUL,
	eIMUL,
	eDIV,
	eIDIV,
	eNEG,
	eCAST,
	ePRINT
};

void mapInit(std::map<std::string, size_t>& comMap);

} // namespace command
