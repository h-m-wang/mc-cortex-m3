#include "sys_ctl.h"

void Sys_Reset(void)
{
    SYSCTRL->GLBRESET |= SYSCTRL_RESET;

}

void Sys_Remap(void)
{
    SYSCTRL->REMAPPER |= SYSCTRL_REMAP;
}

uint32_t Get_Flash_Data_base(void)
{
    return ((SYSCTRL->REMAPPER & 0xffffff00)>>8);
}
