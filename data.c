#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "assembler.h"

/*
 * Function that literally converts the data number into binary
 */
void dataProcessor(char *s, FILE *dataptr, char *outputName, int lineCounterCheck, int flag)
{
    /*Ouputting into file, 64 bits*/
    /*Check there is no ;*/
    if (strstr(s, ";") != NULL || s[0] != '\t')
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheck);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    /*
     * Remove tab
     */
    char stringLine[256];
    if (s[0] == '\t')
    {
        strcpy(stringLine, s + 1);
    }
    else
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheck);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    if (!stringLine[0])
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheck);
        remove(outputName);
        exit(EXIT_FAILURE);
    }

    if (flag == 2) //.byte
    {
        int8_t int8PassFinal = strtolToInt8(stringLine, lineCounterCheck, outputName);

        writeBinaryIntSign(dataptr, int8PassFinal, 1);
    }
    else if (flag == 3) //.ascii
    {
        /*It's just one char*/
        if (strlen(stringLine) > 1)
        {
            fprintf(stderr, "Error on line %d\n", lineCounterCheck);
            remove(outputName);
            exit(EXIT_FAILURE);
        }
        else if (stringLine[0] > 127 || stringLine[0] < -128)
        {
            fprintf(stderr, "Error on line %d\n", lineCounterCheck);
            remove(outputName);
            exit(EXIT_FAILURE);
        }

        signed char charPass = stringLine[0];

        writeBinaryIntSign(dataptr, charPass, 1);
    }
    else if (flag == 4) //.short
    {
        signed short shortPassFinal = strtolToShort(stringLine, lineCounterCheck, outputName);

        writeBinaryIntSign(dataptr, shortPassFinal, 2);
    }
    else if (flag == 5) //.int
    {
        signed int intPassFinal = strtolToInt(stringLine, lineCounterCheck, outputName);

        writeBinaryIntSign(dataptr, intPassFinal, 4);
    }
    else if (flag == 6) //.long
    {
        signed long LongPassFinal = strtolToLongLong(stringLine, lineCounterCheck, outputName);

        writeBinaryIntSign(dataptr, LongPassFinal, 8);
    }
    else if (flag == 7) //.float
    {
        float floatPassFinal = strtolToFloat(stringLine, lineCounterCheck, outputName);

        writeBinaryFloatSign(dataptr, floatPassFinal, 4);
    }
    else if (flag == 8) //.double
    {
        double doublePassFinal = strtolToDouble(stringLine, lineCounterCheck, outputName);

        writeBinaryDoubleSign(dataptr, doublePassFinal, 8);
    }
    else
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheck);
        remove(outputName);
        exit(EXIT_FAILURE);
    }
    
}




























/*
 * Error checks
 */

void errorCheckDigitNegative(char *stringCheck, int line, char *outputNameCheck)
{
    // First digit is either - or number
    if (!isdigit(stringCheck[0]) && stringCheck[0] != '-')
    {
        fprintf(stderr, "Error on line %d\n", line);
        remove(outputNameCheck);
        exit(EXIT_FAILURE);
    }

    // Data is a number
    for (int i = 1; i < strlen(stringCheck); i++)
    {
        if (!isdigit(stringCheck[i]))
        {
            fprintf(stderr, "Error on line %d\n", line);
            remove(outputNameCheck);
            exit(EXIT_FAILURE);
        }
    }
}

void errorCheckDigits (char * stringCheck, int line, char * outputNameCheck)
{
    // Data is a number
    for (int i = 0; i < strlen(stringCheck); i++)
    {
        if (!isdigit(stringCheck[i]))
        {
            fprintf(stderr, "Error on line %d\n", line);
            remove(outputNameCheck);
            exit(EXIT_FAILURE);
        }
    }
}

void notFloatingCheck(char *stringCheck, int line, char *outputNameCheck)
{
    // Data is a number
    for (int i = 0; i < strlen(stringCheck); i++)
    {
        if (stringCheck[i] == '.')
        {
            fprintf(stderr, "Error on line %d\n", line);
            remove(outputNameCheck);
            exit(EXIT_FAILURE);
        }
    }
}

void doubleNoCharactersCheck(char *stringCheck, int line, char *outputNameCheck)
{
    // Data is a number
    for (int i = 0; i < strlen(stringCheck); i++)
    {
        if ((stringCheck[i] != '-') && (!isdigit(stringCheck[i])) && (stringCheck[i] != '.') && (stringCheck[i] != 'e') && (stringCheck[i] != '+'))
        {
            fprintf(stderr, "Error on line %d\n", line);
            remove(outputNameCheck);
            exit(EXIT_FAILURE);
        }
    }
}

void isCharactersCheck(char *stringCheck, int line, char *outputNameCheck)
{
    // Data is a number
    for (int i = 0; i < strlen(stringCheck); i++)
    {
        if (!isalpha(stringCheck[i]))
        {
            fprintf(stderr, "Error on line %d\n", line);
            remove(outputNameCheck);
            exit(EXIT_FAILURE);
        }
    }
}































/*
 * Str converters
 */

int8_t strtolToInt8(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr, lineCounterCheckStr, outputNameStr);
    notFloatingCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const long int8Pass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((int8Pass > INT8_MAX) || (int8Pass < INT8_MIN))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return (int8_t)int8Pass;
}

int16_t strtolToShort(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr, lineCounterCheckStr, outputNameStr);
    notFloatingCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const long shortPass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((shortPass > SHRT_MAX) || (shortPass < SHRT_MIN))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    // Convert & write
    return (int16_t)shortPass;
}

int32_t strtolToInt(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr, lineCounterCheckStr, outputNameStr);
    notFloatingCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const long intPass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((intPass > INT32_MAX) || (intPass < INT32_MIN))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return (int32_t)intPass;
}

int64_t strtolToLongLong(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr, lineCounterCheckStr, outputNameStr);
    notFloatingCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const long longPass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return (int64_t)longPass;
}

float strtolToFloat(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    doubleNoCharactersCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const float floatPass = strtof(stringLineStr, &endptrStr);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return floatPass;
}

double strtolToDouble(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    doubleNoCharactersCheck(stringLineStr, lineCounterCheckStr, outputNameStr);
    const double doublePass = strtod(stringLineStr, &endptrStr);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return doublePass;
}







/* Addresses method */

long strtolTo24(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;
    errorCheckDigits(stringLineStr, lineCounterCheckStr, outputNameStr);
    notFloatingCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const long pass24 = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

     if ((pass24 > 16777215 ) || (pass24 < 0))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return pass24;
}


// For unsigned int convert
uint32_t strtoulToInt(char *stringLineStr, int lineCounterCheckStr, char *outputNameStr)
{
    char *endptrStr;

    errorCheckDigits(stringLineStr, lineCounterCheckStr, outputNameStr);
    notFloatingCheck(stringLineStr, lineCounterCheckStr, outputNameStr);

    const long intPass = strtoul(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((intPass > UINT32_MAX) || (intPass < 0))
    {
        fprintf(stderr, "Error on line %d\n", lineCounterCheckStr);
        remove(outputNameStr);
        exit(EXIT_FAILURE);
    }

    return (uint32_t)intPass;
}
