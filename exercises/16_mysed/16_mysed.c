#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    const char* start = cmd + 2;  // 跳过 's/'
    
    // 找到第二个'/'（old_str的终止符）
    const char* second_slash = strchr(start, '/');
    if (second_slash == NULL) {
        return -1;
    }
    
    // 找到第三个'/'（new_str的终止符）
    const char* third_slash = strchr(second_slash + 1, '/');
    if (third_slash == NULL) {
        return -1;
    }
    
    // 分配并复制old_str
    int old_len = second_slash - start;
    *old_str = (char*)malloc(old_len + 1);
    strncpy(*old_str, start, old_len);
    (*old_str)[old_len] = '\0';
    
    // 分配并复制new_str
    int new_len = third_slash - (second_slash + 1);
    *new_str = (char*)malloc(new_len + 1);
    strncpy(*new_str, second_slash + 1, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char* pos = strstr(str, old);
    if (pos != NULL) {
        int old_len = strlen(old);
        int new_len = strlen(new);
        int remaining_len = strlen(pos + old_len);
        
        // 创建临时缓冲区保存替换后的内容
        char temp[MAX_LINE_LENGTH];
        strcpy(temp, pos + old_len);
        
        // 复制新字符串
        strcpy(pos, new);
        strcpy(pos + new_len, temp);
    }
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
