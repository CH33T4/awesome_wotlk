#pragma once
#include <vector>


struct PatchDetails {
    unsigned virtualAddress;
    const char* hexBytes;
};

PatchDetails s_patches[] = {
    {
        0x004DCCF0, // lua_ScanDllStart
        "B8" "00000000" // mov eax, 1
        "C3"            // ret
    },
    {
        0x004E5CB0, // ScanDllStart
        "B8" "01000000" // mov eax, 1
        "A3" "74B4B600" // mov s_isScanDllFinished, eax
        "68" "E05C4E00" // push AwesomeWotlkLib.dll
        "E8" "0CAF0576" // call LoadLibraryA
        "55" // push ebp
        "8BEC" // mov ebp, esp
        "E8" "A410F2FF" // call 0x00406D70
        "E9" "075BF2FF" // jmp 0x0040B7D8
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCC" // int3 (15 times)
        "417765736F6D65576F746C6B4C69622E646C6C00" // AwesomeWotlkLib.dll
    },
    {
        0x0040B7D0, // StartAddress
        "E9" "DBA40D00" // jmp 0x004E5CB0
        "909090" // nop (3 times)
    }
};