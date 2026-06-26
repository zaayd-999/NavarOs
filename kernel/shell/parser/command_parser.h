#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "parser_constants.h"

enum FlagType {
    FLAG_STRING,
    FLAG_BOOL
};

struct Flag {
    const char* key;
    FlagType type;
    
    union {
        bool boolean;
        const char* string;
    } value;
};

struct Command {
    const char* name;
    
    const char* args[MAX_ARGS];
    int argc = 0;
    
    Flag flags[MAX_FLAGS];
    int flagc = 0;
};

Command parse_command(const char* cmd);

#endif