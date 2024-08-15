#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

/* Read 函数从标准输入读取多项式的系数和指数，并构建链表 */
List Read() {
    List L = (List)malloc(sizeof(struct Node)); // 创建哑头节点
    L->Next = NULL;
    Position Tail = L; // 尾指针，用于指向链表的最后一个节点

    int N; // 元素个数
    scanf("%d", &N); // 读取元素个数

    for (int i = 0; i < N; ++i) {
        ElementType Element;
        scanf("%d", &Element); // 读取元素值

        Position P = (Position)malloc(sizeof(struct Node)); // 创建新节点
        P->Element = Element;
        P->Next = NULL;

        Tail->Next = P; // 将新节点添加到链表尾部
        Tail = P; // 更新尾指针
    }

    return L;
}

/* Print 函数遍历链表并打印每个节点的元素 */
void Print(List L) {
    Position P = L->Next; // 跳过哑头节点
    int isFirst = 1; // 用于控制输出格式，确保在第一个元素前不打印空格

    while (P != NULL) {
        if (isFirst) {
            isFirst = 0; // 已经处理过第一个元素
        } else {
            printf(" "); // 在元素之间打印空格
        }
        printf("%d", P->Element);
        P = P->Next; // 移动到下一个节点
    }
    printf("\n"); // 所有元素打印完毕后换行
}

List Reverse( List L ) 
{
    Position head=L;
    Position cur=L->Next;
    Position nxt=NULL;
    head->Next=NULL;
    while(cur!=NULL)
    {
        nxt=cur->Next;
        cur->Next=head->Next;
        head->Next=cur;
        cur=nxt;
    }
    return head;
}

int main() {
    List L1, L2;
    L1 = Read(); // 从标准输入读取链表
    L2 = Reverse(L1); // 反转链表
    Print(L1); // 打印原始链表，注意在Reverse函数中原始链表会被破坏
    Print(L2); // 打印反转后的链表
    return 0;
}

/* Reverse 函数实现请参考前面的代码 */
