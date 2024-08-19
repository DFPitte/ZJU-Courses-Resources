#include<bits/stdc++.h>
using namespace std;

int main()
{
    int x,y;
    cin>>x;
    unsigned int ux = (unsigned)x;
    cout <<((x < 0) == (-x > 0))<<" "<< -x <<" "<< (x<0)<< " "<<(-x > 0);
    return 0;
}