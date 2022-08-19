#ifndef _PARSER_H
#define _PARSER_H

#include <stdint.h>

typedef struct {
    uint8_t args[4];
    char command;
} l3vm_command;

typedef struct {
    char* source;
    l3vm_command* commands;
} l3vm_parser;

#endif