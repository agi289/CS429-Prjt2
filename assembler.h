#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * Mneumonic enum
 */
enum instr_opcode {
    pushb = 0x00,
    pushs = 0x01,
    pushi = 0x02,
    pushl = 0x03,
    pushf = 0x04,
    pushd = 0x05,
    pushbm = 0x06,
    pushsm = 0x07,
    pushim = 0x08,
    pushlm = 0x09,
    pushfm = 0x0a,
    pushdm = 0x0b,
    pushmm = 0x0c,
    dupb = 0x0d,
    dups = 0x0e,
    dupi = 0x0f,
    dupl = 0x10,
    dupf = 0x11,
    dupd = 0x12,
    popb = 0x13,
    pops = 0x14,
    popi = 0x15,
    popl = 0x16,
    popf = 0x17,
    popd = 0x18,
    popbm = 0x19,
    popsm = 0x1a,
    popim = 0x1b,
    poplm = 0x1c,
    popfm = 0x1d,
    popdm = 0x1e,
    popmm = 0x1f,
    swapb = 0x20,
    swaps = 0x21,
    swapi = 0x22,
    swapl = 0x23,
    swapf = 0x24,
    swapd = 0x25,
    convbs = 0x26,
    convbi = 0x27,
    convbl = 0x28,
    convbf = 0x29,
    convbd = 0x2a,
    convsb = 0x2b,
    convsi = 0x2c,
    convsl = 0x2d,
    convsf = 0x2e,
    convsd = 0x2f,
    convib = 0x30,
    convis = 0x31,
    convil = 0x32,
    convif = 0x33,
    convid = 0x34,
    convlb = 0x35,
    convls = 0x36,
    convli = 0x37,
// Gap
    convlf = 0x39,
    convld = 0x3a,
    convfb = 0x3b,
    convfs = 0x3c,
    convfi = 0x3d,
    convfl = 0x3e,
    convfd = 0x3f,
    convdb = 0x40,
    convds = 0x41,
    convdi = 0x42,
    convdl = 0x43,
    convdf = 0x44,
    inch = 0x45,
    inb = 0x46,
    ins = 0x47,
    ini = 0x48,
    inl = 0x49,
    inf = 0x4a,
    ind = 0x4b,
    outch = 0x4c,
    outb = 0x4d,
    outs = 0x4e,
    outi = 0x4f,
    outl = 0x50,
    outf = 0x51,
    outd = 0x52,
    addb = 0x53,
    adds = 0x54,
    addi = 0x55,
    addl = 0x56,
    addf = 0x57,
    addd = 0x58,
    subb = 0x59,
    subs = 0x5a,
    subi = 0x5b,
    subl = 0x5c,
    subf = 0x5d,
    subd = 0x5e,
    mulb = 0x5f,
    muls = 0x60,
    muli = 0x61,
    mull = 0x62,
    mulf = 0x63,
    muld = 0x64,
    divb = 0x65,
    divs = 0x66,
    divi = 0x67,
    divl = 0x68,
    divf = 0x69,
    divd = 0x6a,
    and8 = 0x6b,
    and16 = 0x6c,
    and32 = 0x6d,
    and64 = 0x6e,
    or8 = 0x6f,
    or16 = 0x70,
    or32 = 0x71,
    or64 = 0x72,
    xor8 = 0x73,
    xor16 = 0x74,
    xor32 = 0x75,
    xor64 = 0x76,
    not8 = 0x77,
    not16 = 0x78,
    not32 = 0x79,
    not64 = 0x7a,
    shftrb = 0x7b,
    shftrs = 0x7c,
    shftri = 0x7d,
    shftrl = 0x7e,
    shftlb = 0x7f,
    shftls = 0x80,
    shftli = 0x81,
    shftll = 0x82,
    jmp = 0x83,
    jrpc = 0x84,
    jind = 0x85,
    jz = 0x86,
    jnz = 0x87,
    jgt = 0x88,
    jlt = 0x89,
    jge = 0x8a,
    jle = 0x8b,
    call = 0x8c,
    returnCall = 0x8d,
    Halt = 0x8e
};

/*
 * Symbol table struct
 * Has a label and an address
 * Used for the instructions and register addresses
 */

typedef struct
{
    char label[64]; // 64 bit
    unsigned int address;
} Symbols;

/* Use for parts of instruction when doing regex checks*/
struct instr_info {
	int size;
	int operands;
	char* regex;
};


























/* opcode.c functions */
/*
 * Gets the size of the instruction
 */
int sizeCheck(enum instr_opcode op);


/*
* Matches string with the opcode 
*/
enum instr_opcode checkCommand(char *instruction, char *endFile, int lineCounterCheck);










/* assembler.c functions */

/*
 * Function to process labels
 * Stores instruction (need to figure out)
 */
void labelProcessor(char *s, FILE *output, unsigned int addressValue, char * outputName);








/* prep.c functions*/

/*
 * Function to process Instructions
 * Utilizes reg & binary function
 */
void instructionsProcessors(char *s, FILE *ptr, char *outputName, int lineCounterInstruc, Symbols table[], int sizeForTable, int max);

/*
 * Function to process label solely in Instructions
 * Deals w addresses
 */
void instructionsLabel(char *rest, FILE *ptr, char *outputName, int lineCounterInstruc, Symbols table[], int sizeForTable, int max );

/*
* Checks spaces (# arguments) correct
*/
void spaceCheck(char *s, int spaces, int lineSpaces, char * outputSpaces);

/*
* Checks space is less than error
*/
void spaceCheckLess(char *s, int spaces, int lineSpaces, char *outputSpaces);









/* Data Processor class*/
/*
* Function that literally converts the data number into binary
*/
void dataProcessor(char *s, FILE *dataptr, char *outputName, int lineCounterCheck, int flag);





















/*
* Checks number is negative or positive with digits (for signed numbers)
*/
void errorCheckDigitNegative (char * stringCheck, int line, char * outputNameCheck);

/*
* Checks number has digits (for unsigned numbers)
*/
void errorCheckDigits (char * stringCheck, int line, char * outputNameCheck);

/*
* Checks that non floating point numbers don't have .
*/
void notFloatingCheck(char *stringCheck, int line, char *outputNameCheck);

/*
* Checks floating point don't have anything besides digit, ., - 
*/
void doubleNoCharactersCheck(char *stringCheck, int line, char *outputNameCheck);


// Functions for converting from string to each type needed

/*
* Checks a string is only characters, ascii 
*/
void isCharactersCheck(char *stringCheck, int line, char *outputNameCheck);
























/*
* Strtol for int8 
*/
int8_t strtolToInt8(char * stringLineStr, int lineCounterCheckStr, char * outputNameStr);

/*
* Strtol for short
*/
int16_t strtolToShort(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);

/*
* Strtol for int
*/
int32_t strtolToInt(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);


/*
* Strtol for long long
*/
int64_t strtolToLongLong(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);


/*
* Strtol for float 
*/
float strtolToFloat(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);


/*
* Strtol for double
*/
double strtolToDouble(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);






















/*
* Strtol for 24 bit memories
* Returns long so have to convert
*/
long strtolTo24(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);


/*
* Convert unsigned int for addresses
*/
uint32_t strtoulToInt(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr);







/*Write Binary.c -- might delete*/

/*
 * Function to binary for signed integers up to a long
 */
void writeBinaryIntSign(FILE * ptr, int64_t value, int numBytes);


/*
 * Function to binary for unsigned integers up to a long
 */
void writeBinaryIntUnsigned(FILE * ptr, uint64_t value, int numBytes);

/*
* Function to binary for signed double
*/
void writeBinaryDoubleSign(FILE * ptr, double value, int numBytes);

/*
* Function to binary for signed float
*/
void writeBinaryFloatSign(FILE * ptr, float value, int numBytes);