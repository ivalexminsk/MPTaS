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
    }
    else
    {
        //MCLK reconf
        RESET_BITS(UCSCTL4, SELM_MASK);
        SET_BITS(UCSCTL4, SELM_DCOCLK);

        //SMCLK reconf
        RESET_BITS(UCSCTL4, SELS_MASK);
        SET_BITS(UCSCTL4, SELS_DCOCLK);
    }


    //TODO:
}
