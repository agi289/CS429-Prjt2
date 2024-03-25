#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include "assembler.h"

void instructionsProcessors(char *s, FILE *ptr, char *outputName, int lineCounterInstruc, Symbols table[], int sizeForTable, int max)
{
    /*Check there is no ;*/
    if (strstr(s, ";") != NULL)
    {
        fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    /*Syntax error check, starts with tab*/
    if (s[0] != '\t')
    {
        fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    /*
     * Remove tab
     */
    int i = 0;
    char line[256];
    while (s[i] == '\t')
    {
        i++;
    }
    strcpy(line, s + i);

    /*Syntax error check of space or semicolon*/
    if (!line[0])
    {
        fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
        remove(outputName);
        exit(EXIT_FAILURE);
    }
    if (line[0] == '\t' || line[0] == ' ' || line[0] == ';' || line[0] == ':')
    {
        fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    /*check that first character in instruction is letter*/
    if (!isalpha(line[0]))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    // printf("%s\n", line);

    /*No arguments use strcmp*/
    if (strcmp(line, "dupb") == 0 || strcmp(line, "dups") == 0 || strcmp(line, "dupi") == 0 ||
        strcmp(line, "dupl") == 0 || strcmp(line, "dupf") == 0 || strcmp(line, "dupd") == 0 ||
        strcmp(line, "popb") == 0 || strcmp(line, "pops") == 0 || strcmp(line, "popi") == 0 ||
        strcmp(line, "popl") == 0 || strcmp(line, "popf") == 0 || strcmp(line, "popd") == 0 ||
        strcmp(line, "swapb") == 0 || strcmp(line, "swaps") == 0 || strcmp(line, "swapi") == 0 ||
        strcmp(line, "swapl") == 0 || strcmp(line, "swapf") == 0 || strcmp(line, "swapd") == 0 ||
        strcmp(line, "convbs") == 0 || strcmp(line, "convbi") == 0 || strcmp(line, "convbl") == 0 ||
        strcmp(line, "convbf") == 0 || strcmp(line, "convbd") == 0 || strcmp(line, "convsb") == 0 ||
        strcmp(line, "convsi") == 0 || strcmp(line, "convsl") == 0 || strcmp(line, "convsf") == 0 ||
        strcmp(line, "convsd") == 0 || strcmp(line, "convib") == 0 || strcmp(line, "convis") == 0 ||
        strcmp(line, "convil") == 0 || strcmp(line, "convif") == 0 || strcmp(line, "convid") == 0 ||
        strcmp(line, "convlb") == 0 || strcmp(line, "convls") == 0 || strcmp(line, "convli") == 0 ||
        strcmp(line, "convlf") == 0 || strcmp(line, "convld") == 0 || strcmp(line, "convfb") == 0 ||
        strcmp(line, "convfs") == 0 || strcmp(line, "convfi") == 0 || strcmp(line, "convfl") == 0 ||
        strcmp(line, "convfd") == 0 || strcmp(line, "convdb") == 0 || strcmp(line, "convds") == 0 || strcmp(line, "convdi") == 0 ||
        strcmp(line, "convdl") == 0 || strcmp(line, "convdf") == 0 || strcmp(line, "inch") == 0 ||
        strcmp(line, "inb") == 0 || strcmp(line, "ins") == 0 || strcmp(line, "ini") == 0 ||
        strcmp(line, "inl") == 0 || strcmp(line, "inf") == 0 || strcmp(line, "ind") == 0 ||
        strcmp(line, "outch") == 0 || strcmp(line, "outb") == 0 || strcmp(line, "outs") == 0 || strcmp(line, "outi") == 0 ||
        strcmp(line, "outl") == 0 || strcmp(line, "outf") == 0 || strcmp(line, "outd") == 0 ||
        strcmp(line, "addb") == 0 || strcmp(line, "adds") == 0 || strcmp(line, "addi") == 0 || strcmp(line, "addl") == 0 || strcmp(line, "addf") == 0 ||
        strcmp(line, "addd") == 0 || strcmp(line, "subb") == 0 || strcmp(line, "subs") == 0 || strcmp(line, "subi") == 0 || strcmp(line, "subl") == 0 ||
        strcmp(line, "subf") == 0 || strcmp(line, "subd") == 0 || strcmp(line, "mulb") == 0 ||
        strcmp(line, "muls") == 0 || strcmp(line, "muli") == 0 || strcmp(line, "mull") == 0 ||
        strcmp(line, "mulf") == 0 || strcmp(line, "muld") == 0 || strcmp(line, "divb") == 0 ||
        strcmp(line, "divs") == 0 || strcmp(line, "divi") == 0 || strcmp(line, "divl") == 0 ||
        strcmp(line, "divf") == 0 || strcmp(line, "divd") == 0 || strcmp(line, "and8") == 0 ||
        strcmp(line, "and16") == 0 || strcmp(line, "and32") == 0 || strcmp(line, "and64") == 0 ||
        strcmp(line, "or8") == 0 || strcmp(line, "or16") == 0 || strcmp(line, "or32") == 0 || strcmp(line, "or64") == 0 ||
        strcmp(line, "xor8") == 0 || strcmp(line, "xor16") == 0 || strcmp(line, "xor32") == 0 ||
        strcmp(line, "xor64") == 0 || strcmp(line, "not8") == 0 || strcmp(line, "not16") == 0 ||
        strcmp(line, "not32") == 0 || strcmp(line, "not64") == 0 || strcmp(line, "jind") == 0 || strcmp(line, "return") == 0 || strcmp(line, "halt") == 0)
    {
        // Get opcode string and value
        enum instr_opcode inputFirst = checkCommand(line, outputName, lineCounterInstruc);

        writeBinaryIntUnsigned(ptr, inputFirst, 1);
    }
    else
    {
        // Stores original line for later on space checks
        char original[strlen(line) + 1];
        strcpy(original, line);

        /* Checks line has at least 1 space*/
        spaceCheckLess(line, 1, lineCounterInstruc, outputName);
        char *mnemonic = strtok(line, " ");
        isCharactersCheck(mnemonic, lineCounterInstruc, outputName);

        if (strcmp(mnemonic, "pushb") == 0 || strcmp(mnemonic, "pushs") == 0 || strcmp(mnemonic, "pushi") == 0 ||
            strcmp(mnemonic, "pushl") == 0 || strcmp(mnemonic, "pushf") == 0 || strcmp(mnemonic, "pushd") == 0 ||
            strcmp(mnemonic, "shftrb") == 0 || strcmp(mnemonic, "shftrs") == 0 || strcmp(mnemonic, "shftri") == 0 ||
            strcmp(mnemonic, "shftrl") == 0 || strcmp(mnemonic, "shftlb") == 0 || strcmp(mnemonic, "shftls") == 0 ||
            strcmp(mnemonic, "shftli") == 0 || strcmp(mnemonic, "shftll") == 0)
        {

            spaceCheck(original, 1, lineCounterInstruc, outputName);
            char *rest = strtok(NULL, "\0");
            spaceCheck(rest, 0, lineCounterInstruc, outputName);

            if (strcmp(mnemonic, "pushb") == 0 || strcmp(mnemonic, "shftrb") == 0 || strcmp(mnemonic, "shftlb") == 0)
            {
                // int8 & opcode
                if (strcmp(mnemonic, "pushb") == 0)
                {
                    int8_t int8Binary = strtolToInt8(rest, lineCounterInstruc, outputName);
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    // write opcode & operands 8 bits a time
                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, int8Binary, 1);
                }
                else if (strcmp(mnemonic, "shftrb") == 0 || strcmp(mnemonic, "shftlb") == 0)
                {
                    int8_t int8Binary = strtolToInt8(rest, lineCounterInstruc, outputName);
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    // write opcode & operands 8 bits a time
                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, int8Binary, 1);
                }
            }
            else if (strcmp(mnemonic, "pushs") == 0 || strcmp(mnemonic, "shftrs") == 0 || strcmp(mnemonic, "shftls") == 0)
            {
                // short
                if (strcmp(mnemonic, "pushs") == 0)
                {
                    int16_t shortBinary = strtolToShort(rest, lineCounterInstruc, outputName);

                    // Get opcode string and value
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, shortBinary, 2);
                }
                else if (strcmp(mnemonic, "shftrs") == 0 || strcmp(mnemonic, "shftls") == 0)
                {
                    int8_t shortBinary = strtolToInt8(rest, lineCounterInstruc, outputName);
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    // write opcode & operands 8 bits a time
                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, shortBinary, 1);
                }
            }
            else if (strcmp(mnemonic, "pushi") == 0 || strcmp(mnemonic, "shftri") == 0 || strcmp(mnemonic, "shftli") == 0)
            {
                // int
                if (strcmp(mnemonic, "pushi") == 0)
                {
                    int32_t intBinary = strtolToInt(rest, lineCounterInstruc, outputName);

                    // Get opcode string and value
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, intBinary, 4);
                }
                else if (strcmp(mnemonic, "shftri") == 0 || strcmp(mnemonic, "shftli") == 0)
                {
                    int8_t intBinary = strtolToInt8(rest, lineCounterInstruc, outputName);
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    // write opcode & operands 8 bits a time
                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, intBinary, 1);
                }
            }
            else if (strcmp(mnemonic, "pushl") == 0 || strcmp(mnemonic, "shftrl") == 0 || strcmp(mnemonic, "shftll") == 0)
            {
                // long long
                if (strcmp(mnemonic, "pushl") == 0)
                {
                    int64_t LLBinary = strtolToLongLong(rest, lineCounterInstruc, outputName);

                    // Get opcode string and value
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, LLBinary, 8);
                }
                else if (strcmp(mnemonic, "shftrl") == 0 || strcmp(mnemonic, "shftll") == 0)
                {
                    int8_t LLBinary = strtolToInt8(rest, lineCounterInstruc, outputName);
                    enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                    // write opcode & operands 8 bits a time
                    writeBinaryIntUnsigned(ptr, input, 1);
                    writeBinaryIntSign(ptr, LLBinary, 1);
                }
            }
            else if (strcmp(mnemonic, "pushf") == 0)
            {
                // float & opcocde
                float floatBinary = strtolToFloat(rest, lineCounterInstruc, outputName);
                enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                writeBinaryIntUnsigned(ptr, input, 1);

                writeBinaryFloatSign(ptr, floatBinary, 4);
            }
            else if (strcmp(mnemonic, "pushd") == 0)
            {
                // double & opcode
                double doubleBinary = strtolToDouble(rest, lineCounterInstruc, outputName);
                enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

                writeBinaryIntUnsigned(ptr, input, 1);

                writeBinaryDoubleSign(ptr, doubleBinary, 8);
            }
            else
            {
                fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                remove(outputName);
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(mnemonic, "pushbm") == 0 || strcmp(mnemonic, "pushsm") == 0 || strcmp(mnemonic, "pushim") == 0 ||
                 strcmp(mnemonic, "pushlm") == 0 || strcmp(mnemonic, "pushfm") == 0 || strcmp(mnemonic, "pushdm") == 0 ||
                 strcmp(mnemonic, "popbm") == 0 || strcmp(mnemonic, "popsm") == 0 || strcmp(mnemonic, "popim") == 0 ||
                 strcmp(mnemonic, "poplm") == 0 || strcmp(mnemonic, "popfm") == 0 || strcmp(mnemonic, "popdm") == 0 ||
                 strcmp(mnemonic, "jmp") == 0 || strcmp(mnemonic, "jz") == 0 || strcmp(mnemonic, "jnz") == 0 ||
                 strcmp(mnemonic, "jgt") == 0 || strcmp(mnemonic, "jlt") == 0 || strcmp(mnemonic, "jge") == 0 ||
                 strcmp(mnemonic, "jle") == 0 || strcmp(mnemonic, "call") == 0)
        {
            spaceCheck(original, 1, lineCounterInstruc, outputName);
            char *rest = strtok(NULL, "\0");
            spaceCheck(rest, 0, lineCounterInstruc, outputName);

            // Get opcode string and value
            enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);
            writeBinaryIntUnsigned(ptr, input, 1);

            instructionsLabel(rest, ptr, outputName, lineCounterInstruc, table, sizeForTable, max);
        }
        else if (strcmp(mnemonic, "jrpc") == 0)
        {
            spaceCheck(original, 1, lineCounterInstruc, outputName);
            char *rest = strtok(NULL, "\0");
            spaceCheck(rest, 0, lineCounterInstruc, outputName);

            // int8
            int8_t int8BinaryJRPC = strtolToInt8(rest, lineCounterInstruc, outputName);

            // Get opcode string and value
            enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);

            writeBinaryIntUnsigned(ptr, input, 1);
            writeBinaryIntSign(ptr, int8BinaryJRPC, 1);
        }
        else if (strcmp(mnemonic, "pushmm") == 0 || strcmp(mnemonic, "popmm") == 0) // 2 spaces
        {
            // Get opcode string and value
            enum instr_opcode input = checkCommand(mnemonic, outputName, lineCounterInstruc);
            writeBinaryIntUnsigned(ptr, input, 1);

            spaceCheck(original, 2, lineCounterInstruc, outputName);
            char *label = strtok(NULL, " ");
            spaceCheck(label, 0, lineCounterInstruc, outputName);
            char *items = strtok(NULL, "\0");
            spaceCheck(items, 0, lineCounterInstruc, outputName);

            int8_t itemsBinary = strtolToInt8(items, lineCounterInstruc, outputName);
            instructionsLabel(label, ptr, outputName, lineCounterInstruc, table, sizeForTable, max);

            writeBinaryIntSign(ptr, itemsBinary, 1);
        }
        else
        {
            fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
            remove(outputName);
            exit(EXIT_FAILURE);
        }
    }
}

void spaceCheck(char *s, int spaces, int lineSpaces, char *outputSpaces)
{
    int spaceCount = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            spaceCount++;
        }
    }

    if (spaceCount != spaces)
    {
        fprintf(stderr, "Error on line %d\n", lineSpaces);
        remove(outputSpaces);
        exit(EXIT_FAILURE);
    }
}

void spaceCheckLess(char *s, int spaces, int lineSpaces, char *outputSpaces)
{
    int spaceCount = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            spaceCount++;
        }
    }

    if (spaceCount < spaces)
    {
        fprintf(stderr, "Error on line %d\n", lineSpaces);
        remove(outputSpaces);
        exit(EXIT_FAILURE);
    }
}

void instructionsLabel(char *rest, FILE *ptr, char *outputName, int lineCounterInstruc, Symbols table[], int sizeForTable, int max)
{
    // 24 bits

    uint32_t LDLiteral = 0;
    if (rest[0] == ':')
    {
        // checks if contains label and operations or just label
        int operationsCountPlus = 0;
        int operationsCountNeg = 0;
        for (int i = 0; i < strlen(rest); i++)
        {
            if (rest[i] == '+')
            {
                operationsCountPlus++;
            }
            if (rest[i] == '-')
            {
                operationsCountNeg++;
            }
        }

        // Label w operations
        if (operationsCountPlus > 0 || operationsCountNeg > 0)
        {
            char copy[strlen(rest) + 1];
            strcpy(copy, rest);

            if (operationsCountPlus == 1)
            {
                char *label = strtok(copy, "+");
                char *operation = strtok(NULL, "\0");

                if (!operation)
                {
                    fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                    remove(outputName);
                    exit(EXIT_FAILURE);
                }

                char LabelFinal[strlen(label)];
                strcpy(LabelFinal, label + 1);

                int errorFlag = 0;
                for (int i = 0; i < sizeForTable; i++)
                {
                    if (strcmp(table[i].label, LabelFinal) == 0)
                    {
                        LDLiteral = table[i].address;
                        errorFlag = 1;
                        break;
                    }
                }

                if (errorFlag == 0)
                {
                    fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                    remove(outputName);
                    exit(EXIT_FAILURE);
                }

                // operation
                u_int32_t operate = strtoulToInt(operation, lineCounterInstruc, outputName);

                // if ((LDLiteral + operate >= max) || (LDLiteral + operate < 0) || (operate >= max || operate < 0))
                // {
                //     printf("Hh\n");
                //     fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                //     remove(outputName);
                //     exit(EXIT_FAILURE);
                // }

                uint32_t addressOperationAdd = LDLiteral + operate;

                writeBinaryIntUnsigned(ptr, addressOperationAdd, 3);
            }
            else if (operationsCountNeg == 1)
            {
                char *label = strtok(copy, "-");
                char *operation = strtok(NULL, "\0");

                 if (!operation)
                {
                    fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                    remove(outputName);
                    exit(EXIT_FAILURE);
                }

                char LabelFinal[strlen(label)];
                strcpy(LabelFinal, label + 1);

                int errorFlag = 0;

                for (int i = 0; i < sizeForTable; i++)
                {
                    if (strcmp(table[i].label, LabelFinal) == 0)
                    {
                        LDLiteral = table[i].address;
                        errorFlag = 1;
                        break;
                    }
                }

                if (errorFlag == 0)
                {
                    fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                    remove(outputName);
                    exit(EXIT_FAILURE);
                }

                // operation
                int operate = strtoulToInt(operation, lineCounterInstruc, outputName);

                if ((LDLiteral - operate < 0))
                {
                    fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                    remove(outputName);
                    exit(EXIT_FAILURE);
                }

                int addressOperationSub = LDLiteral - operate;

                writeBinaryIntUnsigned(ptr, addressOperationSub, 3);
            }
            else
            {
                fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                remove(outputName);
                exit(EXIT_FAILURE);
            }
        }
        // Just label
        else
        {
            char Literal[strlen(rest)];
            strcpy(Literal, rest + 1);
            /*Look through symbol array*/
            int errorFlag = 0;
            for (int i = 0; i < sizeForTable; i++)
            {
                if (strcmp(table[i].label, Literal) == 0)
                {
                    LDLiteral = table[i].address;
                    errorFlag = 1;
                    break;
                }
            }

            if (errorFlag == 0)
            {
                fprintf(stderr, "Error on line %d\n", lineCounterInstruc);
                remove(outputName);
                exit(EXIT_FAILURE);
            }
            writeBinaryIntUnsigned(ptr, LDLiteral, 3);
        }
    }
    else
    {

        // 24 bit int
        unsigned int memoryAddressValueHere;
        memoryAddressValueHere = strtolTo24(rest, lineCounterInstruc, outputName);

        writeBinaryIntUnsigned(ptr, memoryAddressValueHere, 3);
    }
}