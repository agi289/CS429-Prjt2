#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "simulator.h"

#define MEMORY_SIZE 512 * 1024 // 512 KB, or just do 512?

/*Global variables*/
uint32_t PC = 0;
uint32_t sp = 0x40000;
uint8_t memory[MEMORY_SIZE];

/*Memory Functions*/

/*
 * Read memory
 * Returns the memory stored at the given address
 */
uint64_t readMemory(uint64_t address, int nbytes)
{
    uint64_t final = 0b0ull;

    for (int i = 0; i < nbytes; i++)
    {
        if ((address + i < 0) || (address < 0) || (i < 0) || (address + i >= MEMORY_SIZE))
        {
            fprintf(stderr, "Simulation error\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            final |= (((uint64_t)memory[address + i]) << (8 * (nbytes - 1 - i)));
        }
    }

    return final;
}

/*
 * Write Memory
 * Inputs a value in the memory stored at a given address
 */
void writeMemory(uint64_t address, uint64_t data, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
    {
        if ((address + i >= MEMORY_SIZE) || (address + i < 0) || (address < 0 || i < 0))
        {
            fprintf(stderr, "Simulation error\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            memory[address + i] = ((uint64_t)data >> (8 * (nbytes - i - 1)));
        }
    }
}

/* Helper functions */
/*
 * Helper function
 * Whenever do don't do sp increment done here
 */

// int8
int8_t _popb()
{
    uint64_t resultpop = readMemory((sp - 1), 1);
    sp -= 1;
    return (int8_t)resultpop;
}

void _pushb(int8_t input)
{
    writeMemory(sp, input, 1);
    sp += 1;
}

// short
short _pops()
{
    uint64_t resultpop = readMemory((sp - 2), 2);
    sp -= 2;
    return (short)resultpop;
}

void _pushs(short input)
{
    writeMemory(sp, input, 2);
    sp += 2;
}

// int
int _popi()
{
    uint64_t resultpop = readMemory((sp - 4), 4);
    sp -= 4;
    return (int)resultpop;
}

void _pushi(int input)
{
    writeMemory(sp, input, 4);
    sp += 4;
}

// long
long _popl()
{
    uint64_t resultpop = readMemory((sp - 8), 8);
    sp -= 8;
    return (long)resultpop;
}

void _pushl(long input)
{
    writeMemory(sp, input, 8);
    sp += 8;
}

// float

float _popf()
{
    uint64_t resultpop = readMemory((sp - 4), 4);
    sp -= 4;
    return *(float *)&resultpop;
}

void _pushf(float input)
{
    writeMemory(sp, *(uint64_t *)&input, 4);
    sp += 4;
}

// doubel
double _popd()
{
    uint64_t resultpop = readMemory((sp - 8), 8);
    sp -= 8;
    return *(double *)&resultpop;
}

void _pushd(double input)
{
    writeMemory(sp, *(uint64_t *)&input, 8);
    sp += 8;
}

/* Functions */

// push value //////////////////////////////////////////////////////////////////////////////////////////////////

void pushb()
{
    int8_t value = readMemory(PC + 1, 1);
    writeMemory(sp, value, 1);

    sp = sp + 1;
    PC = PC + 2;
}

void pushs()
{
    short value = readMemory(PC + 1, 2);
    writeMemory(sp, value, 2);

    sp = sp + 2;
    PC = PC + 3;
}

void pushi()
{
    int value = readMemory(PC + 1, 4);
    writeMemory(sp, value, 4);

    sp = sp + 4;
    PC = PC + 5;
}

void pushl()
{
    long value = readMemory(PC + 1, 8);
    writeMemory(sp, value, 8);

    sp = sp + 8;
    PC = PC + 9;
}

void pushf()
{
    uint64_t value = readMemory(PC + 1, 4);
    float input = *(float *)&value;
    writeMemory(sp, *(uint64_t *)&input, 4);

    sp = sp + 4;
    PC = PC + 5;
}

void pushd()
{
    uint64_t value = readMemory(PC + 1, 8);
    double input = *(double *)&value;
    writeMemory(sp, *(uint64_t *)&input, 8);

    sp = sp + 8;
    PC = PC + 9;
}

// //pushbm /////////////////////////////////////////////////////////////////////////////////////////

void pushbm()
{
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    // used address as a pointer to read 4 byte value (for memory have to do readmemory twice)
    uint64_t int8Stored = readMemory(address, 1);
    int8_t int8Final = int8Stored;
    writeMemory(sp, int8Stored, 1);

    sp += 1;
    PC += 4;
}

void pushsm()
{
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    // used address as a pointer to read 4 byte value (for memory have to do readmemory twice)
    uint64_t shortStored = readMemory(address, 2);
    short shortFinal = shortStored;
    writeMemory(sp, shortStored, 2);

    sp += 2;
    PC += 4;
}

void pushim()
{
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    // used address as a pointer to read 4 byte value (for memory have to do readmemory twice)
    uint64_t intStored = readMemory(address, 4);
    int intFinal = intStored;
    writeMemory(sp, intStored, 4);

    sp += 4;
    PC += 4;
}

void pushlm()
{
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    // used address as a pointer to read 4 byte value (for memory have to do readmemory twice)
    uint64_t longStored = readMemory(address, 8);
    long longFinal = longStored;
    writeMemory(sp, longStored, 8);

    sp += 8;
    PC += 4;
}

void pushfm()
{
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    // used address as a pointer to read 4 byte value (for memory have to do readmemory twice)
    uint64_t floatStored = readMemory(address, 4);
    float floatFinal = *(float *)&floatStored;

    writeMemory(sp, *(uint64_t *)&floatStored, 4);

    sp += 4;
    PC += 4;
}

void pushdm()
{
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    // used address as a pointer to read 8 byte value (for memory have to do readmemory twice)
    uint64_t doubleStored = readMemory(address, 8);
    double doubleFinal = *(double *)&doubleStored;

    writeMemory(sp, *(uint64_t *)&doubleFinal, 8);

    sp += 8;
    PC += 4;
}

// pushmm

void pushmm()
{
    uint32_t address = readMemory(PC + 1, 3);
    int8_t items = readMemory(PC + 4, 1);
    for (int i = 0; i < items; i++)
    {
        int read = readMemory(address + i, 1);
        writeMemory(sp + i, read, 1);
    }
    sp = sp + items;
    PC = PC + 5;
}

// dup //////////////////////////////////////////////////////////////////////////////////////////////////

void dupb()
{
    int8_t replace = readMemory(sp - 1, 1);
    writeMemory(sp, replace, 1);

    sp = sp + 1;
    PC = PC + 1;
}

void dups()
{
    short replace = readMemory(sp - 2, 2);
    writeMemory(sp, replace, 2);

    sp = sp + 2;
    PC = PC + 1;
}

void dupi()
{
    int replace = readMemory(sp - 4, 4);
    writeMemory(sp, replace, 4);

    sp = sp + 4;
    PC = PC + 1;
}

void dupl()
{
    long replace = readMemory(sp - 8, 8);
    writeMemory(sp, replace, 8);

    sp = sp + 8;
    PC = PC + 1;
}

void dupf()
{
    uint64_t replaceFloat = readMemory(sp - 4, 4);
    float replaceHere = *(float *)&replaceFloat;
    writeMemory(sp, *(uint64_t *)&replaceHere, 4);

    sp = sp + 4;
    PC = PC + 1;
}

void dupd()
{
    uint64_t replace = readMemory(sp - 8, 8);
    double replaceHere = *(double *)&replace;
    writeMemory(sp, *(uint64_t *)&replaceHere, 8);

    sp = sp + 8;
    PC = PC + 1;
}

// pop /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void popb()
{
    sp = sp - 1;
    PC = PC + 1;
}

void pops()
{
    sp = sp - 2;
    PC = PC + 1;
}

void popi()
{
    sp = sp - 4;
    PC = PC + 1;
}

void popl()
{
    sp = sp - 8;
    PC = PC + 1;
}

void popf()
{
    sp = sp - 4;
    PC = PC + 1;
}

void popd()
{
    sp = sp - 8;
    PC = PC + 1;
}

// popbm

void popbm()
{
    sp = sp - 1;
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    uint64_t int8Store = readMemory(sp, 1);
    int8_t int8Final = int8Store;

    writeMemory(address, int8Final, 1);
    PC += 4;
}

void popsm()
{
    sp = sp - 2;
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    uint64_t shortStore = readMemory(sp, 2);
    short shortFinal = shortStore;

    writeMemory(address, shortFinal, 2);
    PC += 4;
}

void popim()
{
    sp = sp - 4;
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    uint64_t intStore = readMemory(sp, 4);
    int intFinal = intStore;

    writeMemory(address, intFinal, 4);
    PC += 4;
}

void poplm()
{
    sp = sp - 8;
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    uint64_t longStore = readMemory(sp, 8);
    long longFinal = longStore;

    writeMemory(address, longFinal, 8);
    PC += 4;
}

void popfm()
{
    sp = sp - 4;
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    uint64_t floatStore = readMemory(sp, 4);
    float floatFinal = *(float *)&floatStore;

    writeMemory(address, *(uint64_t *)&floatFinal, 4);
    PC += 4;
}

void popdm()
{
    sp = sp - 8;
    // reading address store din binary that's 3 bytes
    uint32_t address = readMemory(PC + 1, 3);

    uint64_t longStore = readMemory(sp, 8);
    double longFinal = *(double *)&longStore;

    writeMemory(address, *(uint64_t *)&longFinal, 8);
    PC += 4;
}

// popmm ////////////////////////////////////////////////////////////////////////////////////////////////////////////

void popmm()
{
    uint32_t address = readMemory(PC + 1, 3);
    int items = readMemory(PC + 4, 1);
    sp = sp - items;
    for (int i = 0; i < items; i++)
    {
        int start = readMemory(sp + i, 1);
        writeMemory(address + i, start, 1);
    }
    PC = PC + 5;
}

// swap ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void swapb()
{
    int8_t tmp = _popb();
    int8_t place = _popb();
    writeMemory(sp - 1, place, 1);
    writeMemory(sp - 2, tmp, 1);
    PC = PC + 1;
}

void swaps()
{
    short tmp = _pops();
    short place = _pops();
    writeMemory(sp - 2, place, 2);
    writeMemory(sp - 4, tmp, 2);
    PC = PC + 1;
}

void swapi()
{
    int tmp = _popi();
    int place = _popi();
    writeMemory(sp - 4, place, 4);
    writeMemory(sp - 8, tmp, 4);
    PC = PC + 1;
}

void swapl()
{
    long tmp = _popl();
    long place = _popl();
    writeMemory(sp - 8, place, 8);
    writeMemory(sp - 16, tmp, 8);
    PC = PC + 1;
}

void swapf()
{
    float tmp = _popf();
    float place = _popf();
    writeMemory(sp - 4, *(uint64_t *)&place, 4);
    writeMemory(sp - 8, *(uint64_t *)&tmp, 4);
    PC = PC + 1;
}

void swapd()
{
    double tmp = _popd();
    double place = _popd();
    writeMemory(sp - 8, *(uint64_t *)&place, 8);
    writeMemory(sp - 16, *(uint64_t *)&tmp, 8);
    PC = PC + 1;
}

/*Functions to convert*/
void convbs()
{
    // read 1 byte from sp-1
    int8_t byte = readMemory(sp - 1, 1);

    short newValue = (short)byte;

    writeMemory(sp - 1, *(uint16_t *)&newValue, 2);

    sp = sp + 1;
    PC = PC + 1;
}

void convbi()
{
    // read 1 byte from sp-1
    int8_t byte = readMemory(sp - 1, 1);

    int newValue = (int)byte;

    writeMemory(sp - 1, *(uint32_t *)&newValue, 4);

    sp = sp + 3;
    PC = PC + 1;
}

void convbl()
{
    // read 1 byte from sp-1
    int8_t byte = readMemory(sp - 1, 1);

    long newValue = (long)byte;

    writeMemory(sp - 1, *(uint64_t *)&newValue, 8);

    sp = sp + 7;
    PC = PC + 1;
}

void convbf()
{
    // read 1 byte from sp-1
    int8_t byte = readMemory(sp - 1, 1);

    float newValue = (float)byte;

    writeMemory(sp - 1, *(uint32_t *)&newValue, 4);

    sp = sp + 3;
    PC = PC + 1;
}

void convbd()
{
    // read 1 byte from sp-1
    int8_t byte = readMemory(sp - 1, 1);

    double newValue = (double)byte;

    writeMemory(sp - 1, *(uint64_t *)&newValue, 8);

    sp = sp + 7;
    PC = PC + 1;
}

void convsb()
{
    // read 1 byte from sp-1
    short shortVal = readMemory(sp - 2, 2);

    int8_t newValue = (int8_t)shortVal;

    writeMemory(sp - 2, *(uint8_t *)&newValue, 1);

    sp = sp - 1;
    PC = PC + 1;
}

void convsi()
{
    // read 1 byte from sp-1
    short shortVal = readMemory(sp - 2, 2);

    int newValue = (int)shortVal;

    writeMemory(sp - 2, *(uint32_t *)&newValue, 4);

    sp = sp + 2;
    PC = PC + 1;
}

void convsl()
{
    // read 1 byte from sp-1
    short shortVal = readMemory(sp - 2, 2);

    long newValue = (long)shortVal;

    writeMemory(sp - 2, *(uint64_t *)&newValue, 8);

    sp = sp + 6;
    PC = PC + 1;
}

void convsf()
{
    // read 1 byte from sp-1
    int16_t shortVal = readMemory(sp - 2, 2);

    float newValue = (float)shortVal;

    writeMemory(sp - 2, *(uint32_t *)&newValue, 4);

    sp = sp + 2;
    PC = PC + 1;
}

void convsd()
{
    // read 1 byte from sp-1
    int16_t shortVal = readMemory(sp - 2, 2);

    double newValue = (double)shortVal;

    writeMemory(sp - 2, *(uint64_t *)&newValue, 8);

    sp = sp + 6;
    PC = PC + 1;
}

void convib()
{
    int intVal = readMemory(sp - 4, 4);

    int8_t byte = (int8_t)intVal;
    writeMemory(sp - 4, *(uint8_t *)&byte, 1);

    sp = sp - 3;
    PC = PC + 1;
}

void convis()
{
    int intVal = readMemory(sp - 4, 4);

    short byte = (short)intVal;
    writeMemory(sp - 4, *(uint16_t *)&byte, 2);

    sp = sp - 2;
    PC = PC + 1;
}

void convil()
{
    int intVal = readMemory(sp - 4, 4);

    long byte = (long)intVal;
    writeMemory(sp - 4, *(uint64_t *)&byte, 8);

    sp = sp + 4;
    PC = PC + 1;
}

void convif()
{
    int32_t intVal = readMemory(sp - 4, 4);

    float byte = (float)intVal;
    writeMemory(sp - 4, *(uint32_t *)&byte, 4);

    PC = PC + 1;
}

void convid()
{
    int32_t intVal = readMemory(sp - 4, 4);

    double byte = (double)intVal;
    writeMemory(sp - 4, *(uint64_t *)&byte, 8);

    sp = sp + 4;
    PC = PC + 1;
}

// long

void convlb()
{
    long intVal = readMemory(sp - 8, 8);

    int8_t byte = (int8_t)intVal;
    writeMemory(sp - 8, *(uint8_t *)&byte, 1);

    sp = sp - 7;
    PC = PC + 1;
}

void convls()
{
    long intVal = readMemory(sp - 8, 8);

    short byte = (short)intVal;
    writeMemory(sp - 8, *(uint16_t *)&byte, 2);

    sp = sp - 6;
    PC = PC + 1;
}

void convli()
{
    long intVal = readMemory(sp - 8, 8);

    int byte = (int)intVal;
    writeMemory(sp - 8, *(uint32_t *)&byte, 4);

    sp = sp - 4;
    PC = PC + 1;
}

void convlf()
{
    int64_t intVal = readMemory(sp - 8, 8);

    float byte = (float)intVal;
    writeMemory(sp - 8, *(uint32_t *)&byte, 4);

    sp = sp - 4;
    PC = PC + 1;
}

void convld()
{
    int64_t intVal = readMemory(sp - 8, 8);

    double byte = (double)intVal;
    writeMemory(sp - 8, *(uint64_t *)&byte, 8);

    PC = PC + 1;
}

// float

void convfb()
{
    uint32_t pass = readMemory((sp - 4), 4);
    int8_t passIn = *(float *)&pass;
    int8_t finalPass = (int8_t)passIn;

    writeMemory((sp - 4), *(uint8_t *)&finalPass, 1);
    sp = sp - 3;
    PC = PC + 1;
}

void convfs()
{
    uint32_t pass = readMemory((sp - 4), 4);
    short passIn = *(float *)&pass;
    short finalPass = (short)passIn;

    writeMemory((sp - 4), *(uint16_t *)&finalPass, 2);
    sp = sp - 2;
    PC = PC + 1;
}

void convfi()
{
    uint32_t pass = readMemory((sp - 4), 4);
    int passIn = *(float *)&pass;
    int finalPass = (int)passIn;

    writeMemory((sp - 4), *(uint32_t *)&finalPass, 4);
    PC = PC + 1;
}

void convfl()
{
    uint32_t pass = readMemory((sp - 4), 4);
    long passIn = *(float *)&pass;
    long finalPass = (long)passIn;

    writeMemory((sp - 4), *(uint64_t *)&finalPass, 8);
    sp = sp + 4;
    PC = PC + 1;
}

void convfd()
{
    uint32_t pass = readMemory((sp - 4), 4);
    double passIn = *(float *)&pass;
    double finalPass = (double)passIn;

    writeMemory((sp - 4), *(uint64_t *)&finalPass, 8);
    sp = sp + 4;
    PC = PC + 1;
}

// double

void convdb()
{
    uint64_t pass = readMemory((sp - 8), 8);
    double passIn = *(double *)&pass;
    int8_t finalPass = (int8_t)passIn;

    writeMemory((sp - 8), *(uint8_t *)&finalPass, 1);
    sp = sp - 7;
    PC = PC + 1;
}

void convds()
{
    uint64_t pass = readMemory((sp - 8), 8);
    double passIn = *(double *)&pass;
    short finalPass = (short)passIn;

    writeMemory((sp - 8), *(uint16_t *)&finalPass, 2);
    sp = sp - 6;
    PC = PC + 1;
}

void convdi()
{
    uint64_t pass = readMemory((sp - 8), 8);
    double passIn = *(double *)&pass;
    int finalPass = (int)passIn;

    writeMemory((sp - 8), *(uint32_t *)&finalPass, 4);
    sp = sp - 4;
    PC = PC + 1;
}

void convdl()
{
    uint64_t pass = readMemory((sp - 8), 8);
    double passIn = *(double *)&pass;
    long finalPass = (long)passIn;

    writeMemory((sp - 8), *(uint64_t *)&finalPass, 8);
    PC = PC + 1;
}

void convdf()
{
    uint64_t pass = readMemory((sp - 8), 8);
    double passIn = *(double *)&pass;
    float finalPass = (float)passIn;

    writeMemory((sp - 8), *(uint32_t *)&finalPass, 4);
    sp = sp - 4;
    PC = PC + 1;
}

// in ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void inch()
{
    char scan[1000];
    scanf("%s", scan);

    /*It's just one char*/
    if (strlen(scan) > 1)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    if (scan[0] > 127 || scan[0] < -128)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    char s = scan[0];

    writeMemory(sp, *(uint64_t *)&s, 1);

    PC = PC + 1;
    sp = sp + 1;
}

void inb()
{
    char scanCheck[1000];
    scanf("%s", scanCheck);

    int8_t scan = strtolToInt8Sim(scanCheck);
    writeMemory(sp, *(uint64_t *)&scan, 1);

    PC = PC + 1;
    sp = sp + 1;
}

void ins()
{
    char scanCheck[1000];
    scanf("%s", scanCheck);

    short scan = strtolToShortSim(scanCheck);
    writeMemory(sp, *(uint64_t *)&scan, 2);

    PC = PC + 1;
    sp = sp + 2;
}

void ini()
{
    char scanCheck[1000];
    scanf("%s", scanCheck);

    int scan = strtolToIntSim(scanCheck);
    writeMemory(sp, *(uint64_t *)&scan, 4);

    PC = PC + 1;
    sp = sp + 4;
}

void inl()
{
    char scanCheck[1000];
    scanf("%s", scanCheck);

    long scan = strtolToLongLongSim(scanCheck);
    writeMemory(sp, *(uint64_t *)&scan, 8);

    PC = PC + 1;
    sp = sp + 8;
}

void inf()
{
    char scanCheck[1000];
    scanf("%s", scanCheck);

    float scan = strtolToFloatSim(scanCheck);
    writeMemory(sp, *(uint64_t *)&scan, 4);

    PC = PC + 1;
    sp = sp + 4;
}

void ind()
{
    char scanCheck[1000];
    scanf("%s", scanCheck);

    double scan = strtolToDoubleSim(scanCheck);
    writeMemory(sp, *(uint64_t *)&scan, 8);

    PC = PC + 1;
    sp = sp + 8;
}

// out ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void outch()
{
    sp = sp - 1;
    uint64_t read = readMemory(sp, 1);
    char newValue = (char)read;
    printf("%c\n", newValue);
    PC = PC + 1;
}

void outb()
{
    sp = sp - 1;
    uint64_t read = readMemory(sp, 1);
    int8_t newValue = (int8_t)read;
    printf("%d\n", newValue);
    PC = PC + 1;
}

void outs()
{
    sp = sp - 2;
    uint64_t read = readMemory(sp, 2);
    short newValue = (short)read;
    printf("%d\n", newValue);
    PC = PC + 1;
}

void outi()
{
    sp = sp - 4;
    uint64_t read = readMemory(sp, 4);
    int newValue = (int)read;
    printf("%d\n", newValue);
    PC = PC + 1;
}

void outl()
{
    sp = sp - 8;
    uint64_t read = readMemory(sp, 8);
    long newValue = (long)read;
    printf("%ld\n", newValue);
    PC = PC + 1;
}

void outf()
{
    sp = sp - 4;
    uint64_t read = readMemory(sp, 4);
    float newValue = *(float *)&read;
    printf("%f\n", newValue);
    PC = PC + 1;
}

void outd()
{
    sp = sp - 8;
    uint64_t read = readMemory(sp, 8);
    double newValue = *(double *)&read;
    printf("%lf\n", newValue);
    PC = PC + 1;
}

// add /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void addb()
{
    int8_t second = _popb();
    int8_t first = _popb();
    _pushb((first + second));
    PC = PC + 1;
}

void adds()
{
    short second = _pops();
    short first = _pops();
    _pushs((first + second));
    PC = PC + 1;
}

void addi()
{
    int second = _popi();
    int first = _popi();
    _pushi((first + second));
    PC = PC + 1;
}

void addl()
{
    long second = _popl();
    long first = _popl();
    _pushl((first + second));
    PC = PC + 1;
}

void addf()
{
    float second = _popf();
    float first = _popf();
    _pushf((first + second));
    PC = PC + 1;
}

void addd()
{
    double second = _popd();
    double first = _popd();
    _pushd((first + second));
    PC = PC + 1;
}

// sub /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void subb()
{
    int8_t second = _popb();
    int8_t first = _popb();
    _pushb((first - second));
    PC = PC + 1;
}

void subs()
{
    short second = _pops();
    short first = _pops();
    _pushs((first - second));
    PC = PC + 1;
}

void subi()
{
    int second = _popi();
    int first = _popi();
    _pushi((first - second));
    PC = PC + 1;
}

void subl()
{
    long second = _popl();
    long first = _popl();
    _pushl((first - second));
    PC = PC + 1;
}

void subf()
{
    float second = _popf();
    float first = _popf();
    _pushf((first - second));
    PC = PC + 1;
}

void subd()
{
    double second = _popd();
    double first = _popd();
    _pushd((first - second));
    PC = PC + 1;
}

// mul /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mulb()
{
    int8_t second = _popb();
    int8_t first = _popb();
    _pushb((first * second));
    PC = PC + 1;
}

void muls()
{
    short second = _pops();
    short first = _pops();
    _pushs((first * second));
    PC = PC + 1;
}

void muli()
{
    int second = _popi();
    int first = _popi();
    _pushi((first * second));
    PC = PC + 1;
}

void mull()
{
    long second = _popl();
    long first = _popl();
    _pushl((first * second));
    PC = PC + 1;
}

void mulf()
{
    float second = _popf();
    float first = _popf();
    _pushf((first * second));
    PC = PC + 1;
}

void muld()
{
    double second = _popd();
    double first = _popd();
    _pushd((first * second));
    PC = PC + 1;
}

// div /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void divb()
{
    int8_t second = _popb();
    if (second == 0)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    int8_t first = _popb();
    _pushb((first / second));
    PC = PC + 1;
}

void divs()
{
    short second = _pops();
    if (second == 0)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    short first = _pops();
    _pushs((first / second));
    PC = PC + 1;
}

void divi()
{
    int second = _popi();
    if (second == 0)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    int first = _popi();
    _pushi((first / second));
    PC = PC + 1;
}

void divl()
{
    long second = _popl();
    if (second == 0)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    long first = _popl();
    _pushl((first / second));
    PC = PC + 1;
}

void divf()
{
    float second = _popf();
    if (second == 0.0)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    float first = _popf();
    _pushf((first / second));
    PC = PC + 1;
}

void divd()
{
    double second = _popd();
    if (second == 0.0)
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
    double first = _popd();
    _pushd((first / second));
    PC = PC + 1;
}

// and /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void and8()
{
    int8_t second = _popb();
    int8_t first = _popb();
    _pushb((first & second));
    PC = PC + 1;
}

void and16()
{
    short second = _pops();
    short first = _pops();
    _pushs((first & second));
    PC = PC + 1;
}

void and32()
{
    int second = _popi();
    int first = _popi();
    _pushi((first & second));
    PC = PC + 1;
}

void and64()
{
    long second = _popl();
    long first = _popl();
    _pushl((first & second));
    PC = PC + 1;
}

// or /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void or8()
{
    int8_t second = _popb();
    int8_t first = _popb();
    _pushb((first | second));
    PC = PC + 1;
}

void or16()
{
    short second = _pops();
    short first = _pops();
    _pushs((first | second));
    PC = PC + 1;
}

void or32()
{
    int second = _popi();
    int first = _popi();
    _pushi((first | second));
    PC = PC + 1;
}

void or64()
{
    long second = _popl();
    long first = _popl();
    _pushl((first | second));
    PC = PC + 1;
}

// xor /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void xor8()
{
    int8_t second = _popb();
    int8_t first = _popb();
    _pushb((first ^ second));
    PC = PC + 1;
}

void xor16()
{
    short second = _pops();
    short first = _pops();
    _pushs((first ^ second));
    PC = PC + 1;
}

void xor32()
{
    int second = _popi();
    int first = _popi();
    _pushi((first ^ second));
    PC = PC + 1;
}

void xor64()
{
    long second = _popl();
    long first = _popl();
    _pushl((first ^ second));
    PC = PC + 1;
}

// not /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void not8()
{
    int8_t first = _popb();
    _pushb((~first));
    PC = PC + 1;
}

void not16()
{
    short first = _pops();
    _pushs((~first));
    PC = PC + 1;
}

void not32()
{
    int first = _popi();
    _pushi((~first));
    PC = PC + 1;
}

void not64()
{
    long first = _popl();
    _pushl((~first));
    PC = PC + 1;
}

// shftr

void shftrb()
{
    int8_t stored = readMemory(sp - 1, 1);
    int8_t value = readMemory(PC + 1, 1);
    int8_t valueShift = stored >> value;
    writeMemory(sp - 1, valueShift, 1);
    PC = PC + 2;
}

void shftrs()
{
    short stored = readMemory(sp - 2, 2);
    short value = readMemory(PC + 1, 1);
    short valueShift = stored >> value;
    writeMemory(sp - 2, valueShift, 2);
    PC = PC + 2;
}

void shftri()
{
    int stored = readMemory(sp - 4, 4);
    int value = readMemory(PC + 1, 1);
    int valueShift = stored >> value;
    writeMemory(sp - 4, valueShift, 4);
    PC = PC + 2;
}

void shftrl()
{
    long stored = readMemory(sp - 8, 8);
    long value = readMemory(PC + 1, 1);
    long valueShift = stored >> value;
    writeMemory(sp - 8, valueShift, 8);
    PC = PC + 2;
}

// shftl

void shftlb()
{
    int8_t stored = readMemory(sp - 1, 1);
    int8_t value = readMemory(PC + 1, 1);
    int8_t valueShift = stored << value;
    writeMemory(sp - 1, valueShift, 1);
    PC = PC + 2;
}

void shftls()
{
    short stored = readMemory(sp - 2, 2);
    short value = readMemory(PC + 1, 1);
    short valueShift = stored << value;
    writeMemory(sp - 2, valueShift, 2);
    PC = PC + 2;
}

void shftli()
{
    int stored = readMemory(sp - 4, 4);
    int value = readMemory(PC + 1, 1);
    int valueShift = stored << value;
    writeMemory(sp - 4, valueShift, 4);
    PC = PC + 2;
}

void shftll()
{
    long stored = readMemory(sp - 8, 8);
    long value = readMemory(PC + 1, 1);
    long valueShift = stored << value;
    writeMemory(sp - 8, valueShift, 8);
    PC = PC + 2;
}

// jumps
void jmp()
{
    uint32_t address = readMemory(PC + 1, 3);
    PC = address;
}

void jrpc()
{
    int8_t offset = readMemory(PC + 1, 1);
    PC += offset;
}

// jind and jumps (check from here)

void jind()
{
    int value = readMemory(sp - 4, 4);
    PC = value;
}


void jz()
{
    uint32_t address = readMemory(PC + 1, 3);
    
    int value = readMemory(sp - 4, 4);

    PC = value == 0 ? address : PC+4;
}

void jnz()
{
    uint32_t address = readMemory(PC + 1, 3);
    
    int value = readMemory(sp - 4, 4);

    PC = value != 0 ? address : PC+4;
}

void jgt()
{
    uint32_t address = readMemory(PC + 1, 3);
    
    int value = readMemory(sp - 4, 4);

    PC = value > 0 ? address : PC+4;
}

void jlt()
{
    uint32_t address = readMemory(PC + 1, 3);
    
    int value = readMemory(sp - 4, 4);

    PC = value < 0 ? address : PC+4;
}

void jge()
{
    uint32_t address = readMemory(PC + 1, 3);
    
    int value = readMemory(sp - 4, 4);

    PC = value >= 0 ? address : PC+4;
}

void jle()
{
    uint32_t address = readMemory(PC + 1, 3);
    
    int value = readMemory(sp - 4, 4);

    PC = value <= 0 ? address : PC+4;
}


// call and return

void call()
{
    uint32_t address = readMemory(PC + 1, 3);

    writeMemory(sp, PC+4, 4);
    sp = sp + 4;

    PC = address;
}

void returnCall()
{
    sp = sp - 4;
    PC = readMemory(sp, 4);
    
}

// check this section


/// halt //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void halt()
{
    exit(EXIT_SUCCESS);
}

/*
 * Finds the opcode and references the correct instruction function
 */
void decodeBinary(uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
        pushb();
        break;
    case 0x01:
        pushs();
        break;
    case 0x02:
        pushi();
        break;
    case 0x03:
        pushl();
        break;
    case 0x04:
        pushf();
        break;
    case 0x05:
        pushd();
        break;
    case 0x06:
        pushbm();
        break;
    case 0x07:
        pushsm();
        break;
    case 0x08:
        pushim();
        break;
    case 0x09:
        pushlm();
        break;
    case 0x0a:
        pushfm();
        break;
    case 0x0b:
        pushdm();
        break;
    case 0x0c:
        pushmm();
        break;
    case 0x0d:
        dupb();
        break;
    case 0x0e:
        dups();
        break;
    case 0x0f:
        dupi();
        break;
    case 0x10:
        dupl();
        break;
    case 0x11:
        dupf();
        break;
    case 0x12:
        dupd();
        break;
    case 0x13:
        popb();
        break;
    case 0x14:
        pops();
        break;
    case 0x15:
        popi();
        break;
    case 0x16:
        popl();
        break;
    case 0x17:
        popf();
        break;
    case 0x18:
        popd();
        break;
    case 0x19:
        popbm();
        break;
    case 0x1a:
        popsm();
        break;
    case 0x1b:
        popim();
        break;
    case 0x1c:
        poplm();
        break;
    case 0x1d:
        popfm();
        break;
    case 0x1e:
        popdm();
        break;
    case 0x1f:
        popmm();
        break;
    case 0x20:
        swapb();
        break;
    case 0x21:
        swaps();
        break;
    case 0x22:
        swapi();
        break;
    case 0x23:
        swapl();
        break;
    case 0x24:
        swapf();
        break;
    case 0x25:
        swapd();
        break;
    case 0x26:
        convbs();
        break;
    case 0x27:
        convbi();
        break;
    case 0x28:
        convbl();
        break;
    case 0x29:
        convbf();
        break;
    case 0x2a:
        convbd();
        break;
    case 0x2b:
        convsb();
        break;
    case 0x2c:
        convsi();
        break;
    case 0x2d:
        convsl();
        break;
    case 0x2e:
        convsf();
        break;
    case 0x2f:
        convsd();
        break;
    case 0x30:
        convib();
        break;
    case 0x31:
        convis();
        break;
    case 0x32:
        convil();
        break;
    case 0x33:
        convif();
        break;
    case 0x34:
        convid();
        break;
    case 0x35:
        convlb();
        break;
    case 0x36:
        convls();
        break;
    case 0x37:
        convli();
        break;
    case 0x39:
        convlf();
        break;
    case 0x3a:
        convld();
        break;
    case 0x3b:
        convfb();
        break;
    case 0x3c:
        convfs();
        break;
    case 0x3d:
        convfi();
        break;
    case 0x3e:
        convfl();
        break;
    case 0x3f:
        convfd();
        break;
    case 0x40:
        convdb();
        break;
    case 0x41:
        convds();
        break;
    case 0x42:
        convdi();
        break;
    case 0x43:
        convdl();
        break;
    case 0x44:
        convdf();
        break;
    case 0x45:
        inch();
        break;
    case 0x46:
        inb();
        break;
    case 0x47:
        ins();
        break;
    case 0x48:
        ini();
        break;
    case 0x49:
        inl();
        break;
    case 0x4a:
        inf();
        break;
    case 0x4b:
        ind();
        break;
    case 0x4c:
        outch();
        break;
    case 0x4d:
        outb();
        break;
    case 0x4e:
        outs();
        break;
    case 0x4f:
        outi();
        break;
    case 0x50:
        outl();
        break;
    case 0x51:
        outf();
        break;
    case 0x52:
        outd();
        break;
    case 0x53:
        addb();
        break;
    case 0x54:
        adds();
        break;
    case 0x55:
        addi();
        break;
    case 0x56:
        addl();
        break;
    case 0x57:
        addf();
        break;
    case 0x58:
        addd();
        break;
    case 0x59:
        subb();
        break;
    case 0x5a:
        subs();
        break;
    case 0x5b:
        subi();
        break;
    case 0x5c:
        subl();
        break;
    case 0x5d:
        subf();
        break;
    case 0x5e:
        subd();
        break;
    case 0x5f:
        mulb();
        break;
    case 0x60:
        muls();
        break;
    case 0x61:
        muli();
        break;
    case 0x62:
        mull();
        break;
    case 0x63:
        mulf();
        break;
    case 0x64:
        muld();
        break;
    case 0x65:
        divb();
        break;
    case 0x66:
        divs();
        break;
    case 0x67:
        divi();
        break;
    case 0x68:
        divl();
        break;
    case 0x69:
        divf();
        break;
    case 0x6a:
        divd();
        break;
    case 0x6b:
        and8();
        break;
    case 0x6c:
        and16();
        break;
    case 0x6d:
        and32();
        break;
    case 0x6e:
        and64();
        break;
    case 0x6f:
        or8();
        break;
    case 0x70:
        or16();
        break;
    case 0x71:
        or32();
        break;
    case 0x72:
        or64();
        break;
    case 0x73:
        xor8();
        break;
    case 0x74:
        xor16();
        break;
    case 0x75:
        xor32();
        break;
    case 0x76:
        xor64();
        break;
    case 0x77:
        not8();
        break;
    case 0x78:
        not16();
        break;
    case 0x79:
        not32();
        break;
    case 0x7a:
        not64();
        break;
    case 0x7b:
        shftrb();
        break;
    case 0x7c:
        shftrs();
        break;
    case 0x7d:
        shftri();
        break;
    case 0x7e:
        shftrl();
        break;
    case 0x7f:
        shftlb();
        break;
    case 0x80:
        shftls();
        break;
    case 0x81:
        shftli();
        break;
    case 0x82:
        shftll();
        break;
    case 0x83:
        jmp();
        break;
    case 0x84:
        jrpc();
        break;
    case 0x85:                      // check from here
        jind();
        break;
    case 0x86:
        jz();
        break;
    case 0x87:
        jnz();
        break;
    case 0x88:
        jgt();
        break;
    case 0x89:
        jlt();
        break;
    case 0x8a:
        jge();
        break;
    case 0x8b:
        jle();
        break;
    case 0x8c:
        call();
        break;
    case 0x8d:
        returnCall();
        break;                                      // to here
    case 0x8e:
        halt();
        break;
    default:
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * Do an execute instructions function
 * switch per opcode and calls above functions
 */
void readAndExecute()
{
    uint8_t instructionCheck = readMemory(PC, 1);

    decodeBinary(instructionCheck);
}

/*To implement*/
// to8(), to16(), to32(), to64(), tofloat(), to double()

int main(int argc, char *argv[])
{

    /*
     * Step 1: Scan the file
     */
    FILE *fp;

    if ((argc != 2) || (argv[1] == NULL) || (!strstr(argv[1], ".slko")))
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "rb");

    // Initialize arrays
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }

    if (fp == NULL)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        exit(EXIT_FAILURE);
    }

    // size_t readFile = fread(memory, sizeof(uint8_t), MEMORY_SIZE, fp);

    uint32_t codeOffset;

    while (!ferror(fp) && fread(&codeOffset, sizeof(uint32_t), 1, fp) != 1)
        ;

    uint32_t dataOffset;

    while (!ferror(fp) && fread(&dataOffset, sizeof(uint32_t), 1, fp) != 1)
        ;

    // Big endian convert back
    uint32_t codeOffsetFinal = (codeOffset >> 24 & 0xFF) | (codeOffset >> 16 & 0xFF) | (codeOffset >> 8 & 0xFF) | (codeOffset & 0xFF);
    uint32_t dataOffsetFinal = (dataOffset >> 24 & 0xFF) | (dataOffset >> 16 & 0xFF) | (dataOffset >> 8 & 0xFF) | (dataOffset & 0xFF);
    uint32_t codeSize = dataOffsetFinal - codeOffsetFinal;

    char *dst = memory;
    size_t n;
    while (n = fread(dst, sizeof(uint8_t), codeSize, fp))
    {
        dst += n;
        codeSize -= n;
    }

    // rests to data section of heap pointer
    dst = memory + 0x10000;

    while (n = fread((dst), sizeof(uint8_t), 1, fp))
    {
        dst += n;
        codeSize -= n;
    }

    // check ferror
    if (ferror(fp) != 0)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        readAndExecute();
    }

    // Close the file.
    fclose(fp);

    return 0;
}