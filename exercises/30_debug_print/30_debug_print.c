#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#if DEBUG_LEVEL >= 3
#define DEBUG_PRINT(fmt, ...) \
    do { \
        void *buffer[10]; \
        int nptrs = backtrace(buffer, 10); \
        printf("DEBUG: func=%s, line=%d, backtrace=%d frames, " fmt "\n", __func__, __LINE__, nptrs, ##__VA_ARGS__); \
    } while (0)
#elif DEBUG_LEVEL >= 2
#define DEBUG_PRINT(fmt, ...) \
    do { \
        printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#elif DEBUG_LEVEL >= 1
#define DEBUG_PRINT(fmt, ...) \
    do { \
        printf("DEBUG: func=%s, line=%d\n", __func__, __LINE__); \
    } while (0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)

#endif




















void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}
