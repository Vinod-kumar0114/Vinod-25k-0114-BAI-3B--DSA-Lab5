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
    
    void stats(){
        if(tp== NULL){
            cout<<"empty stack\n";
            return;
        }
        
        int mx =tp->data;
        int mn= tp->data;
        
        Node* t= tp;
        while(t!=NULL){
            if(t->data >mx){
                mx =t->data;
            }
            if(t->data <mn){
                mn= t->data;
            }
            t= t->next;
        }
        
        cout<<"max is "<<mx<<endl;
        cout<<"min is "<<mn<<endl;
        
        t =tp;
        if(c%2 ==1){
            int m= c/2;
            for(int i=0; i<m; i++){
                t=t->next;
            }
            cout<<"mid is "<<t->data<<endl;
        }else{
            int m = (c/2)-1;
            for(int i=0; i<m; i++){
                t= t->next;
            }
            int m2 = t->data;
            int m1 =t->next->data;
            cout<<"mid elements: "<<m1<<" and "<<m2<<endl;
        }
    }
};

int main(){
    Stack s;
    int n;    
    cout<<"total elements: ";
    cin>>n;
    
    for(int i=0; i<n; i++){
        int v;
        cout<<"enter val: ";
        cin>>v;
        s.push(v);
    }
    
    if(n> 0){
        s.stats();
    }
}