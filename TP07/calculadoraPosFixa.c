#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    float items[MAX];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

void push(Stack *stack, float value) {
    if (!isFull(stack)) {
        stack->items[++stack->top] = value;
    } else {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

float pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top--];
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void printInfix(Stack *stack) {
    if (!isEmpty(stack)) {
        float value = pop(stack);
        printInfix(stack);
        printf("%.2f ", value);
    }
}

void printPrefix(Stack *stack) {
    if (!isEmpty(stack)) {
        float value = pop(stack);
        printf("%.2f ", value);
        printPrefix(stack);
    }
}

void evaluateExpression(char *expression) {
    Stack stack;
    initialize(&stack);

    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (token[0] >= '0' && token[0] <= '9') {
            float value = atof(token);
            push(&stack, value);
        } else {
            float operand2, operand1, result;
            switch (token[0]) {
                case '+':
                case '-':
                case '*':
                case '/':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    switch (token[0]) {
                        case '+':
                            result = operand1 + operand2;
                            break;
                        case '-':
                            result = operand1 - operand2;
                            break;
                        case '*':
                            result = operand1 * operand2;
                            break;
                        case '/':
                            result = operand1 / operand2;
                            break;
                    }
                    push(&stack, result);
                    break;
                case 's':
                    operand1 = pop(&stack);
                    result = sin(operand1);
                    push(&stack, result);
                    break;
                case 'c':
                    operand1 = pop(&stack);
                    result = cos(operand1);
                    push(&stack, result);
                    break;
                case 't':
                    operand1 = pop(&stack);
                    result = tan(operand1);
                    push(&stack, result);
                    break;
                case 'l':
                    operand1 = pop(&stack);
                    result = log10(operand1);
                    push(&stack, result);
                    break;
                case 'r':
                    operand1 = pop(&stack);
                    result = sqrt(operand1);
                    push(&stack, result);
                    break;
                case '^':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    result = pow(operand1, operand2);
                    push(&stack, result);
                    break;
                case '%':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    result = fmod(operand1, operand2);
                    push(&stack, result);
                    break;
                default:
                    printf("Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }

    printf("Resultado: %.2f\n", pop(&stack));
    printf("Notacao infixa: ");
    printInfix(&stack);
    printf("\nNotacao pre-fixa: ");
    printPrefix(&stack);
    printf("\n");
}

int main() {
    char expression[MAX];

    printf("Digite a expressao posfixa: ");
    fgets(expression, sizeof(expression), stdin);

    expression[strcspn(expression, "\n")] = '\0';

    evaluateExpression(expression);

    return 0;
}

