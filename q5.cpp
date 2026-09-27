#include <iostream>
using namespace std;

class Node{
public:
    char data;
    Node* next;

    Node(char v):data(v), next(nullptr){}
};

class Stack{
    Node* tp;
    int c;
public:
    Stack(){
        tp= NULL;
        c= 0;
    }
    
    void push(char v){
        Node* newNode =new Node(v);
        newNode->next =tp;
        tp=newNode;
        c++;
    }
    
    char pop(){
        if(tp== NULL) return '\0';
        char v =tp->data;
        Node* t= tp;
        tp= tp->next;
        delete t;
        c--;
        return v;
    }
    
    char top(){
        if(tp== NULL) return '\0';
        return tp->data;
    }
    
    bool isEmpty(){
        return tp ==NULL;
    }
};

void addNum(char* arr, int& idx, int num){
    if(num== 0){
        arr[idx++]='0';
        return;
    }
    char temp[20];
    int i=0;
    while(num> 0){
        temp[i++]= (num%10) + '0';
        num/=10;
    }
    for(int j=i-1; j>=0; j--){
        arr[idx++]=temp[j];
    }
}

void buildInfx(int n, char* in){
    int x=0;
    for(int i=1; i<=n; i++){
        int t =3*i-2;
        addNum(in, x, t);
        if(i< n){
            in[x++]=' ';
            in[x++]='+';
            in[x++]=' ';
        }
    }
    in[x]='\0';
}

void buildRev(int n, char* in){
    int x=0;
    for(int i=n; i>=1; i--){
        int t =3*i-2;
        addNum(in, x, t);
        if(i> 1){
            in[x++]=' ';
            in[x++]='+';
            in[x++]=' ';
        }
    }
    in[x]='\0';
}

int len(char* s){
    int l =0;
    while(s[l]!='\0') l++;
    return l;
}

void revStr(char* s){
    int l= len(s);
    if(l>0 && s[l-1]==' '){
        s[l-1]='\0';
        l--;
    }
    for(int i=0; i<l/2; i++){
        char t= s[i];
        s[i]= s[l-1-i];
        s[l-1-i]= t;
    }
    
    int i=0;
    while(s[i]!='\0'){
        if(s[i]>='0' && s[i]<='9'){
            int st =i;
            while(s[i]>='0' && s[i]<='9') i++;
            for(int k=0; k<(i-st)/2; k++){
                char t = s[st+k];
                s[st+k] = s[i-1-k];
                s[i-1-k] = t;
            }
        }else{
            i++;
        }
    }
}

void toPost(char* in, char* post){
    Stack s;
    int i=0, j=0;
    while(in[i]!='\0'){
        if(in[i]==' '){ i++; continue; }
        if(in[i]>='0' && in[i]<='9'){
            while(in[i]>='0' && in[i]<='9'){
                post[j++]=in[i++];
            }
            post[j++]=' ';
            i--;
        }
        else if(in[i]=='+'){
            while(!s.isEmpty()){
                post[j++]=s.pop();
                post[j++]=' ';
            }
            s.push('+');
        }
        i++;
    }
    while(!s.isEmpty()){
        post[j++]=s.pop();
        post[j++]=' ';
    }
    post[j]='\0';
}

void toPre(int n, char* pre){
    char revIn[1000];
    buildRev(n, revIn);
    
    Stack s;
    int i=0, j=0;
    while(revIn[i]!='\0'){
        if(revIn[i]==' '){ i++; continue; }
        if(revIn[i]>='0' && revIn[i]<='9'){
            while(revIn[i]>='0' && revIn[i]<='9'){
                pre[j++]=revIn[i++];
            }
            pre[j++]=' ';
            i--;
        }
        else if(revIn[i]=='+'){
            s.push('+');
        }
        i++;
    }
    while(!s.isEmpty()){
        pre[j++]=s.pop();
        pre[j++]=' ';
    }
    pre[j]='\0';
    revStr(pre);
}

int main(){
    int n;
    cout<<"enter n: ";
    cin>>n;
    
    char infx[1000];
    buildInfx(n, infx);
    
    char post[1000];
    toPost(infx, post);
    
    char pre[1000];
    toPre(n, pre);
    
    cout<<"\nSeries: "<<infx<<endl;
    cout<<"Postfix: "<<post<<endl;
    cout<<"Prefix: "<<pre<<endl;
}