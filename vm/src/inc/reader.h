#ifndef _READER_H
#define _READER_H

#include <stdio.h>

typedef int (*input_fn)(char input);

_Bool read_bytecode(const char *, input_fn);

#endif