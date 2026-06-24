#include "../constants.h"
#include "command_parser.h"

static bool is_space(char c) {
    return c == ' ' || c == '\t';
}

static bool starts_with_dash(const char* s) {
    return s[0] == '-';
}

static const char* get_flag_key(const char* s) {
    if (s[0] == '-' && s[1] == '-')
        return s + 2;

    if (s[0] == '-')
        return s + 1;

    return s;
}

Command parse_command(const char* cmd) {
    static char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];

    Command command;
    command.name = 0;
    command.argc = 0;
    command.flagc = 0;

    int token_count = 0;
    int i = 0;

    while (cmd[i] != '\0') {
        while (is_space(cmd[i]))
            i++;

        if (cmd[i] == '\0')
            break;

        int j = 0;
        bool in_quotes = false;
        char quote_char = 0;

        while (cmd[i] != '\0' && j < MAX_TOKEN_LENGTH - 1) {
            if (cmd[i] == '\\') {
                i++;

                if (cmd[i] == '"' || cmd[i] == '\'' || cmd[i] == '\\') {
                    tokens[token_count][j++] = cmd[i++];
                } else {
                    tokens[token_count][j++] = '\\';
                }

                continue;
            }

            if ((cmd[i] == '"' || cmd[i] == '\'') && !in_quotes) {
                in_quotes = true;
                quote_char = cmd[i++];
                continue;
            }

            if (in_quotes && cmd[i] == quote_char) {
                in_quotes = false;
                quote_char = 0;
                i++;
                continue;
            }

            if (!in_quotes && is_space(cmd[i]))
                break;

            tokens[token_count][j++] = cmd[i++];
        }

        tokens[token_count][j] = '\0';
        token_count++;

        if (token_count >= MAX_TOKENS)
            break;
    }

    if (token_count == 0)
        return command;

    command.name = tokens[0];

    for (int t = 1; t < token_count; t++) {
        if (starts_with_dash(tokens[t])) {
            if (command.flagc >= MAX_FLAGS)
                continue;

            Flag* flag = &command.flags[command.flagc++];
            flag->key = get_flag_key(tokens[t]);

            if (t + 1 < token_count && !starts_with_dash(tokens[t + 1])) {
                flag->type = FLAG_STRING;
                flag->value.string = tokens[t + 1];
                t++;
            } else {
                flag->type = FLAG_BOOL;
                flag->value.boolean = true;
            }
        } else {
            if (command.argc < MAX_ARGS) {
                command.args[command.argc++] = tokens[t];
            }
        }
    }

    return command;
}