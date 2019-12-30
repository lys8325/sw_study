#include <iostream>
#include <vector>

using namespace std;

int map[2001][2001] = {-1}; // 0~999 음수, 1000=0, 1001~2000 양수
bool crash[1000] = {false}; // 충돌했는지
bool turn[1000] = {false}; // 이번턴에 움직인 원자인지, false는 곧 움직여 충돌하지 않음을 뜻함.
int dy[4] = {1,-1,0,0};
int dx[4] = {0,0,-1,1};
int cont[4] = {1,0,3,2}; // 마주 보는  방향의 인덱스
int T,N,E,R;
// T = 테스트케이스 수, N = 원자수, E = 총 방출한 에너지, R = 살아있는 원자수

struct atom{
    int x;
    int y;
    int direct;
    int energy;
    bool live;
};

vector<atom> list;

void init(){
    for(int i=0;i<2001;++i){
        for(int j=0;j<2001;++j){
            map[i][j]=-1;
        }
    }

    for(int i=0;i<N;++i){
        crash[i]=false;
    }

    while(!list.empty()){
        list.pop_back();
    }
}

void calc_crash(){
    int xx,yy;
    for(int i=0;i<N;++i){
        turn[i] = false; // 턴 정보 초기화
        if(crash[i]){ // 충돌했다면
            xx=list[i].x;
            yy=list[i].y;
            E += list[i].energy; // 방출한 총 에너지 증가
            map[yy][xx]=-1;
            list[i].live = false; // 사라짐
            crash[i] = false;
            --R; // 살아있는 원자수 감소
        }
    }
}

void progress(){
    int px,py,pd,tm;
    for(int i=0;i<N;++i){
        if(list[i].live){
            px = list[i].x;
            py = list[i].y;
            pd = list[i].direct;
            list[i].x = px + dx[pd];
            list[i].y = py + dy[pd];
            if(i != map[py][px]){
                //지우려고 하는 원자 번호와 맵상 번호가 다르다는 것은
                //원자번호가 더 빠른 원자가 현재 조사중인 원자의 위치에 들어온 것이므로
                //충돌이 아니고 유효하다. 따라서 지우면 안된다.
            }
            else{
                map[py][px] = -1;
            }

            if(list[i].x < 0 || list[i].x > 2000 || list[i].y < 0 || list[i].y > 2000){
                // map에서 벗어났다면, 영원히 만나지 못하기 때문에 더 이상 신경쓸 필요가 없지만 에너지는 방출x
                list[i].live = false;
                --R;
            }
            else{ // map상에 있다면
                tm = map[list[i].y][list[i].x];
                if(tm !=-1 && !turn[tm] && (cont[pd] == list[tm].direct)){
                    //turn이 거짓이라 곧 움직이지만, 방향이 마주보는 방향이라 0.5초 후 충돌일 때
                    crash[tm] = true;
                    crash[i] = true;
                    calc_crash();//0.5초 충돌이 더 빠르기 때문에 1초 충돌을 위해 먼저 계산해 정리해준다.
                }
                else if(tm != -1 && turn[tm]){ // map에 다른 원자가 있었고, 이미 움직여 도착한 원자라면 충돌
                    // turn이 false라면 곧 움직이기 떄문에 충돌x else 로 이동!
                    crash[tm] = true;
                    crash[i] = true;
                }
                else{ // 충돌없다
                    // 기존에 번호가 있었지만 곧 움직일 원자여서 충돌로 여기지 않는 경우라면
                    // 맵상에서 그 번호는 사라지지만, 반복문에서 후에 처리되기 때문에
                    // 나중에 이동한 곳에 마킹된다.
                    map[list[i].y][list[i].x] = i;
                }
                turn[i] = true;
            }
        }
    }
    calc_crash();
}


int main() {
    int tx,ty,td,te;
    cin>>T;
    for(int t=1;t<=T;++t){
        cin>>N;
        E = 0;
        R = N;
        init();
        for(int i=0;i<N;++i){
            cin>>tx>>ty>>td>>te;
            list.push_back(atom{tx+1000,ty+1000,td,te, true});
            map[ty+1000][tx+1000] = i;
        }
        while(R != 0){
            progress();
        }
        cout<<"#"<<t<<" "<<E<<endl;
    }

    return 0;
}