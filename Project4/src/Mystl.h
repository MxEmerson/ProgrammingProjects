#ifndef __MYSTL_H__
#define __MYSTL_H__

//#define DEBUG

#include "Graph.h"

class Stack
{
private:
    Vertex ver[30];
    int pos;
public:
    Stack();
    ~Stack();
    bool empty() const;
    bool pop();
    bool push(Vertex v);
    Vertex top() const;
};

#ifdef DEBUG
//-----------------

typedef struct QNode
{
    QNode(int _n, std::string _name, Path *_Fout){
        ver=new Vertex(_n,_name,_Fout);
        next=nullptr;
    }
    Vertex* ver;
    QNode* next;
}QNode;


class Queue
{
private:
    QNode* head;
public:
    Queue();
    ~Queue();
    bool empty() const;
    bool pop();
    bool push(Vertex v);
    Vertex* front() const;
    Vertex* back() const;
};

//-----------------
#endif  //DEBUG

#endif  //__MYSTL_H__