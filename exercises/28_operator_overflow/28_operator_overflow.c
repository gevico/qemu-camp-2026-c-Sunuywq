#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) \
    carry ? "Overflow" : "Not Overflow"

int check_add_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "add %2, %0\n\t"       // 执行加法a + b
        "setc %1\n\t"          // 如果进位标志位被设置，则setc = 1
        : "=r" (a), "=r" (carry)
        : "r" (b), "0" (a)
    );
    return carry;
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "sub %2, %0\n\t"       // 执行减法a - b
        "setc %1\n\t"          // 如果进位标志位被设置（借位），则setc = 1
        : "=r" (a), "=r" (carry)
        : "r" (b), "0" (a)
    );
    return carry;
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
    unsigned int high_bits;
    __asm__ volatile(
        "mull %2\n\t"           // edx:eax = eax * b (a already in eax)
        "movl %%edx, %0\n\t"    // high_bits = edx
        : "=r" (high_bits)
        : "a" (a), "r" (b)
        : "edx"
    );
    return high_bits != 0;
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char is_div_zero;
    __asm__ volatile(
        "test %1, %1\n\t"      // 测试b是否为0
        "setz %0\n\t"          // 如果b为0，则is_div_zero = 1
        : "=r" (is_div_zero)
        : "r" (b)
    );
    return is_div_zero;
}

int main() {
    printf("(UINT_MAX + 1)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(UINT_MAX, 1)));   // 1
    printf("(1, 0)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(1, 0)));  
    printf("(0, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(0, 1)));          // 1
    printf("(2, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(2, 1)));
    printf("(UINT_MAX, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(UINT_MAX, 2)));   // 1
    printf("(1, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(1, 2)));
    printf("(10, 0)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(10, 0)));                         // 1
    printf("(2, 1)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(2, 1)));
    return 0;
}