#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

int main(int argc, char** argv){
    struct stat ent;
    time_t ori_time, aft_time;
    char *path = argv[1];
    char command[1000] = {0};
    
    assert(stat(path, &ent) == 0);

    ori_time = ent.st_mtime;
    printf("Filename: %s\n", path);
    printf("Time of last modification: %s", ctime(&ori_time));
    printf("content:\n");
    strcat(command, "cat ");
    strcat(command, path);
    system(command);

    while(1){
        stat(path, &ent);
        aft_time = ent.st_mtime;
        if(ori_time != aft_time){
            printf("\n----------------------------\n");
            printf("New  modified time: %s", ctime(&aft_time));
            printf("Last modified time: %s", ctime(&ori_time));
            printf("New content:\n");
            system(command);
            ori_time = aft_time;
        }
    }

    return 0;
}