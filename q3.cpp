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
        if(tp== NULL){
            return '\0';
        }
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

int prec(char c){
    if(c=='^') return 3;
    if(c=='*' || c=='/') return 2;
    if(c=='+' || c=='-') return 1;
    return -1;
}

int len(const char* s){
    int l=0;
    while(s[l]!='\0'){
        l++;
    }
    return l;
}

void rev(char* s, int l){
    for(int i=0; i<l/2; i++){
        char t= s[i];
        s[i]= s[l-i-1];
        s[l-i-1] =t;
    }
}

void inToPost(const char* infx, char* post){
    Stack s;
    int i=0;
    int j =0;
    while(infx[i]!='\0'){
        char c= infx[i];
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9')){
            post[j++]=c;
        }
        else if(c=='(' || c=='['){
            s.push('(');
        }
        else if(c==')' || c==']'){
            while(!s.isEmpty() && s.top()!='('){
                post[j++]= s.pop();
            }
            if(!s.isEmpty()) s.pop();
        }
        else{
            while(!s.isEmpty() && prec(c)<=prec(s.top())){
                post[j++] =s.pop();
            }
            s.push(c);
        }
        i++;
    }
    while(!s.isEmpty()){
        post[j++]=s.pop();
    }
    post[j]='\0';
}

void inToPre(const char* infx, char* pre){
    int l= len(infx);
    char revIn[100];
    for(int i=0; i<l; i++){
        revIn[i]= infx[l-i-1];
        if(revIn[i]=='(') revIn[i]=')';
        else if(revIn[i]==')') revIn[i]='(';
        else if(revIn[i]=='[') revIn[i]=']';
        else if(revIn[i]==']') revIn[i]='[';
    }
    revIn[l]='\0';
    
    Stack s;
    int i=0, j=0;
    while(revIn[i]!='\0'){
        char c= revIn[i];
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9')){
            pre[j++]=c;
        }
        else if(c=='('){
            s.push('(');
        }
        else if(c==')'){
            while(!s.isEmpty() && s.top()!='('){
                pre[j++]= s.pop();
            }
            if(!s.isEmpty()) s.pop();
        }
        else{
            while(!s.isEmpty() && prec(c)<prec(s.top())){
                pre[j++] =s.pop();
            }
            s.push(c);
        }
        i++;
    }
    while(!s.isEmpty()){
        pre[j++]=s.pop();
    }
    pre[j]='\0';
    
    rev(pre, j);
}

int main(){
    const char* e1 = "p*r*((1-c)/(1+c))";
    const char* e2 = "1-c^2";
    const char* e3 = "(1/2)*(a-b)";
    
    char post1[100], pre1[100];
    char post2[100], pre2[100];
    char post3[100], pre3[100];
    
    inToPost(e1, post1);
    inToPre(e1, pre1);
    
    inToPost(e2, post2);
    inToPre(e2, pre2);
    
    inToPost(e3, post3);
    inToPre(e3, pre3);
    
    cout<<"eq 1 rhs postfix: "<<post1<<endl;
    cout<<"eq 1 rhs prefix: "<<pre1<<endl<<endl;
    
    cout<<"eq 2 rhs postfix: "<<post2<<endl;
    cout<<"eq 2 rhs prefix: "<<pre2<<endl<<endl;
    
    cout<<"eq 3 rhs postfix: "<<post3<<endl;
    cout<<"eq 3 rhs prefix: "<<pre3<<endl;
    
    return 0;
}