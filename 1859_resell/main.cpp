#include <iostream>
#include <queue>
#define MAXN 1000000

using namespace std;

int n,mp,mi;
long long int total;
int predict[MAXN+1];
priority_queue<pair<int,int>> calc;

void answer(int index){
    int b;
    b= index;
    while(!calc.empty()){
        calc.pop();
    }
    for(int a=index;a<=n;++a){
        calc.push({predict[a],a});
    }
    mp=calc.top().first;

    mi=calc.top().second;
    while(b < mi){
        total += (mp - predict[b]);
        ++b;
    }
    if(mi<n){
        answer(mi+1);
    }
    else{return;}

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;
    cin>>test;
    for(int t=1;t<=test;++t){
        cin>>n;
        total=0;
        for(int j=1;j<=n;++j){
            cin>>predict[j];
        }
        answer(1);

        cout<<"#"<<t<<" "<<total<<"\n";
    }
}