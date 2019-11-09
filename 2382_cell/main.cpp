#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 100
using namespace std;

int cell[MAX_N][MAX_N]={0};
int dy[]={0,-1,1,0,0};
int dx[]={0,0,0,-1,1};

struct mo{
    char live;
    int y;
    int x;
    int entity;
    int direct;
};

int n,t,m,k,sum,num;
vector<mo> info;
priority_queue<pair<int,int>> calc;
void init_cell(){
    for(int a=1;a<n-1;++a){
        for(int b=1;b<n-1;++b){
            cell[a][b]=0;
        }
    }
    for(int c=0;c<n;++c){
        cell[0][c]=-1;
        cell[n-1][c]=-1;
    }
    for(int c=1;c<n-1;++c){
        cell[c][0]=-1;
        cell[c][n-1]=-1;
    }
}

void absorb(int tty, int ttx){
    int temp=0;
    int winner;
    for(int w=1;w<num;++w) {
        if (info[w].live == 1) {
            if (info[w].y==tty && info[w].x==ttx) {
                calc.push({info[w].entity,w});
                info[w].live=0;
                temp += info[w].entity;
            }
        }
    }
    winner=calc.top().second;
    info[winner].live=1;
    info[winner].entity=temp;
    cell[tty][ttx]=winner;

    while(!calc.empty()){
        calc.pop();
    }
}

void progress() {
    int ty, tx;
    for(int q=1;q<num;++q) {
        if (info[q].live == 1) {
            ty = info[q].y;
            tx = info[q].x;
            if (cell[ty][tx] == -1) {

            }
            else {
                cell[ty][tx] = 0;
            }
        }
    }
    for (int p = 1; p < num; ++p) {
        if (info[p].live == 1) {
            ty = info[p].y;
            tx = info[p].x;
            ty += dy[info[p].direct];
            tx += dx[info[p].direct];
            info[p].y = ty;
            info[p].x = tx;
            if (cell[ty][tx] == -1) {
                info[p].entity /= 2;
                if(info[p].entity==0){
                }
                if (info[p].direct == 1) {
                    info[p].direct = 2;
                } else if (info[p].direct == 2) {
                    info[p].direct = 1;
                } else if (info[p].direct == 3) {
                    info[p].direct = 4;
                } else {
                    info[p].direct = 3;
                }
            }
            else if(cell[ty][tx] == 0) {
                cell[ty][tx] = p;
            }
            else{
                    cell[ty][tx] = -2;
            }
        }
        else {

        }
    }
    for(int a=1;a<n-1;++a){
        for(int b=1;b<n-1;++b){
            if(cell[a][b]==-2){
                absorb(a,b);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int xx,yy,ee,dd;
    cin>>t;
    for(int test=1;test<=t;++test){
        cin>>n>>m>>k;
        init_cell();
        info.push_back(mo{0,0,0,0,0});
        for(int i=1;i<=k;++i){
            cin>>yy>>xx>>ee>>dd;
            cell[yy][xx]=i;
            info.push_back(mo{1,yy,xx,ee,dd});
        }
        /*for(int a=1;a<n-1;++a){
            for(int b=1;b<n-1;++b){
                cout<<cell[a][b]<<" ";
                if(b==n-2){
                    cout<<"\n";
                }
            }
        }*/
        num = info.size();
        for(int j=0;j<m;++j){
            progress();
        }
        sum=0;
        for(int i=1;i<=k;++i){
            if(info[i].live==1){
                sum += info[i].entity;
            }
        }
        cout<<"#"<<test<<" "<<sum<<"\n";
        info.clear();
    }
    return 0;
}