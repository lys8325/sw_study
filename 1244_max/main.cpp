#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;
priority_queue<pair<int,int>> PQ;
char origin[10];
int t[10];
int n,len,mp,temp;

void transfer(){
    temp=0;
    for(int i=0;i<len;++i){
        cout<<atoi((origin))*(10^(len-i-1))<<endl;
        temp += (origin[i]-'0')*(10);
    }
    return temp;
}

void findanswer(int s,int cn){
    int a;
    for(int i=s;i<len;++i){
        PQ.push({origin[i],i});
    }
    while(s == (a=PQ.top().second)){
        PQ.pop();
        ++s;
    }
    PQ.pop();
    if(PQ.empty()){
        swap(origin[a],origin[a-1]);
    }
    else{
        swap(origin[s],origin[a]);
    }
    while (!PQ.empty()){
        PQ.pop();
    }
    if(cn != n){
        findanswer(s+1,cn+1);
    }
    else{
        return;
    }
}

int main() {
    int test;
    cin>>test;
    for(int t=1;t<=test;++t){
        cin>>origin>>n;
        len=strlen(origin);
        transfer();
        cout<<n;
        findanswer(0,0);
        cout<<"#"<<t<<" "<<origin<<"\n";
    }



    return 0;
}