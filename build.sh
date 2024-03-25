#!/usr/bin/sh
gcc -o assembler assembler.c assembler.h instructions.c opcode.c data.c binary.c
gcc -o simulator simulator.c simulator.h simulatorCheck.c