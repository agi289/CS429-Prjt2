#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "simulator.h"


/*
 * Str converters
 */

int8_t strtolToInt8Sim(char *stringLineStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr);
    notFloatingCheck(stringLineStr);

    const long int8Pass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
      fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((int8Pass > INT8_MAX) || (int8Pass < INT8_MIN))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    return (int8_t)int8Pass;
}

int16_t strtolToShortSim(char *stringLineStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr);
    notFloatingCheck(stringLineStr);

    const long shortPass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((shortPass > SHRT_MAX) || (shortPass < SHRT_MIN))
    {
        fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    // Convert & write
    return (int16_t)shortPass;
}

int32_t strtolToIntSim(char *stringLineStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr);
    notFloatingCheck(stringLineStr);

    const long intPass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    /*Bound check */
    if ((intPass > INT32_MAX) || (intPass < INT32_MIN))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    return (int32_t)intPass;
}

int64_t strtolToLongLongSim(char *stringLineStr)
{
    char *endptrStr;

    errorCheckDigitNegative(stringLineStr);
    notFloatingCheck(stringLineStr);

    const long longPass = strtol(stringLineStr, &endptrStr, 10);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    return (int64_t)longPass;
}

float strtolToFloatSim(char *stringLineStr)
{
    char *endptrStr;

    doubleNoCharactersCheck(stringLineStr);

    const float floatPass = strtof(stringLineStr, &endptrStr);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    return floatPass;
}

double strtolToDoubleSim(char *stringLineStr)
{
    char *endptrStr;

    doubleNoCharactersCheck(stringLineStr);
    const double doublePass = strtod(stringLineStr, &endptrStr);

    if ((errno == ERANGE) || (errno == EINVAL))
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    return doublePass;
}























void errorCheckDigitNegative(char *stringCheck)
{
    // First digit is either - or number
    if (!isdigit(stringCheck[0]) && stringCheck[0] != '-')
    {
       fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
    }

    // Data is a number
    for (int i = 1; i < strlen(stringCheck); i++)
    {
        if (!isdigit(stringCheck[i]))
        {
            fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
        }
    }
}


void notFloatingCheck(char *stringCheck)
{
    // Data is a number
    for (int i = 0; i < strlen(stringCheck); i++)
    {
        if (stringCheck[i] == '.')
        {
            fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
        }
    }
}

void doubleNoCharactersCheck(char *stringCheck)
{
    // Data is a number
    for (int i = 0; i < strlen(stringCheck); i++)
    {
        if ((stringCheck[i] != '-') && (!isdigit(stringCheck[i])) && (stringCheck[i] != '.') && (stringCheck[i] != 'e') && (stringCheck[i] != '+'))
        {
            fprintf(stderr, "Simulation error\n");
        exit(EXIT_FAILURE);
        }
    }
}
