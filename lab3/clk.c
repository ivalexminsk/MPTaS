#include "clk.h"
#include "types.h"
#include "AJIOB_regs_help.h"

#define SELM_SHIFT 0
#define SELS_SHIFT 4

#define SEL_BASIC_MASK (BIT0 | BIT1 | BIT2)

#define XT1CLK_VALUE 0
#define DCOCLK_VALUE 3

#define SELM_MASK (SEL_BASIC_MASK << SELM_SHIFT)
#define SELS_MASK (SEL_BASIC_MASK << SELS_SHIFT)

#define SELM_XT1CLK (XT1CLK_VALUE << SELM_SHIFT)
#define SELS_XT1CLK (XT1CLK_VALUE << SELS_SHIFT)

#define SELM_DCOCLK (DCOCLK_VALUE << SELM_SHIFT)
#define SELS_DCOCLK (DCOCLK_VALUE << SELS_SHIFT)

void clk_init()
{
    //TODO: config FLL

    //MCLK enable to DCOCLK
    RESET_BITS(UCSCTL4, SELM_MASK);
    SET_BITS(UCSCTL4, SELM_DCOCLK);

    //SMCLK enable to DCOCLK
    RESET_BITS(UCSCTL4, SELS_MASK);
    SET_BITS(UCSCTL4, SELS_DCOCLK);

    //Pin 7.7 as peripheral
    SET_BITS(P7SEL, BIT7);
    SET_BITS(P7DIR, BIT7);

    set_vcore_up(1);

    //SVS reconfigure to mode, that can work with 01 & 11 in PMMCOREV
    // RESET_BITS(SVSMHCTL, SVSMHRRL_7);
    // SET_BITS(SVSMHCTL, SVSMHRRL_3);
}

void clk_toggle()
{
    if (UCSCTL4 & SELM_MASK)
    {
        //something not XT1CLK is selected => select xt1

        //MCLK reconf
        RESET_BITS(UCSCTL4, SELM_MASK);
        SET_BITS(UCSCTL4, SELM_XT1CLK);

        //SMCLK reconf
        RESET_BITS(UCSCTL4, SELS_MASK);
        SET_BITS(UCSCTL4, SELS_XT1CLK);

        //Vcore reconfigure to low-U
        //SET_BITS(PMMCTL0, BIT0);
        //RESET_BITS(PMMCTL0, BIT1);
        set_vcore_down(2);
        set_vcore_down(1);
    }
    else
    {
        //Vcore reconfigure to high-U
        //SET_BITS(PMMCTL0, BIT0);
        //SET_BITS(PMMCTL0, BIT1);
        set_vcore_up(2);
        set_vcore_up(3);

        //MCLK reconf
        RESET_BITS(UCSCTL4, SELM_MASK);
        SET_BITS(UCSCTL4, SELM_XT1CLK);

        //SMCLK reconf
        RESET_BITS(UCSCTL4, SELS_MASK);
        SET_BITS(UCSCTL4, SELS_XT1CLK);
    }


    //TODO:
}

void set_vcore_up (unsigned int level)
{
    // Open PMM registers for write access
    PMMCTL0_H = 0xA5;
    //TODO: fix
    // Make sure no flags are set for iterative sequences
    // while ((PMMIFG & SVSMHDLYIFG) == 0);
    // while ((PMMIFG & SVSMLDLYIFG) == 0);
    // Set SVS/SVM high side new level
    SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
    // Set SVM low side to new level
    SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
    // Wait till SVM is settled
    while ((PMMIFG & SVSMLDLYIFG) == 0);
    // Clear already set flags
    RESET_BITS(PMMIFG, (SVMLVLRIFG + SVMLIFG));
    // Set VCore to new level
    PMMCTL0_L = PMMCOREV0 * level;
    // Wait till new level reached
    if ((PMMIFG & SVMLIFG))
    {
        while ((PMMIFG & SVMLVLRIFG) == 0);
    }
    // Set SVS/SVM low side to new level
    SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;
}

void set_vcore_down (unsigned int level)
{
    // Open PMM registers for write access
    PMMCTL0_H = 0xA5;

    // Set SVS/SVM low side to new level (and enables it if need)
    SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
    while ((PMMIFG & SVSMLDLYIFG) == 0);

    // Set VCore to new level
    PMMCTL0_L = PMMCOREV0 * level;
    // Wait till new level reached
    if ((PMMIFG & SVMLIFG))
    {
        while ((PMMIFG & SVMLVLRIFG) == 0);
    }

    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;
}
