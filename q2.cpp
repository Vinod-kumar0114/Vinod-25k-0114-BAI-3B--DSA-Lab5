#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

class Stack{
public:
    Node* tp;
    Stack(){
        tp= NULL;
    }
    
    void push(int v){
        Node* nn= new Node;
        nn->data =v;
        nn->next= tp;
        tp= nn;
    }
    
    int pop(){
        if(tp==NULL) return -1;
        Node* t= tp;
        int val= t->data;
        tp= tp->next;
        delete t;
        return val;
    }
    
    bool is_empty(){
        return tp==NULL;
    }
};

void rev_stk(Stack& s, Stack& rev){
    while(!s.is_empty()){
        rev.push(s.pop());
    }
}

void sort_stk(Stack& s){
    Node* i= s.tp;
    while(i != NULL){
        Node* j= i->next;
        while(j!= NULL){
            if(i->data > j->data){
                int temp= i->data;
                i->data= j->data;
                j->data= temp;
            }
            j= j->next;
        }
        i= i->next;
    }
}

class CircularQ{
    int arr[100];
    int f, r, sz;
public:
    CircularQ(){
        f= -1;
        r =-1;
        sz= 100;
    }
    
    void enq(int v){
        if((r+1)%sz == f) return;
        if(f== -1){
            f= 0;
            r= 0;
        }
        else{
            r= (r+1)%sz;
        }
        arr[r]= v;
    }
    
    void display(){
        if(f== -1) return;
        cout<<"circular q: ";
        int i= f;
        while(true){
            cout<<arr[i]<<" ";
            if(i== r) break;
            i= (i+1)%sz;
        }
        cout<<endl;
    }
};

int main(){
    Stack s1, s2, s3;
    Stack b1, b2;
    int n1, n2, v;
    
    cout<<"enter size for stack 1: ";
    cin>>n1;
    for(int i=0; i<n1; i++){
        cout<<"val: ";
        cin>>v;
        s1.push(v);
    }
    
    cout<<"enter size for stack 2: ";
    cin>>n2;
    for(int i=0; i<n2; i++){
        cout<<"val: ";
        cin>>v;
        s2.push(v);
    }
    
    rev_stk(s1, b1);
    rev_stk(s2, b2);
    
    while(!b1.is_empty() || !b2.is_empty()){
        if(!b1.is_empty()){
            s3.push(b1.pop());
        }
        if(!b2.is_empty()){
            s3.push(b2.pop());
        }
    }
    
    Stack final_s3;
    rev_stk(s3, final_s3);
    
    cout<<"\nthird stack: ";
    Node* curr= final_s3.tp;
    while(curr!= NULL){
        cout<<curr->data<<" ";
        curr= curr->next;
    }
    cout<<endl;
    
    sort_stk(final_s3);
    
    CircularQ q;
    Stack temp_rev;
    rev_stk(final_s3, temp_rev);
    
    curr= temp_rev.tp;
    while(curr!= NULL){
        q.enq(curr->data);
        curr= curr->next;
    }
    
    q.display();
    
    return 0;
}