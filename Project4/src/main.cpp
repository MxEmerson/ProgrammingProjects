#include "Graph.h"
#include <iostream>
using namespace std;

int main()
{
    Graph G;
    Tree T1,T2;
    int m,n,c;
    string name;
    cout<<"输入点\n";
    for(int i=0;i<10;i++){
        cin>>name;
        G.addVex(name);
        T1.addVex(name);
        T2.addVex(name);
    }
    cout<<"输入边\n";
    for(int i=0;i<10;i++){
        cin>>m>>n>>c;
        G.addPath(m,n,c);
    }
    G.dfs(T1);
    G.bfs(T2);
    T1.print();
    T2.print();
    return 0;
}