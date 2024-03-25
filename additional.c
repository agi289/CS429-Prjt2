

// /*Functions*/
// void convbd()
// {
//     // read 1 byte from sp-1
//     uint8_t byte = readMemory(sp - 1, 1);

//     double newValue = (double)byte;

//     writeMemory(sp - 1, *(uint64_t *)&newValue, 8);

//     sp = sp + 7;
//     PC = PC + 1;
// }

// void convdf()
// {
//     uint64_t pass = readMemory((sp - 8), 8);
//     double passIn = *(double *)&pass;
//     float finalPass = (float)passIn;

//     writeMemory((sp - 8), *(uint32_t *)&finalPass, 4);
//     sp = sp - 4;
//     PC = PC + 1;
// }

