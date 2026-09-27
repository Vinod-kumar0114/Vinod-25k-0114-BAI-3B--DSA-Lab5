#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;

    Node(int v):data(v), next(nullptr){}
};

class Stack{
    Node* tp;
    int c;
public:
    Stack(){
        tp= NULL;
        c= 0;
    }
    
    void push(int v){
        Node* newNode =new Node(v);
        newNode->data=v;
        newNode->next =tp;
        tp=newNode;
        c++;
    }
    
    int pop(){
        if(tp== NULL){
            return -1;
        }
        int v =tp->data;
        Node* t= tp;
        tp= tp->next;
        delete t;
        c--;
        return v;
    }
    
    int top(){
        if(tp== NULL) return -1;
        return tp->data;
    }
    
    bool isEmpty(){
        return tp ==NULL;
    }
};

bool chkCnd(char* c, int x){
    int i=0;
    while(c[i]==' '||c[i]=='x') i++;
    char o1=c[i++];
    char o2=' ';
    if(c[i]=='=' || c[i]=='>' || c[i]=='<') o2=c[i++];
    while(c[i]==' ') i++;
    int v=0, s=1;
    if(c[i]=='-'){ s=-1; i++; }
    while(c[i]>='0' && c[i]<='9'){ v=v*10+(c[i]-'0'); i++; }
    v*=s;
    
    if(o1=='>' && o2=='=') return x>=v;
    if(o1=='<' && o2=='=') return x<=v;
    if(o1=='>') return x>v;
    if(o1=='<') return x<v;
    if(o1=='=' && o2=='=') return x==v;
    return false;
}

int pr(char c){
    if(c=='^') return 3;
    if(c=='*' || c=='/') return 2;
    if(c=='+' || c=='-') return 1;
    return -1;
}

void toPost(char* in, char* post){
    Stack s;
    int i=0, j=0;
    while(in[i]!='\0'){
        if(in[i]==' ') { i++; continue; }
        if((in[i]>='0'&&in[i]<='9') || in[i]=='x'){
            while((in[i]>='0'&&in[i]<='9') || in[i]=='x'){
                post[j++]=in[i++];
            }
            post[j++]=' ';
            i--; 
        }
        else if(in[i]=='('){
            s.push('(');
        }
        else if(in[i]==')'){
            while(!s.isEmpty() && s.top()!='('){
                post[j++]=(char)s.pop();
                post[j++]=' ';
            }
            if(!s.isEmpty()) s.pop();
        }
        else{
            while(!s.isEmpty() && pr(in[i])<=pr((char)s.top())){
                post[j++]=(char)s.pop();
                post[j++]=' ';
            }
            s.push(in[i]);
        }
        i++;
    }
    while(!s.isEmpty()){
        post[j++]=(char)s.pop();
        post[j++]=' ';
    }
    post[j]='\0';
}

int pwr(int b, int e){
    int r=1;
    for(int i=0;i<e;i++) r*=b;
    return r;
}

int evl(char* post, int x){
    Stack s;
    int i=0;
    while(post[i]!='\0'){
        if(post[i]==' ') { i++; continue; }
        if(post[i]>='0' && post[i]<='9'){
            int v=0;
            while(post[i]>='0' && post[i]<='9'){
                v = v*10 + (post[i]-'0');
                i++;
            }
            s.push(v);
            continue;
        }
        else if(post[i]=='x'){
            s.push(x);
            i++;
            continue;
        }
        else{
            int b = s.pop();
            int a = s.pop();
            if(post[i]=='+') s.push(a+b);
            else if(post[i]=='-') s.push(a-b);
            else if(post[i]=='*') s.push(a*b);
            else if(post[i]=='/') s.push(a/b);
            else if(post[i]=='^') s.push(pwr(a,b));
            i++;
        }
    }
    return s.pop();
}

int main(){
    char e1[100], c1[50];
    char e2[100], c2[50];
    int x;
    
    cout<<"Enter Expression 1: ";
    cin.getline(e1, 100);
    cout<<"Enter Condition 1: ";
    cin.getline(c1, 50);
    
    cout<<"Enter Expression 2: ";
    cin.getline(e2, 100);
    cout<<"Enter Condition 2: ";
    cin.getline(c2, 50);
    
    cout<<"Enter x: ";
    cin>>x;
    
    char* sel_e = e1;
    char* sel_c = c1;
    
    if(!chkCnd(c1, x)){
        sel_e = e2;
        sel_c = c2;
    }
    
    char post[100];
    toPost(sel_e, post);
    int res =evl(post, x);
    
    cout<<"\nThe program selects:\n";
    cout<<"Condition: "<<sel_c<<endl;
    cout<<"Expression: "<<sel_e<<endl;
    cout<<"Postfix: "<<post<<endl;
    cout<<"Calculated Value: "<<res<<endl;
    
    return 0;
}