#include "calc_logic.h"

#include "driverlib.h"

long multiply(short o1, short o2)
{
    //Set a 16-bit Operand into the specific Operand 1 register to specify
    //signed multiplication
    MPY32_setOperandOne16Bit(
            MPY32_MULTIPLY_SIGNED,
            o1);
    //Set 16-bit Operand 2 to begin the multiplication operation
    MPY32_setOperandTwo16Bit(
            o2);

    //Read out the result
    long result = HWREG16(MPY32_BASE + OFS_RES1);

    result = (result << 16) + HWREG16(MPY32_BASE + OFS_RES0);
    return result;
}
