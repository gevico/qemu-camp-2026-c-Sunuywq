// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    // 去掉前导空格
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t') {
        start++;
    }
    
    // 去掉后导空格
    int end = strlen(str) - 1;
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }
    
    if (start > 0) {
        for (int i = 0; i <= end - start; i++) {
            str[i] = str[start + i];
        }
    }
    str[end - start + 1] = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // 去掉尾部的换行符
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      // 空行，跳过
      continue;
    }

    if (line[0] == '#') {
      // 这是一个新单词
      if (in_entry && strlen(current_word) > 0 && strlen(current_translation) > 0) {
        // 保存之前的条目
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
      }
      
      // 提取新单词
      strcpy(current_word, line + 1);  // 跳过 '#'
      memset(current_translation, 0, sizeof(current_translation));
      in_entry = 1;
    } else if (strncmp(line, "Trans:", 6) == 0) {
      // 这是翻译行
      strcpy(current_translation, line + 6);  // 跳过 'Trans:'
      trim(current_translation);
    }
  }

  // 保存最后的条目
  if (in_entry && strlen(current_word) > 0 && strlen(current_translation) > 0) {
    hash_table_insert(table, current_word, current_translation);
    (*dict_count)++;
  }

  fclose(file);
  return 0;
}
