#include <iostream>
#include <string>
#include <vector>
using namespace std;

int t;
string target, original;
vector<int> makeTable(){
    int strLen = target.length();
    int j = 0;
    vector<int> pi(strLen, 0);
    for(int i=1;i<strLen;++i){
        while(j > 0 && target[i] != target[j]){
            j = pi[j-1];
        }
        if(target[i] == target[j]){
            pi[i] = ++j;
        }
    }
    return pi;
}

vector<int> kmp(){
    vector<int> ans;
    vector<int> pi = makeTable();
    int oriLen = original.length();
    int tarLen = target.length();
    int j = 0;
    for(int i=0;i<oriLen;++i){
        while(j>0 && original[i] != target[j]){
            j = pi[j-1];
        }
        if(original[i] == target[j]){
            if(j == tarLen-1){
                ans.push_back(i-tarLen+1);
                j=0;
            }else{
                ++j;
            }
        }
    }
    return ans;
}

int main() {

    for(int i=0;i<10;++i){
        cin>>t>>target>>original;
        cout<<"#"<<t<<" "<<kmp().size()<<"\n";
    }

    return 0;
}
