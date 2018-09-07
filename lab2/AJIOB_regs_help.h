#pragma once

#define SET_BITS(reg, mask)                                             \
  reg |= mask

#define RESET_BITS(reg, mask)                                           \
  reg &= ~mask
