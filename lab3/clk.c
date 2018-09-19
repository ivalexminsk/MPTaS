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
    //DCORSEL sel to min interval (0 to 1.13 MHz)
    RESET_BITS(UCSCTL1, (BIT4 | BIT5 | BIT6));
    //SELREF => XT1CLK
    RESET_BITS(UCSCTL3, (BIT4 | BIT5 | BIT6));
    //FLLREFDIV => /1
    RESET_BITS(UCSCTL3, (BIT2 | BIT1 | BIT0));
    //FLLD => /1
    RESET_BITS(UCSCTL2, (BIT12 | BIT13 | BIT14));
    //FLLN => 21
    RESET_BITS(UCSCTL2, 0x3FF);
    SET_BITS(UCSCTL2, 21);

    //MCLK enable to DCOCLK
    RESET_BITS(UCSCTL4, SELM_MASK);
    SET_BITS(UCSCTL4, SELM_DCOCLK);

    //SMCLK enable to DCOCLK
    RESET_BITS(UCSCTL4, SELS_MASK);
    SET_BITS(UCSCTL4, SELS_DCOCLK);

    //Pin 7.7 as peripheral
    SET_BITS(P7SEL, BIT7);
    SET_BITS(P7DIR, BIT7);

    //set to maximum level
    for (unsigned int i = 1; i <= VCORE_MAX; i++)
    {
        set_vcore_up(i);
    }
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
        for (unsigned int i = (VCORE_MAX - 1); i >= VCORE_MIN; i--)
        {
            set_vcore_up(i);
        }
    }
    else
    {
        //Vcore reconfigure to high-U
        for (unsigned int i = (VCORE_MIN + 1); i <= VCORE_MAX; i++)
        {
            set_vcore_up(i);
        }

        //MCLK reconf
        RESET_BITS(UCSCTL4, SELM_MASK);
        SET_BITS(UCSCTL4, SELM_DCOCLK);

        //SMCLK reconf
        RESET_BITS(UCSCTL4, SELS_MASK);
        SET_BITS(UCSCTL4, SELS_DCOCLK);
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

    // Set SVS/SVM low side to minimum level
    SVSMLCTL = SVSLE + SVMLE;
    while ((PMMIFG & SVSMLDLYIFG) == 0);

    // Set VCore to new level
    PMMCTL0_L = PMMCOREV0 * level;
    // Wait till new level reached
    if ((PMMIFG & SVMLIFG))
    {
        while ((PMMIFG & SVMLVLRIFG) == 0);
    }

    // Set SVS/SVM low side to new level (and enables it if need)
    SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;

    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;
}
