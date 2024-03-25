#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "assembler.h"

void writeBinaryIntSign(FILE * ptr, int64_t value, int numBytes)
{
    int8_t buffer = 0;
//    printf("Value: %ld\n", value);
    for (int i = numBytes - 1; i >= 0; i--)
    {
        buffer = ((int8_t)((value >> (8 * i))) & 0xFF);
    //   printf("i is: %d\n", 8*i);
    //   printf("Buffer is: %d\n", buffer);
    //   printf("-------------\n");
        fwrite(&buffer, sizeof(buffer), 1, ptr);
    }
}

void writeBinaryIntUnsigned(FILE * ptr, uint64_t value, int numBytes)
{
    uint8_t buffer = 0;
    //printf("Value in Binary Int Unsigned: %ld\n", value);
    for (int i = numBytes - 1; i >= 0; i--)
    {
        buffer = ((uint8_t)((value >> (8 * i))) & 0xFF);
        // printf("Unsigned i is: %d\n", 8*i);
        // printf("Buffer is: %d\n", buffer);
        fwrite(&buffer, sizeof(buffer), 1, ptr);
    }
}

void writeBinaryDoubleSign(FILE * ptr, double value, int numBytes)
{
    uint64_t name = *((uint64_t*) &value);
    int8_t buffer = 0;
    // int8_t check [numBytes];
    // printf("Value: %f\n", value);
    for (int i = numBytes - 1; i >= 0; i--)
    {
        buffer = ((name >> (8 * i))) & 0xFF;
        // printf("i is: %d\n", 8*i);
        // printf("Buffer is: %lf\n", (double) buffer);
        // check[i] = buffer;
        fwrite(&buffer, sizeof(buffer), 1, ptr);
    }
    // printf("Final: %lf", (*(double*)check));
}

void writeBinaryFloatSign(FILE * ptr, float value, int numBytes)
{
    uint64_t name = *((uint64_t*) &value);
    int8_t buffer = 0;
    // int8_t check [numBytes];
    // printf("Value: %f\n", value);
    for (int i = numBytes - 1; i >= 0; i--)
    {
        buffer = ((name >> (8 * i))) & 0xFF;
        // printf("i is: %d\n", 8*i);
        // printf("Buffer is: %lf\n", (float) buffer);
        // check[i] = buffer;
        fwrite(&buffer, sizeof(buffer), 1, ptr);
    }
    // printf("Final: %lf", (*(float*)check));
}