#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Stack {
    int *a;
    int top;
    int cap;
};


void init(Stack &st, int S) {
    st.cap = S;
    st.top = -1;
    st.a = new int[S];
}

bool empty(Stack &st) { return st.top == -1; }
bool isEmpty(Stack &st) { return st.top == -1; }
bool isFull(Stack &st) { return st.top == st.cap - 1; }

int size(Stack &st) { return st.top + 1; }

int topEl(Stack &st) {
    if (isEmpty(st)) return -1;
    return st.a[st.top];
}

int peek(Stack &st) {
    if (isEmpty(st)) return -1;
    return st.a[st.top];
}

void push(Stack &st, int x) {
    if (!isFull(st))
        st.a[++st.top] = x;
}

int pop(Stack &st) {
    if (isEmpty(st)) return -1;
    return st.a[st.top--];
}

void printStack(Stack &st, const char *name) {
    cout << "\n" << name << " (top -> bottom):\n";
    while (!isEmpty(st)) {
        cout << pop(st) << " ";
    }
    cout << "\n";
}

int main() {
    srand(time(NULL));

    int variant = 24;
    int S = variant * 5 + 50;
    cout << "Variant: " << variant << "\n";
    cout << "Stack size S = " << S << "\n";

    Stack st, evenSt, oddSt;
    init(st, S);
    init(evenSt, S);
    init(oddSt, S);


    for (int i = 0; i < S; i++) {
        push(st, rand() % 1000 + 1);
    }


    while (!isEmpty(st)) {
        int x = pop(st);
        if (x % 2 == 0) push(evenSt, x);
        else push(oddSt, x);
    }


    printStack(evenSt, "Even stack");
    printStack(oddSt, "Odd stack");

    delete[] st.a;
    delete[] evenSt.a;
    delete[] oddSt.a;

    return 0;
}
