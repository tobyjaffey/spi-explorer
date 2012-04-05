#ifndef SHELL_H
#define SHELL_H 1

#include "common.h"

void shell_init(void);
void shell_eval(const uint8_t *str, uint32_t len);

#endif

