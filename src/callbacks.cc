#include "sdk/amxxmodule.h"

extern AMX_NATIVE_INFO g_natives[];

// amxmodx

void OnAmxxAttach()
{
    MF_AddNatives(g_natives);
}