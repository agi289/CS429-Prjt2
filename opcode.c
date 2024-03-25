#include <stdio.h>
#include <string.h>
#include "assembler.h"

/* Checks opcode and returns size of full instruction */
int sizeCheck(enum instr_opcode op)
{
	switch (op)
	{
	case dupb:
	case dups:
	case dupi:
	case dupl:
	case dupf:
	case dupd:
	case popb:
	case pops:
	case popi:
	case popl:
	case popf:
	case popd:
	case swapb:
	case swaps:
	case swapi:
	case swapl:
	case swapf:
	case swapd:
	case convbs:
	case convbi:
	case convbl:
	case convbf:
	case convbd:
	case convsb:
	case convsi:
	case convsl:
	case convsf:
	case convsd:
	case convib:
	case convis:
	case convil:
	case convif:
	case convid:
	case convlb:
	case convls:
	case convli:
	case convlf:
	case convld:
	case convfb:
	case convfs:
	case convfi:
	case convfl:
	case convfd:
	case convdb:
	case convds:
	case convdi:
	case convdl:
	case convdf:
	case inch:
	case inb:
	case ins:
	case ini:
	case inl:
	case inf:
	case ind:
	case outch:
	case outb:
	case outs:
	case outi:
	case outl:
	case outf:
	case outd:
	case addb:
	case adds:
	case addi:
	case addl:
	case addf:
	case addd:
	case subb:
	case subs:
	case subi:
	case subl:
	case subf:
	case subd:
	case mulb:
	case muls:
	case muli:
	case mull:
	case mulf:
	case muld:
	case divb:
	case divs:
	case divi:
	case divl:
	case divf:
	case divd:
	case and8:
	case and16:
	case and32:
	case and64:
	case or8:
	case or16:
	case or32:
	case or64:
	case xor8:
	case xor16:
	case xor32:
	case xor64:
	case not8:
	case not16:
	case not32:
	case not64:
	case jind:
	case returnCall:
	case Halt:
	{
		return 1;
		break;
	}
	case pushb:
	case shftrb:
	case shftrs:
	case shftri:
	case shftrl:
	case shftlb:
	case shftls:
	case shftli:
	case shftll:
	case jrpc:
	{
		return 2;
		break;
	}
	case pushs:
	{
		return 3;
		break;
	}
	case pushbm:
	case pushsm:
	case pushim:
	case pushlm:
	case pushfm:
	case pushdm:
	case popbm:
	case popsm:
	case popim:
	case poplm:
	case popfm:
	case popdm:
	case jz:
	case jnz:
	case jgt:
	case jlt:
	case jge:
	case jle:
	case jmp:
	case call:
	{
		return 4;
		break;
	}
	case pushi:
	case pushf:
	case pushmm:
	case popmm:
	{
		return 5;
		break;
	}
	case pushl:
	case pushd:
	{
		return 9;
		break;
	}
	}
}


/*Checks string and returns opcode*/
enum instr_opcode checkCommand(char *instruction, char *endFile, int lineCounterCheck)
{
	if (strcmp(instruction, "pushb") == 0)
	{
		return pushb;
	}
	else if (strcmp(instruction, "pushs") == 0)
	{
		return pushs;
	}
	else if (strcmp(instruction, "pushi") == 0)
	{
		return pushi;
	}
	else if (strcmp(instruction, "pushl") == 0)
	{
		return pushl;
	}
	else if (strcmp(instruction, "pushf") == 0)
	{
		return pushf;
	}
	else if (strcmp(instruction, "pushd") == 0)
	{
		return pushd;
	}
	else if (strcmp(instruction, "pushbm") == 0)
	{
		return pushbm;
	}
	else if (strcmp(instruction, "pushsm") == 0)
	{
		return pushsm;
	}
	else if (strcmp(instruction, "pushim") == 0)
	{
		return pushim;
	}
	else if (strcmp(instruction, "pushlm") == 0)
	{
		return pushlm;
	}
	else if (strcmp(instruction, "pushfm") == 0)
	{
		return pushfm;
	}
	else if (strcmp(instruction, "pushdm") == 0)
	{
		return pushdm;
	}
	else if (strcmp(instruction, "pushmm") == 0)
	{
		return pushmm;
	}
	else if (strcmp(instruction, "dupb") == 0)
	{
		return dupb;
	}
	else if (strcmp(instruction, "dups") == 0)
	{
		return dups;
	}
	else if (strcmp(instruction, "dupi") == 0)
	{
		return dupi;
	}
	else if (strcmp(instruction, "dupl") == 0)
	{
		return dupl;
	}
	else if (strcmp(instruction, "dupf") == 0)
	{
		return dupf;
	}
	else if (strcmp(instruction, "dupd") == 0)
	{
		return dupd;
	}
	else if (strcmp(instruction, "popb") == 0)
	{
		return popb;
	}
	else if (strcmp(instruction, "pops") == 0)
	{
		return pops;
	}
	else if (strcmp(instruction, "popi") == 0)
	{
		return popi;
	}
	else if (strcmp(instruction, "popl") == 0)
	{
		return popl;
	}
	else if (strcmp(instruction, "popf") == 0)
	{
		return popf;
	}
	else if (strcmp(instruction, "popd") == 0)
	{
		return popd;
	}
	else if (strcmp(instruction, "popbm") == 0)
	{
		return popbm;
	}
	else if (strcmp(instruction, "popsm") == 0)
	{
		return popsm;
	}
	else if (strcmp(instruction, "popim") == 0)
	{
		return popim;
	}
	else if (strcmp(instruction, "poplm") == 0)
	{
		return poplm;
	}
	else if (strcmp(instruction, "popfm") == 0)
	{
		return popfm;
	}
	else if (strcmp(instruction, "popdm") == 0)
	{
		return popdm;
	}
	else if (strcmp(instruction, "popmm") == 0)
	{
		return popmm;
	}
	else if (strcmp(instruction, "swapb") == 0)
	{
		return swapb;
	}
	else if (strcmp(instruction, "swaps") == 0)
	{
		return swaps;
	}
	else if (strcmp(instruction, "swapi") == 0)
	{
		return swapi;
	}
	else if (strcmp(instruction, "swapl") == 0)
	{
		return swapl;
	}
	else if (strcmp(instruction, "swapf") == 0)
	{
		return swapf;
	}
	else if (strcmp(instruction, "swapd") == 0)
	{
		return swapd;
	}
	else if (strcmp(instruction, "convbs") == 0)
	{
		return convbs;
	}
	else if (strcmp(instruction, "convbi") == 0)
	{
		return convbi;
	}
	else if (strcmp(instruction, "convbl") == 0)
	{
		return convbl;
	}
	else if (strcmp(instruction, "convbf") == 0)
	{
		return convbf;
	}
	else if (strcmp(instruction, "convbd") == 0)
	{
		return convbd;
	}
	else if (strcmp(instruction, "convsb") == 0)
	{
		return convsb;
	}
	else if (strcmp(instruction, "convsi") == 0)
	{
		return convsi;
	}
	else if (strcmp(instruction, "convsl") == 0)
	{
		return convsl;
	}
	else if (strcmp(instruction, "convsf") == 0)
	{
		return convsf;
	}
	else if (strcmp(instruction, "convsd") == 0)
	{
		return convsd;
	}
	else if (strcmp(instruction, "convib") == 0)
	{
		return convib;
	}
	else if (strcmp(instruction, "convis") == 0)
	{
		return convis;
	}
	else if (strcmp(instruction, "convil") == 0)
	{
		return convil;
	}
	else if (strcmp(instruction, "convif") == 0)
	{
		return convif;
	}
	else if (strcmp(instruction, "convid") == 0)
	{
		return convid;
	}
	else if (strcmp(instruction, "convlb") == 0)
	{
		return convlb;
	}
	else if (strcmp(instruction, "convls") == 0)
	{
		return convls;
	}
	else if (strcmp(instruction, "convli") == 0)
	{
		return convli;
	}
	else if (strcmp(instruction, "convlf") == 0)
	{
		return convlf;
	}
	else if (strcmp(instruction, "convld") == 0)
	{
		return convld;
	}
	else if (strcmp(instruction, "convfb") == 0)
	{
		return convfb;
	}
	else if (strcmp(instruction, "convfs") == 0)
	{
		return convfs;
	}
	else if (strcmp(instruction, "convfi") == 0)
	{
		return convfi;
	}
	else if (strcmp(instruction, "convfl") == 0)
	{
		return convfl;
	}
	else if (strcmp(instruction, "convfd") == 0)
	{
		return convfd;
	}
	else if (strcmp(instruction, "convdb") == 0)
	{
		return convdb;
	}
	else if (strcmp(instruction, "convds") == 0)
	{
		return convds;
	}
	else if (strcmp(instruction, "convdi") == 0)
	{
		return convdi;
	}
	else if (strcmp(instruction, "convdl") == 0)
	{
		return convdl;
	}
	else if (strcmp(instruction, "convdf") == 0)
	{
		return convdf;
	}
	else if (strcmp(instruction, "inch") == 0)
	{
		return inch;
	}
	else if (strcmp(instruction, "inb") == 0)
	{
		return inb;
	}
	else if (strcmp(instruction, "ins") == 0)
	{
		return ins;
	}
	else if (strcmp(instruction, "ini") == 0)
	{
		return ini;
	}
	else if (strcmp(instruction, "inl") == 0)
	{
		return inl;
	}
	else if (strcmp(instruction, "inf") == 0)
	{
		return inf;
	}
	else if (strcmp(instruction, "ind") == 0)
	{
		return ind;
	}
	else if (strcmp(instruction, "outch") == 0)
	{
		return outch;
	}
	else if (strcmp(instruction, "outb") == 0)
	{
		return outb;
	}
	else if (strcmp(instruction, "outs") == 0)
	{
		return outs;
	}
	else if (strcmp(instruction, "outi") == 0)
	{
		return outi;
	}
	else if (strcmp(instruction, "outl") == 0)
	{
		return outl;
	}
	else if (strcmp(instruction, "outf") == 0)
	{
		return outf;
	}
	else if (strcmp(instruction, "outd") == 0)
	{
		return outd;
	}
	else if (strcmp(instruction, "addb") == 0)
	{
		return addb;
	}
	else if (strcmp(instruction, "adds") == 0)
	{
		return adds;
	}
	else if (strcmp(instruction, "addi") == 0)
	{
		return addi;
	}
	else if (strcmp(instruction, "addl") == 0)
	{
		return addl;
	}
	else if (strcmp(instruction, "addf") == 0)
	{
		return addf;
	}
	else if (strcmp(instruction, "addd") == 0)
	{
		return addd;
	}
	else if (strcmp(instruction, "subb") == 0)
	{
		return subb;
	}
	else if (strcmp(instruction, "subs") == 0)
	{
		return subs;
	}
	else if (strcmp(instruction, "subi") == 0)
	{
		return subi;
	}
	else if (strcmp(instruction, "subl") == 0)
	{
		return subl;
	}
	else if (strcmp(instruction, "subf") == 0)
	{
		return subf;
	}
	else if (strcmp(instruction, "subd") == 0)
	{
		return subd;
	}
	else if (strcmp(instruction, "mulb") == 0)
	{
		return mulb;
	}
	else if (strcmp(instruction, "muls") == 0)
	{
		return muls;
	}
	else if (strcmp(instruction, "muli") == 0)
	{
		return muli;
	}
	else if (strcmp(instruction, "mull") == 0)
	{
		return mull;
	}
	else if (strcmp(instruction, "mulf") == 0)
	{
		return mulf;
	}
	else if (strcmp(instruction, "muld") == 0)
	{
		return muld;
	}
	else if (strcmp(instruction, "divb") == 0)
	{
		return divb;
	}
	else if (strcmp(instruction, "divs") == 0)
	{
		return divs;
	}
	else if (strcmp(instruction, "divi") == 0)
	{
		return divi;
	}
	else if (strcmp(instruction, "divl") == 0)
	{
		return divl;
	}
	else if (strcmp(instruction, "divf") == 0)
	{
		return divf;
	}
	else if (strcmp(instruction, "divd") == 0)
	{
		return divd;
	}
	else if (strcmp(instruction, "and8") == 0)
	{
		return and8;
	}
	else if (strcmp(instruction, "and16") == 0)
	{
		return and16;
	}
	else if (strcmp(instruction, "and32") == 0)
	{
		return and32;
	}
	else if (strcmp(instruction, "and64") == 0)
	{
		return and64;
	}
	else if (strcmp(instruction, "or8") == 0)
	{
		return or8;
	}
	else if (strcmp(instruction, "or16") == 0)
	{
		return or16;
	}
	else if (strcmp(instruction, "or32") == 0)
	{
		return or32;
	}
	else if (strcmp(instruction, "or64") == 0)
	{
		return or64;
	}
	else if (strcmp(instruction, "xor8") == 0)
	{
		return xor8;
	}
	else if (strcmp(instruction, "xor16") == 0)
	{
		return xor16;
	}
	else if (strcmp(instruction, "xor32") == 0)
	{
		return xor32;
	}
	else if (strcmp(instruction, "xor64") == 0)
	{
		return xor64;
	}
	else if (strcmp(instruction, "not8") == 0)
	{
		return not8;
	}
	else if (strcmp(instruction, "not16") == 0)
	{
		return not16;
	}
	else if (strcmp(instruction, "not32") == 0)
	{
		return not32;
	}
	else if (strcmp(instruction, "not64") == 0)
	{
		return not64;
	}
	else if (strcmp(instruction, "shftrb") == 0)
	{
		return shftrb;
	}
	else if (strcmp(instruction, "shftrs") == 0)
	{
		return shftrs;
	}
	else if (strcmp(instruction, "shftri") == 0)
	{
		return shftri;
	}
	else if (strcmp(instruction, "shftrl") == 0)
	{
		return shftrl;
	}
	else if (strcmp(instruction, "shftlb") == 0)
	{
		return shftlb;
	}
	else if (strcmp(instruction, "shftls") == 0)
	{
		return shftls;
	}
	else if (strcmp(instruction, "shftli") == 0)
	{
		return shftli;
	}
	else if (strcmp(instruction, "shftll") == 0)
	{
		return shftll;
	}
	else if (strcmp(instruction, "jmp") == 0)
	{
		return jmp;
	}
	else if (strcmp(instruction, "jrpc") == 0)
	{
		return jrpc;
	}
	else if (strcmp(instruction, "jind") == 0)
	{
		return jind;
	}
	else if (strcmp(instruction, "jz") == 0)
	{
		return jz;
	}
	else if (strcmp(instruction, "jnz") == 0)
	{
		return jnz;
	}
	else if (strcmp(instruction, "jgt") == 0)
	{
		return jgt;
	}
	else if (strcmp(instruction, "jlt") == 0)
	{
		return jlt;
	}
	else if (strcmp(instruction, "jge") == 0)
	{
		return jge;
	}
	else if (strcmp(instruction, "jle") == 0)
	{
		return jle;
	}
	else if (strcmp(instruction, "call") == 0)
	{
		return call;
	}
	else if (strcmp(instruction, "return") == 0)
	{
		return returnCall;
	}
	else if (strcmp(instruction, "halt") == 0)
	{
		return Halt;
	}
	else
	{
		fprintf(stderr, "Error on line %d\n", lineCounterCheck);
		remove(endFile);
		exit(EXIT_FAILURE);
	}
}