#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int8_t strtolToInt8Sim(char *stringLineStr);

int16_t strtolToShortSim(char *stringLineStr);

int32_t strtolToIntSim(char *stringLineStr);

int64_t strtolToLongLongSim(char *stringLineStr);

float strtolToFloatSim(char *stringLineStr);

double strtolToDoubleSim(char *stringLineStr);

void errorCheckDigitNegative(char *stringCheck);

void notFloatingCheck(char *stringCheck);

void doubleNoCharactersCheck(char *stringCheck);