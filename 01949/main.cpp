#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int dy[4] = {-1, 1, 0 , 0};
int dx[4] = {0, 0, 1, -1};
int mount[8][8];
bool visit[8][8];

int t, n, k, ans;

void dfs(int y, int x, bool useK, int curHeight, int curLength){
    if(ans < curLength){
        ans = curLength;
    }

    int nextY, nextX;
    for(int i=0;i<4;++i){
        nextY = y + dy[i];
        nextX = x + dx[i];

        if(nextY>=0 && nextY<n && nextX>=0 && nextX<n && !visit[nextY][nextX]){
            if(useK){
                if(mount[nextY][nextX] < curHeight){
                    visit[nextY][nextX] = true;
                    dfs(nextY, nextX, true, mount[nextY][nextX], curLength+1);
                    visit[nextY][nextX] = false;
                }
            }else{
                if(mount[nextY][nextX] < curHeight){
                    visit[nextY][nextX] = true;
                    dfs(nextY, nextX, false, mount[nextY][nextX], curLength+1);
                    visit[nextY][nextX] = false;
                }

                for(int j=1;j<=k;++j){
                    if(mount[nextY][nextX]-j < curHeight){
                        visit[nextY][nextX] = true;
                        dfs(nextY, nextX, true, mount[nextY][nextX]-j, curLength+1);
                        visit[nextY][nextX] = false;
                    }
                }
            }
        }
    }
}

int main() {
    cin>>t;
    for(int i=1;i<=t;++i){
        ans = 1;
        int maxHeight = -1;

        memset(visit, 0, 64);
        cin>>n>>k;
        for(int p=0;p<n;++p){
            for(int q=0;q<n;++q){
                cin>>mount[p][q];
                maxHeight = max(maxHeight, mount[p][q]);
            }
        }

        for(int p=0;p<n;++p){
            for(int q=0;q<n;++q){
                if(mount[p][q] == maxHeight){
                    visit[p][q] = true;
                    dfs(p, q, false, mount[p][q], 1);
                    visit[p][q] = false;
                    for(int j=1;j<=k;++j){
                        //memset(visit, -1, 64);
                        visit[p][q] = true;
                        dfs(p, q, true, mount[p][q]-j, 1);
                        visit[p][q] = false;
                    }
                }
            }
        }

        cout<<"#"<<i<<" "<<ans<<"\n";
    }
    return 0;
}
