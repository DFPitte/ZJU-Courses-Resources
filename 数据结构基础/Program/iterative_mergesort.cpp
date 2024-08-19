#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge(ElementType list[], ElementType sorted[], int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        } else {
            sorted[k++] = list[j++];
        }
    }
    while (i < mid) {
        sorted[k++] = list[i++];
    }
    while (j < right) {
        sorted[k++] = list[j++];
    }
}

void merge_pass(ElementType list[], ElementType sorted[], int N, int length) {
    int i;
    for (i = 0; i <= N - 2 * length; i += 2 * length) {
        merge(list, sorted, i, i + length, i + 2 * length);
    }
    if (i + length < N) {
        merge(list, sorted, i, i + length, N);
    } else {
        for (int j = i; j < N; j++) {
            sorted[j] = list[j];
        }
    }
}

