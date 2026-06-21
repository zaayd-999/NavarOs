#include "history.h"

#define HISTORY_MAX 67
#define CMD_MAX 256

static char history[HISTORY_MAX][CMD_MAX];

static int history_count = 0;
static int history_index = 0;

static void scopy(char* dest, const char* src){
    int i = 0;
    while(src[i] != '\0' && i < CMD_MAX) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

static bool sempty(const char* str) {
    return str[0] == '\0';
}

void  history_init() {
    history_count = 0;
    history_index = 0;
}

void history_add(const char* cmd) {
    if(sempty(cmd)) return;
    if(cmd[0] == '!' && cmd[1] == '\0') return;
    if(history_count<HISTORY_MAX) {
        scopy(history[history_count],cmd);
        history_count++;
    } else {
        for(int i = 0; i < HISTORY_MAX -1 ; i++) {
            scopy(history[i],history[i+1]);
        }
        scopy(history[HISTORY_MAX-1],cmd);
    }

    history_index=history_count;
}

const char* history_previous() {
    if(history_count == 0) return nullptr;
    if(history_index>0) history_index--;
    return history[history_index];
}

const char* history_next(){
    if(history_count == 0) return nullptr;
    if(history_index < history_count-1){
        history_index++;
        return history[history_index];
    }

    history_index = history_count;
    return "";
}

const char* history_top() {
    if(history_count == 0) return nullptr;
    return history[history_count-1];
}