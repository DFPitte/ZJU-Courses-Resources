#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define min(a,b) ((a>b)?(b):(a))
#define small(x,c) min(x,c-x)
clock_t start,stop;//define start and stop
double duration;
int randint(int v)
{
	if (v < RAND_MAX){
		return rand()%(v-1)+1;
	} else{
		return (rand()*100+rand()%100)%(v-1)+1;
	}
}
int create_data(int arr[],int n,int v,int c){
	int flag[v];
	memset(flag,0,sizeof(flag));
	int cnt = 0;
	int x,pos1,pos2;
	//if c > v and x < (c-v),get another x,until x >= (c-v)
	//to avoid b = (c-x) > v
	if (c>v)
		while ((x = randint(v)) < c-v);
	else
		x = randint(c);
	pos1 = randint(n);
	arr[pos1] = x;
	flag[c-x] = 1;
	//to avoid pos2==pos1
	while ((pos2=randint(n))==pos1);
	arr[pos2] = c-x; 
	flag[x] = 1;
	while (cnt < n){
		//(arr[cnt]!=0) means the answer a or b is at arr[cnt]
		if (arr[cnt]){
			cnt++;
			continue;
		}
		x = randint(v);
		//(c-x<0||c-x>v) means x is impossible to be one of the answer
		if (c-x<0||c-x>v){
			arr[cnt++] = x;
		//to avoid there are two (c/2) in arr[],which can be a pair of answer
		}else if (flag[x]&&c%2==0&&x==c/2){
			continue;
		//if there is (c-x) in arr[],x can't appear in arr[]
		//so we can put another (c-x) into arr[]
		}else if (flag[x]){
			arr[cnt++] = c-x;
    	}else{
		    arr[cnt++] = x;
		    flag[c-x] = 1;
		}
	}
	//return the smaller one of (a,b)
	return small(arr[pos1],c);
}
int main()
{
    int n,a[100001],c,arr[100001],v=10000;//define n,c and a
    scanf("%d %d",&n,&c);//read n and c
    memset(arr,0,sizeof(arr));
    create_data(a,n,v,c);
    start=clock();//start the clock
    int flag=0;//flag is used to mark if the numbers are found 
    for(int i=0;i<n;i++)//Traverse the combination of all array elements
    for(int j=i+1;j<n;j++)
    {
        if(a[i]+a[j]==c)//if the sum of the numbers equals to c
        {
            printf("%d %d\n",a[i],a[j]);//print a[i] and a[j]
            flag=1;//mark flag as 1,meaning the numbers are found
        }
    }
    if(flag==0)printf("No Found\n");//if didn't find the number,print nofound
    stop=clock();//end the clock
    duration=((double)(stop-start))/CLK_TCK;
    printf("%f\n%f\n",(double)(stop-start),duration);//output the time
    return 0;
}