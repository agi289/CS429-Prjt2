#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "assembler.h"

/* Constants:Assuming the max number to be 100 */
#define maxNumSymbols 1000

/* Externs */
extern int sizeCheck(enum instr_opcode op);
extern enum instr_opcode checkCommand(char *instruction, char *endFile, int lineCounterCheck);

/*
 * Global variables
 */
Symbols tableofSymbols[maxNumSymbols]; // Array of symbol entries
int sizeOfTable = 0;                   // Size of table as it grows (being filled in)
int codeFlag = 0;                      // 1 for code 2 for data
int flag = 0;                          // flags for data type
int lineCounter2 = 0;                  /*Error line counter*/
int maxSizeOFFile = 0;

/*
 * Function to process labels
 */
void labelProcessor(char s[], FILE *output, unsigned int addressIntake, char *outputName)
{
    // Substring from index 1
    char check[strlen(s)];
    strcpy(check, s + 1);

    /* Error of label coming twice*/
    if (sizeOfTable != 0)
    {
        for (int i = 0; i < sizeOfTable; i++)
        {
            if (strcmp(tableofSymbols[i].label, check) == 0)
            {
                fprintf(stderr, "Error on line %d\n", lineCounter2);
                remove(outputName);
                exit(EXIT_FAILURE);
            }
        }
    }

    int onecharac = 0;
    /* check characters in the label*/
    for (int j = 0; j < strlen(check); j++)
    {
        if ((isalpha(check[j]) || isdigit(check[j]) || check[j] == '_'))
        {
            if (isalpha(check[j]))
            {
                onecharac++;
            }
        }
        else
        {
            fprintf(stderr, "Error on line %d\n", lineCounter2);
            remove(outputName);
            exit(EXIT_FAILURE);
        }
    }

    if (onecharac < 1)
    {
        fprintf(stderr, "Error on line %d\n", lineCounter2);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    Symbols entry;
    strcpy(entry.label, check);
    entry.address = addressIntake;
    tableofSymbols[sizeOfTable] = entry;
    sizeOfTable++;

    // printf("Label: %s\n", check);
    // printf("Address %d\n", addressIntake);
    // printf("Sucess table!\n");
}

int main(int argc, char *argv[])
{
    /*
     * Step 1: Scan the file
     */
    // Scan with .slk extension
    FILE *fptr;

    if ((argv[1] == NULL) || (!strstr(argv[1], ".slk")))
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        exit(EXIT_FAILURE);
    }

    // Open a file in read mode
    fptr = fopen(argv[1], "r");

    // Open the binary file for writing mode
    FILE *binaryOutput;

    // make file name "sample".sko
    char *inputName = argv[1];
    // char *name = strtok(inputName, ".");
    // char *slkoEnd = ".slko";
    char *fileNameOutput = strcat(inputName, "o");
    // printf("%s\n", fileNameOutput);

    binaryOutput = fopen(fileNameOutput, "wb");

    if (fptr == NULL)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        remove(fileNameOutput);
        exit(EXIT_FAILURE);
    }

    char buffer[256];

    int lines;
    int codeCheck = 0;

    /*First loop to count number of lines & check at least 1 .code*/
    while (fgets(buffer, 256, fptr))
    {
        lines++;

        // Step 1: Replace new line character with null terminator
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        if (strcmp(buffer, ".code") == 0)
        {
            codeCheck++;
        }
    }

    if (codeCheck < 1)
    {
        fprintf(stderr, "Error on line 0\n");
        remove(fileNameOutput);
        exit(EXIT_FAILURE);
    }

    /* Start over file by moving pointer to end*/
    fseek(fptr, 0, SEEK_SET);

    /*Initialize address array for label*/
    uint32_t addresses[lines];
    int index = 1;      // index in array
    uint32_t value = 0; // incrementing value overtime
    uint32_t heapValue = 0x10000;

    /*Loop through to make the bytes*/
    while (fgets(buffer, 256, fptr))
    {
        lineCounter2++;
        // Step 1: Replace new line character with null terminator
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Step 2: empty lines and ; (meaning comments)
        if (buffer[0] == '\0' || buffer[0] == ';')
        {
            addresses[index] = value;
            value += 0;
            index++;
        }
        // Step 3: Process instructions after the : character
        else if (buffer[0] == ':')
        {
            if (codeFlag == 1)
            {
                addresses[index] = value;
                value += 0;
                index++;
            }
            else if (codeFlag == 2)
            {
                addresses[index] = heapValue;
                heapValue += 0;
                index++;
            }
        }
        // Step 4: .code use instructions processor function
        else if (strcmp(buffer, ".code") == 0) // Since string has to use strcmp
        {
            // Indicates gonna have instructions (assembly) after and do related querries
            codeFlag = 1;
            addresses[index] = value;
            value += 0;
            index++;
        }
        // Step 5: .data need to use data processor function
        else if (strcmp(buffer, ".data") == 0)
        {
            // Indicates gonna have : after and need to do data related querries
            codeFlag = 2;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else if (strcmp(buffer, ".byte") == 0)
        {
            flag = 2;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;

        }
        else if (strcmp(buffer, ".ascii") == 0)
        {
            flag = 3;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else if (strcmp(buffer, ".short") == 0)
        {
            flag = 4;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else if (strcmp(buffer, ".int") == 0)
        {
            flag = 5;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else if (strcmp(buffer, ".long") == 0)
        {
            flag = 6;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else if (strcmp(buffer, ".float") == 0)
        {
            flag = 7;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else if (strcmp(buffer, ".double") == 0)
        {
            flag = 8;
            addresses[index] = heapValue;
            heapValue += 0;
            index++;
        }
        else
        {
            if (codeFlag == 1) // instructions are 4 bytes each
            {
                /*Error check that tab is there*/
                if (buffer[0] != '\t')
                {
                    fprintf(stderr, "Error on line %d\n", lineCounter2);
                    remove(fileNameOutput);
                    exit(EXIT_FAILURE);
                }

                /*Removes tab*/
                char temp[strlen(buffer)];
                strcpy(temp, buffer + 1);

                /*Gets mneumonic and corresponding opcode*/
                char *mneumonic = strtok(temp, " ");
                enum instr_opcode opcodeCheck = checkCommand(mneumonic, fileNameOutput, lineCounter2);
                int amount = sizeCheck(opcodeCheck);

                addresses[index] = value;
                value += amount;
                index++;
            }
            else if (codeFlag == 2)
            {
                if (flag == 2) //.byte
                {
                    addresses[index] = heapValue;
                    heapValue += 1;
                    index++;
                }
                else if (flag == 3) //.ascii
                {
                    addresses[index] = heapValue;
                    heapValue += 1;
                    index++;
                }
                else if (flag == 4) //.short
                {
                    addresses[index] = heapValue;
                    heapValue += 2;
                    index++;
                }
                else if (flag == 5) //.int
                {
                    addresses[index] = heapValue;
                    heapValue += 4;
                    index++;
                }
                else if (flag == 6) //.long
                {
                    addresses[index] = heapValue;
                    heapValue += 8;
                    index++;
                }
                else if (flag == 7) //.float
                {
                    addresses[index] = heapValue;
                    heapValue += 4;
                    index++;
                }
                else if (flag == 8) //.double
                {
                    // printf("Before: %d\n", heapValue);
                    // printf("Before: %d\n", heapValue);
                    addresses[index] = heapValue;
                    heapValue += 8;
                    // printf("Value in array: %d\n", addresses[index]);
                    // printf("Index is  %d\n", index);
                    index++;
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", (index));
                    remove(fileNameOutput);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fprintf(stderr, "Error on line %d\n", (index));
                remove(fileNameOutput);
                exit(EXIT_FAILURE);
            }
        }
        // printf("Line Byte at this time: %d\n", value);
        // printf("Line line: %d\n", lineCounter2);
        // printf("Line: %d, value: %d\n", lineCounter2, value);
    }

    // Access max value of File for bound check
    // printf("Check....Line Counter Now: %d\n", lineCounter2);

    /* Start over file by moving pointer to end*/
    lineCounter2 = 0;
    fseek(fptr, 0, SEEK_SET);
    int lineCounter = 0;
    int dataCodeLabelCheck = 0;

    /* Stores the label addresses*/
    while (fgets(buffer, 256, fptr))
    {
        lineCounter2++;
        // Step 1: Replace new line character with null terminator
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (strcmp(buffer, ".code") == 0 || strcmp(buffer, ".data") == 0)
        {
            dataCodeLabelCheck = 1;
        }
        if (buffer[0] == ':')
        {
            if (dataCodeLabelCheck == 1)
            {
                // printf("LineCounter : %d\n", lineCounter2);
                // printf("Problem: %d\n", lineCounter);
                uint32_t addressValue = addresses[lineCounter2];
                // printf("Check: %d\n", addressValue);
                labelProcessor(buffer, binaryOutput, addressValue, fileNameOutput);
            }
            else
            {
                fprintf(stderr, "Error on line %d\n", lineCounter2);
                remove(fileNameOutput);
                exit(EXIT_FAILURE);
            }
        }
        lineCounter++;
    }

    /* Start over file by moving pointer to end*/
    fseek(fptr, 0, SEEK_SET);
    // out file
    fseek(binaryOutput, 8, SEEK_SET);
    lineCounter2 = 0;

    while (fgets(buffer, 256, fptr))
    {
        lineCounter2++;
        // Step 1: Replace new line character with null terminator
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Step 2: Remove empty lines and ; (meaning comments)
        if (buffer[0] == '\0' || buffer[0] == ';')
        {
            continue;
        }
        // Step 3: Process instructions after the : character
        else if (buffer[0] == ':')
        {
            continue;
        }
        // Step 4: .code use instructions processor function
        else if (strcmp(buffer, ".code") == 0) // Since string has to use strcmp
        {
            codeFlag = 1;
        }
        // Step 5: .data need to use data processor function
        else if (strcmp(buffer, ".data") == 0)
        {
            codeFlag = 2;
        }
        else if (strcmp(buffer, ".byte") == 0)
        {
            flag = 2;
        }
        else if (strcmp(buffer, ".ascii") == 0)
        {
            flag = 3;
        }
        else if (strcmp(buffer, ".short") == 0)
        {
            flag = 4;
        }
        else if (strcmp(buffer, ".int") == 0)
        {
            flag = 5;
        }
        else if (strcmp(buffer, ".long") == 0)
        {
            flag = 6;
        }
        else if (strcmp(buffer, ".float") == 0)
        {
            flag = 7;
        }
        else if (strcmp(buffer, ".double") == 0)
        {
            flag = 8;
        }
        else
        {
            if (codeFlag == 1)
            {
                instructionsProcessors(buffer, binaryOutput, fileNameOutput, lineCounter2, tableofSymbols, sizeOfTable, maxSizeOFFile);
            }
            else if (codeFlag == 2)
            {
                continue;
            }
            else
            {
                fprintf(stderr, "Error on line %d\n", lineCounter2);
                remove(fileNameOutput);
                exit(EXIT_FAILURE);
            }
        }
    }

    /* Add code offsers*/
    long codeEnd = ftell(binaryOutput) << 24;
    fseek(binaryOutput, 0, SEEK_SET);
    int codeoffSet = 0x8 << 24;
    fwrite(&codeoffSet, sizeof(codeoffSet), 1, binaryOutput);
    fwrite(&codeEnd, sizeof(codeoffSet), 1, binaryOutput);

    /* Start over file by moving pointer to end*/
    fseek(fptr, 0, SEEK_SET);
    fseek(binaryOutput, 0, SEEK_END);
    lineCounter2 = 0;

    /* Data process*/
    while (fgets(buffer, 256, fptr))
    {
        lineCounter2++;
        // Step 1: Replace new line character with null terminator
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Step 2: Remove empty lines and ; (meaning comments)
        if (buffer[0] == '\0' || buffer[0] == ';')
        {
            continue;
        }
        // Step 3: Process instructions after the : character
        else if (buffer[0] == ':')
        {
            continue;
        }
        // Step 4: .code use instructions processor function
        else if (strcmp(buffer, ".code") == 0) // Since string has to use strcmp
        {
            codeFlag = 1;
        }
        // Step 5: .data need to use data processor function
        else if (strcmp(buffer, ".data") == 0)
        {
            codeFlag = 2;
        }
        else if (strcmp(buffer, ".byte") == 0)
        {
            flag = 2;
        }
        else if (strcmp(buffer, ".ascii") == 0)
        {
            flag = 3;
        }
        else if (strcmp(buffer, ".short") == 0)
        {
            flag = 4;
        }
        else if (strcmp(buffer, ".int") == 0)
        {
            flag = 5;
        }
        else if (strcmp(buffer, ".long") == 0)
        {
            flag = 6;
        }
        else if (strcmp(buffer, ".float") == 0)
        {
            flag = 7;
        }
        else if (strcmp(buffer, ".double") == 0)
        {
            flag = 8;
        }
        else
        {
            if (codeFlag == 1)
            {
                continue;
            }
            else if (codeFlag == 2)
            {
                dataProcessor(buffer, binaryOutput, fileNameOutput, lineCounter2, flag);
            }
            else
            {
                fprintf(stderr, "Error on line %d\n", lineCounter2);
                remove(fileNameOutput);
                exit(EXIT_FAILURE);
            }
        }
    }

    // if (binaryOutput == NULL)
    // {
    //     fprintf(stderr, "Invalid slinker filepath\n");
    //     remove(fileNameOutput);
    //     exit(EXIT_FAILURE);
    // }

    fclose(fptr);
    fclose(binaryOutput);

    return 0;
}
