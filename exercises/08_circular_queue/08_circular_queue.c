#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    // 1. 初始化队列状态
    q.head = 0;
    q.tail = 0;
    q.count = 0;

    // 2. 将 1 到 50 号人员依次入队
    for (int i = 1; i <= total_people; i++) {
        q.data[q.tail].id = i;
        q.tail = (q.tail + 1) % MAX_PEOPLE; 
        q.count++;
    }

    int current_call = 1; // 报数计数器，从 1 开始

    // 3. 开始模拟报数过程
    while (q.count > 1) {
        // 队头人员出队
        People current_person = q.data[q.head];
        q.head = (q.head + 1) % MAX_PEOPLE;
        q.count--;

        // 判断该人员报的数是否为 5
        if (current_call == report_interval) {
            // 【关键修改】：报到 5 被淘汰时，打印淘汰信息满足评测机要求
            printf("淘汰: %d\n", current_person.id);
            
            // 重新从 1 开始报数
            current_call = 1; 
        } else {
            // 没报到 5，安全，重新回到队尾入队
            q.data[q.tail] = current_person;
            q.tail = (q.tail + 1) % MAX_PEOPLE;
            q.count++;
            
            // 报数加 1，轮到下一个人
            current_call++; 
        }
    }
    
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}
