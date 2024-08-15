#include <bits/stdc++.h>

#define MAXN 1005

int n, initial[MAXN], part[MAXN], arr1[MAXN], arr2[MAXN];
bool flag = false;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int is_sorted(int arra[], int arrb[], int n) {
    for (int i = 0; i < n; i++) {
        if (arra[i] != arrb[i])
            return 0;
    }
    return 1;
}

void PercDown(int A[], int p, int N) { // 最大堆
    int Parent, Child;
    int X = A[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            Child++;
        if (X >= A[Child])
            break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

bool Insertion_sort(int num[], int n) {
    bool ans = false;
    int j;
    for (int i = 1; i < n; i++) {
        int lookout = num[i];
        for (j = i; j > 0 && num[j - 1] > lookout; j--)
            num[j] = num[j - 1];
        num[j] = lookout;

        if (is_sorted(num, part, n)) {
            ans = true;
            continue;
        }
        if (ans)
            break;
    }
    return ans;
}

void Heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        PercDown(arr, i, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        PercDown(arr, 0, i);
        if (is_sorted(arr, part, n)) {
            flag = true;
            continue;
        }
        if (flag) {
            return;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &initial[i]);
        arr1[i] = initial[i];
        arr2[i] = initial[i];
    }

    for (int i = 0; i < n; i++)
        scanf("%d", &part[i]);

    if (Insertion_sort(arr2, n)) {
        printf("Insertion Sort\n");
        for (int i = 0; i < n; i++) {
            printf("%d", arr2[i]);
            if (i != n - 1)
                printf(" ");
        }
        printf("\n");
    } else {
        printf("Heap Sort\n");
        Heap_sort(arr1, n);
        for (int i = 0; i < n; i++) {
            printf("%d", arr1[i]);
            if (i != n - 1)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
