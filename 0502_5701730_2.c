#define _CRT_SECURE_NO_WARNINGS //scanf 오류 때문에 선언

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;
//스택사용하여
typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int item) {
    s->data[++(s->top)] = item;
}

int pop(Stack* s) {
    return s->data[(s->top)--];
}
int isEmpty(Stack* s) {
    return(s->top == -1);
}
int isEmptyQueue(QueueType* q) {
    return (q->front == q->rear);
}
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int is_alpha(char ch) {
    return isalpha(ch);
}

char to_lower(char ch) {
    return tolower(ch);
}

void clean_input(char* str) {
    int i, j = 0;
    for (i = 0; str[i]; i++) {
        if (is_alpha(str[i])) {
            str[j++] = to_lower(str[i]);
        }
    }
    str[j] = '\0';
}

int palindrome(char* str) {//회문
    QueueType q;
    Stack s;
    init_queue(&q);
    init_stack(&s);

    clean_input(str);

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        enqueue(&q, str[i]);
        push(&s, str[i]);
    }

    while (!isEmpty(&s) && !isEmpty(&q)) {
        if (pop(&s) != dequeue(&q)) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[MAX_QUEUE_SIZE];
    int choice;
    while (1) {
        printf("1. 회문 입력\n");
        printf("2. 회문 검사\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // 입력 버퍼를 지우기 위해서

        switch (choice) {
        case 1:
            printf("회문을 입력하세요: ");
            scanf("%[^\n]s", str);
            break;
        case 2:
            
            if (palindrome(str)) {
                printf("입력한 문자열은 회문입니다.\n");
            }
            else {
                printf("입력한 문자열은 회문이 아닙니다.\n");
            }
            break;
        case 3:
            exit(0);
        default:
            printf("잘못된 메뉴 선택\n");
            break;
        }
    }
    return 0;
}