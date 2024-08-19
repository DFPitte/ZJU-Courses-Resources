#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define min(a,b) ((a>b)?(b):(a))
#define small(x,c) min(x,c-x)
clock_t start,stop;//define start and stop
double duration;
int n,c;
int a[100001]={0},b[100001];//array a is used to mark if the number has appeared
//for example,if a[i]=1,means number i is in the array b
//array b is used to store the n given numbers
//suppose the integers are no larger than 100000 
clock_t start,stop;
double duration;
#define min(a,b) ((a>b)?(b):(a))
#define small(x,c) min(x,c-x)
clock_t start,stop;//define start and stop
double duration;
int randint(int v)//generate a random number between 1 and v
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
int main(void)
{
    int n,c,a[100001],b[100001];
    scanf("%d %d",&n,&c);//read n and c
    int flag=0;
    create_data(b,n,100000,c);
    start=clock();//start the clock
    for(int i=0;i<n;i++)
    {
        if(a[c-b[i]]==1)
        {
            printf("%d %d\n",b[i],c-b[i]);//if c-b[i] is appeared,than print the two numbers
            flag=1;//meaning the number are found
        }
        a[b[i]]=1;//mark array a[b[i]] as 1
    }
    if(flag==0)
    printf("No found\n");//output nofound if flag=0
    stop=clock();//end the clock
    duration=((double)(stop-start))/CLK_TCK;
    printf("%f\n%f\n",(double)(stop-start),duration);//output the time
    return 0;
}