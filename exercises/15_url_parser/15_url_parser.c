#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // 查找 '?' 的位置，获取参数部分
    const char* params = strchr(url, '?');
    if (params == NULL) {
        printf("URL中没有参数\n");
        return 0;
    }
    
    params++;  // 跳过'?'
    
    // 复制参数部分到可修改的缓冲区
    char buffer[512];
    strncpy(buffer, params, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // 使用strtok分割参数
    char* param = strtok(buffer, "&");
    while (param != NULL) {
        // 分割key和value
        char* equals = strchr(param, '=');
        if (equals != NULL) {
            *equals = '\0';  // 终止key字符串
            char* key = param;
            char* value = equals + 1;
            printf("key = %s, value = %s\n", key, value);
        } else {
            printf("key = %s, value = \n", param);
        }
        param = strtok(NULL, "&");
    }

    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}