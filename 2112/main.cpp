#include <iostream>
#include <algorithm>

using namespace std;
int test,d,k,w,mincount;
int film[13][20];

void replacefilm(int v,int in){
    for(int q=0;q<w;++q){
        film[in][q]=v;
    }
}
void copyfilm(int temp[],int in){
    for(int q=0;q<w;++q){
        temp[q]=film[in][q];
    }
}
void recoverfilm(int temp[],int in){
    for(int q=0;q<w;++q){
        film[in][q]=temp[q];
    }
}
int checking(int x){
    int cc=1;
    int y=0;
    while((cc<k) && (y<d-1)){
        if(cc+d-1-y<k){
            break;
        }
        if(film[y][x] == film[y+1][x]){
            ++cc;
        }
        else{
            cc=1;
        }
        ++y;
    }
    if(cc==k){
        return 1;
    }
    else{
        return -1;
    }
}
void QC(int num,int notyet){
    int sum=0;
    int ce=0;
    for(int p=0;p<w;++p){
        ce=checking(p);
        if(ce==-1){
            break;
        }
        sum += ce;
    }
    if(sum==w){
        mincount=min(mincount,num);
        return;
    }
    else{
        int temp[w];
        for(int index=notyet;index<d;++index){
            ++num;
            if(num>=mincount){
                return;
            }
            copyfilm(temp,index);
            replacefilm(0,index);
            QC(num,index+1);
            replacefilm(1,index);
            QC(num,index+1);
            recoverfilm(temp,index);
            --num;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>test;
    for(int t=1;t<=test;++t){
        cin>>d>>w>>k;
        mincount=k;
        for(int a=0;a<d;++a){
            for(int b=0;b<w;++b){
                cin>>film[a][b];
            }
        }
        if (k==1){
            mincount=0;
        }
        else{
            QC(0,0);
        }
        cout<<"#"<<t<<" "<<mincount<<"\n";
    }
    return 0;
}