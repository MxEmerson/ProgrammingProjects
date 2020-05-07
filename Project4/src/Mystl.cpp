#include "Mystl.h"

//#define DEBUG

Stack::Stack()
{
    pos = -1;
}

Stack::~Stack()
{
}

bool Stack::empty() const
{
    return pos == -1 ? true : false;
}

bool Stack::pop()
{
    if (pos < 0)
        return false;
    pos--;
    return true;
}

bool Stack::push(Vertex v)
{
    if (pos > 29)
        return false;
    pos++;
    ver[pos] = v;
    return true;
}

Vertex Stack::top() const
{
    return ver[pos];
}

#ifdef DEBUG
//-----------------

Queue::Queue()
{
    head = nullptr;
}

Queue::~Queue()
{
}

bool Queue::empty() const
{
    if (head == nullptr)
        return true;
    return false;
}

bool Queue::pop(){
    QNode* newhead=new QNode(head->ver->n,head->ver->name,head->ver->Fout);
    newhead->next=head;
    head=newhead;
}

bool Queue::push(Vertex v){
    QNode*node=head;
    while (node!=nullptr)
    {
        node=node->next;
    }
    node=new QNode(v.n,v.name,v.Fout);
}

Vertex* Queue::front() const{
    return head->ver;
}

Vertex* Queue::back() const{
    QNode*node=head;
    while (node->next!=nullptr)
    {
        node=node->next;
    }
    return node->ver;
}

//-----------------
#endif  //DEBUG