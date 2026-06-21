#ifndef HISTORY_H
#define HISTORY_H

void history_init();
void history_add(const char* cmd);

const char* history_previous();
const char* history_next();
const char* history_top();

#endif