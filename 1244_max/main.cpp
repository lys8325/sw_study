#include <iostream>
#include <string.h>

using namespace std;
char origin[10];
char mp[10]={0};
int n,len;

void findanswer(int s,int cn){
    if(cn > n){
        return;
    }
    int a;
    for(int i=s;i<len-1;++i){
        for(int j=i+1;j<len;++j){
            swap(origin[i],origin[j]);
            if(strncmp(origin,mp,len)>0 && cn == n){
                strncpy(mp,origin,len);
            }
            findanswer(0,cn+1);
            swap(origin[j],origin[i]);
        }
    }
}

int main() {
    int test,flag;
    cin>>test;
    for(int t=1;t<=test;++t){
        flag=0;
        cin>>origin>>n;
        len=strlen(origin);
        if(n>=len){
            if(len%2==0 && n%2==0){
                n=len-1;
            }
            if(len%2==0 && n%2!=0){
                n=len-1;flag=1;
            }
            if(len%2!=0 && n%2==0){
                n=len-1;
            }
            if(len%2!=0 && n%2!=0){
                n=len-1;flag=1;
            }
        }
        for(int i=0;i<10;++i){
            mp[i]=0;
        }
        findanswer(0,1);
        if(flag==1){
            swap(mp[len-1],mp[len-2]);
        }
        cout<<"#"<<t<<" "<<mp<<"\n";
    }
    return 0;
}