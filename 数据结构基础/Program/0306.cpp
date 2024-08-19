#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
    int Coefficient; // 系数
    int Exponent; // 指数
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

/* 读取多项式的函数 */
Polynomial Read() {
    Polynomial head = (Polynomial)malloc(sizeof(struct Node));
    head->Next = NULL;
    PtrToNode cur=head;

    int n;
    scanf("%d", &n); // 读取项数
    for (int i = 0; i < n; ++i) {
        int coefficient, exponent;
        scanf("%d %d", &coefficient, &exponent); // 读取每一项的系数和指数

        PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
        newNode->Coefficient = coefficient;
        newNode->Exponent = exponent;
        newNode->Next = NULL;

        cur->Next = newNode;
        cur = newNode;
    }
    return head;
}

/* 打印多项式的函数 */
void Print(Polynomial p) {
    PtrToNode node = p->Next; // 跳过哑头节点
    int isFirst = 1;
    while (node != NULL) {
        if (!isFirst) {
            printf(" ");
        } else {
            isFirst = 0;
        }
        printf("%d %d", node->Coefficient, node->Exponent);
        node = node->Next;
    }
    printf("\n");
}

/* 添加两个多项式的函数 */
Polynomial Add(Polynomial a, Polynomial b) {
    Polynomial res=(Polynomial)malloc(sizeof(struct Node));
    res->Next=NULL;
    PtrToNode cur=res;
    PtrToNode pa=a; 
    PtrToNode pb=b; 

    while (pa!=NULL&&pb!=NULL) 
    {
        if (pa->Exponent>pb->Exponent) 
        {
            cur->Next=(Polynomial)malloc(sizeof(struct Node));
            cur=cur->Next;
            cur->Exponent=pa->Exponent;
            cur->Coefficient=pa->Coefficient;
            pa=pa->Next;
        } 
        else if (pa->Exponent < pb->Exponent) 
        {
            cur->Next=(Polynomial)malloc(sizeof(struct Node));
            cur=cur->Next;
            cur->Exponent=pb->Exponent;
            cur->Coefficient=pb->Coefficient;
            pb=pb->Next;
        } 
        else 
        {
            int tmp= pa->Coefficient+ pb->Coefficient;
            if (tmp!=0) {
                cur->Next=(Polynomial)malloc(sizeof(struct Node));
                cur=cur->Next;
                cur->Exponent=pa->Exponent;
                cur->Coefficient=tmp;
            }
            pa=pa->Next;
            pb=pb->Next;
        }
    }

    while (pa!=NULL) 
    {
        cur->Next=(Polynomial)malloc(sizeof(struct Node));
        cur=cur->Next;
        cur->Coefficient=pa->Coefficient;
        cur->Exponent=pa->Exponent;
        pa=pa->Next;
    }

    while (pb!=NULL) 
    {
        cur->Next =(Polynomial)malloc(sizeof(struct Node));
        cur=cur->Next;
        cur->Coefficient=pb->Coefficient;
        cur->Exponent=pb->Exponent;
        pb=pb->Next;
    }
    cur->Next=NULL;
    return res;
}

int main() {
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}