#ifndef _READER_H
#define _READER_H

#include <stdio.h>
#include <stdint.h>

typedef int (*input_fn)(uint8_t bytecode);

_Bool read_bytecode(const char *, input_fn);

#endif