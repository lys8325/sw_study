#include <iostream>
using namespace std;

int midpoint(int a,int b, int c){
    return min(a,b)^min(b,c)^min(c,a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t,n;
    int table[200000];
    cin>>t;

    for(int i=1;i<=t;++i){
        cin>>n;
        for(int j=1;j<=2*n-1;++j){
            cin>>table[j];
        }

        for(int m=2;m<=n;++m){
            for(int a=1;a<=2*(n-m)+1;++a){
                table[a]=midpoint(table[a],table[a+1],table[a+2]);
            }
        }
        cout<<"#"<<i<<" "<<table[1]<<"\n";
    }
    return 0;
}