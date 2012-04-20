#/bin/sh

g++ ASM/Converter.cpp EX/EX.cpp ID/ID.cpp IF/IF.cpp MEM/MEM.cpp WB/WB.cpp UTIL/utils.cpp UTIL/MEMSlot.cpp driver.cpp -o test.bin
./test.bin
