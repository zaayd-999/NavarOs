#ifndef SHELL_H
#define SHELL_H

void shell_init();
void shell_print_prompt();
void shell_execute_cmd(const char* cmd);

#endif