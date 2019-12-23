#include "Command.h"

#include <iostream>
#include <cassert>
#include <map>

namespace command
{

void mapInit(std::map<std::string, size_t>& comMap)
{
	comMap["NOP"]	 = eNOP;
	comMap["BREAK"]	 = eBREAK;
	comMap["END"]	 = eEND;
	comMap["JUMP"]   = eJUMP;
	comMap["CALL"]   = eCALL;
	comMap["RET"]	 = eRET;
	comMap["GFLR"]   = eGFLR;
	comMap["SFLR"]   = eSFLR;
	comMap["LOAD"]   = eLOAD;
	comMap["STORE"]  = eSTORE;
	comMap["LDREL"]  = eLDREL;
	comMap["STREL"]  = eSTREL;
	comMap["PUSHSF"] = ePUSHSF;
	comMap["POPSF"]  = ePOPSF;
	comMap["PUSHA"]  = ePUSHA;
	comMap["POP"]	 = ePOP;
	comMap["ASSIGN"] = eASSIGN;
	comMap["SET"]	 = eSET;
	comMap["MOVE"]	 = eMOVE;
	comMap["SWAP"]   = eSWAP;
	comMap["INC"]    = eINC;
	comMap["DEC"]    = eDEC;
	comMap["TEST"]   = eTEST;
	comMap["CMP"]	 = eCMP;
	comMap["IN"]     = eIN;
	comMap["OUT"]    = eOUT;
	comMap["AND"]    = eAND;
	comMap["OR"]	 = eOR;
	comMap["XOR"]	 = eXOR;
	comMap["NAND"]   = eNAND;
	comMap["NOR"]	 = eNOR;
	comMap["NOT"]	 = eNOT;
	comMap["SHL"]	 = eSHL;
	comMap["SHR"]	 = eSHR;
	comMap["ROL"]	 = eROL;
	comMap["ROR"]	 = eROR;
	comMap["SAL"]	 = eSAL;
	comMap["SAR"]	 = eSAR;
	comMap["RCL"]	 = eRCL;
	comMap["RCR"]	 = eRCR;
	comMap["ADD"]	 = eADD;
	comMap["ADC"]	 = eADC;
	comMap["SUB"]	 = eSUB;
	comMap["SBB"]	 = eSBB;
	comMap["MUL"]	 = eMUL;
	comMap["IMUL"]   = eIMUL;
	comMap["DIV"]	 = eDIV;
	comMap["IDIV"]   = eIDIV;
	comMap["NEG"]	 = eNEG;
	comMap["CAST"]	 = eCAST;
	comMap["PRINT"]  = ePRINT;
}

} // namespace command
