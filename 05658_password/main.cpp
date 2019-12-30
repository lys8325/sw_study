#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>
#include <deque>

using namespace std;

struct bst{
    unsigned data;
    struct bst* left;
    struct bst* right;
};

deque<int> Q1;
queue<int> Q2;
stack<int> S;

struct bst* root= NULL;

void add(int data){
    struct bst* p;
    struct bst* q;
    p=root;

    if(root== NULL){
        p=new(struct bst);
        p->data=data;
        p->left= NULL;
        p->right = NULL;
        root=p;
        //cout<<"1"<<endl;
    }
    else{
        while(p != NULL){
            //cout<<"2"<<endl;
            if(data>p->data){
                q=p;
                p=p->right;
            }
            else if(data == p->data){
                return;
            }
            else{
                q=p;
                p=p->left;
            }
        }
        p=new(struct bst);
        p->data=data;
        p->left= NULL;
        p->right = NULL;

        if(p->data > q->data){
            q->right=p;
        }
        else{
            q->left=p;
        }
    }
}
void makedata(int num){
    int temp;
    int data=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<num;j++){
            temp = Q1.front();
            Q1.pop_front();
            data += (temp << (num-j-1)*4);
        }
        Q2.push(data);
        data=0;

    }
    /*while (!Q2.empty()){
        temp=Q2.front();
        Q2.pop();
        cout<<temp<<endl;
    }*/
}

void answer(struct bst* p,int k,int &check,int &Answer){
    if (p== NULL){
        return;
    }
    answer(p->right,k,check,Answer);
    check++;
    if(check==k){
        Answer=p->data;
    }
    answer(p->left,k,check,Answer);
}

int main() {
    int temp;
    int t,n,k;
    int a,b,c,num;
    cin>>t;
    for(int i=0;i<t;i++) {
        int check=0;
        int Answer =0;
        cin>>n>>k;
        char number[n];
        num = n / 4;
        cin>>number;
        for (int l = 0; l < num; l++) {
            for (int j = 0; j<n; j++) {
                if (number[j] == 'A') {
                    a = 10;
                } else if (number[j] == 'B') {
                    a = 11;
                } else if (number[j] == 'C') {
                    a = 12;
                } else if (number[j] == 'D') {
                    a = 13;
                } else if (number[j] == 'E') {
                    a = 14;
                } else if (number[j] == 'F') {
                    a = 15;
                } else {
                    a = number[j] - '0';
                }
                Q1.push_back(a);
            }
            for (int m = 0; m < l; m++) {
                c = Q1.back();
                Q1.pop_back();
                Q1.push_front(c);
            }
            makedata(num);
        }
        while (!Q2.empty()){
            b=Q2.front();
            Q2.pop();
            add(b);
        }

        answer(root,k,check,Answer);
        //Answer = S.top();
        cout<<"#"<<i+1<<" "<<Answer<<endl;
        delete []root;
        root=NULL;

        /*while (!S.empty()){
            S.pop();
        }*/
        /*while (!Q1.empty()){
            Q1.pop_front();
        }*/
    }
    return 0;
}