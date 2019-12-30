#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int,int>> process;
int test,n;
int proc,maxcon,minlen,len,con,nocon;
int dy[]={1,-1,0,0};
int dx[]={0,0,1,-1};
int **map;

int m_length(){
    int l=0;
    for(int a=0;a<n;++a){
        for(int b=0;b<n;++b){
            if(map[a][b] == 2){
                ++l;
            }
        }
    }
    return l;
}

void findanswer(int num,int check){
    if(num+nocon-(check)<maxcon){
        return;
    }
    for(int d=0;d<4;++d){
        int possible=0;
        int y=process[check].first;
        int x=process[check].second;

        while(map[y+dy[d]][x+dx[d]]==0){
            y += dy[d];
            x += dx[d];
            if(y==0||y==(n-1)||x==0||x==(n-1)){
                possible=1;
                break;
            }
        }

        if(possible==1){
            y=process[check].first;
            x=process[check].second;
            while(map[y+dy[d]][x+dx[d]]==0){
                y += dy[d];
                x += dx[d];
                map[y][x]=2;
                if(y==0||y==(n-1)||x==0||x==(n-1)){
                    ++num;
                    break;
                }
            }
        }

        if(check<nocon-1){
            findanswer(num,check+1);
        }
        else if(check==nocon-1){
            len=m_length();
            if(num>maxcon){
                maxcon=num;
                minlen=len;
            }
            else if(num==maxcon){
                minlen=min(minlen,len);
            }
        }
        if(possible==1){
            y=process[check].first;
            x=process[check].second;
            while(map[y+dy[d]][x+dx[d]]==2){
                y += dy[d];
                x += dx[d];
                map[y][x]=0;
                if(y==0||y==(n-1)||x==0||x==(n-1)){
                    --num;
                    break;
                }
            }
        }

    }


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>test;
    for(int i=1;i<=test;++i){
        maxcon=0;
        minlen=145;
        process.clear();
        cin>>n;
        map =new int*[n];
        for(int j=0;j<n;++j){
            map[j]=new int[n];
        }
        proc=0;
        for(int a=0;a<n;++a){
            for(int b=0;b<n;++b){
                cin>>map[a][b];
                if(map[a][b] == 1){
                    if(a!=0&&a!=(n-1)&&b!=0&&b!=(n-1)){
                        process.push_back({a,b});
                    }
                    ++proc;
                }
            }
        }

        nocon=process.size();
        con=proc-nocon;
        maxcon=con;

        findanswer(con,0);

        cout<<"#"<<i<<" "<<minlen<<"\n";


        for(int j=0;j<n;++j){
            delete[] map[j];
        }

    }
    return 0;
}