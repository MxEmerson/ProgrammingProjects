#include "Graph.h"
#include "Mystl.h"
#include <iostream>
#include <queue>
#include <string>
using namespace std;

Graph::Graph()
{
    vexnum = 0;
    pathnum = 0;
}

Graph::~Graph()
{
}

void Graph::addVex(std::string name)
{
    if (vexnum >= 30)
    {
        cout << "Failed to add vex.\n";
        return;
    }
    ver[vexnum].name = name;
    ver[vexnum].Fout = nullptr;
    ver[vexnum].n = vexnum;
    if (vexnum < 30)
        vexnum++;
}

void Graph::addPath(int m, int n, int c)
{
    Path *newPath = new Path(c, m, n);
    Path *tmp;

    tmp = ver[m].Fout;
    ver[m].Fout = newPath;
    newPath->path1 = tmp;

    tmp = ver[n].Fout;
    ver[n].Fout = newPath;
    newPath->path2 = tmp;
}

void Graph::dfs(Tree &T)
{
    bool visit[vexnum] = {false};
    int lastlevel;
    Stack st;
    st.push(ver[0]);
    while (!st.empty())
    {
        if (!visit[st.top().n])
        {
            visit[st.top().n] = true;
            cout << st.top().name << "->";
        }
        Path *node = st.top().Fout;
        int tmp = st.top().n;
        while (node != nullptr)
        {
            if (node->vtx1 == tmp && !visit[node->vtx2])
            {
                st.push(ver[node->vtx2]);
                T.addPath(node->vtx1,node->vtx2,node->cost);
                node = node->path1;
            }
            else if (node->vtx2 == tmp && !visit[node->vtx1])
            {
                st.push(ver[node->vtx1]);
                T.addPath(node->vtx2,node->vtx1,node->cost);
                node = node->path2;
            }
            else
            {
                break;
            }
        }
        if (visit[st.top().n])
        {
            Path *node = st.top().Fout;
            int tmp = st.top().n;
            bool flag = false;
            while (!flag && node != nullptr)
            {
                if (node->vtx1 == tmp)
                {
                    if (!visit[node->vtx2])
                    {
                        flag = true;
                        break;
                    }
                    node = node->path1;
                }
                else if (node->vtx2 == tmp)
                {
                    if (!visit[node->vtx1])
                    {
                        flag = true;
                        break;
                    }
                    node = node->path2;
                }
            }
            if (!flag)
                st.pop();
        }
    }
    cout << endl;
}

void Graph::bfs(Tree &T)
{
    bool visit[vexnum] = {false};
    queue<Vertex> q;
    q.push(ver[0]);
    while (!q.empty())
    {
        if (!visit[q.front().n])
        {
            visit[q.front().n] = true;
            cout << q.front().name << "->";
        }
        Path *node = q.front().Fout;
        int tmp = q.front().n;
        q.pop();
        while (node != nullptr)
        {
            if (node->vtx1 == tmp && !visit[node->vtx2])
            {
                q.push(ver[node->vtx2]);
                T.addPath(node->vtx1,node->vtx2,node->cost);
                node = node->path1;
            }
            else if (node->vtx2 == tmp && !visit[node->vtx1])
            {
                q.push(ver[node->vtx1]);
                T.addPath(node->vtx2,node->vtx1,node->cost);
                node = node->path2;
            }
            else
            {
                break;
            }
        }
    }
    cout << endl;
}

void Graph::resetMark()
{
    /*for (auto iter : ver)
    {
        iter.Fout->mark = false;
    }*/
}

Tree::Tree()
{
    num = 0;
}

Tree::~Tree()
{
}

void Tree::addVex(string name)
{
    if (num >= 30)
    {
        cout << "Failed to add vex.\n";
        return;
    }
    list[num].name = name;
    list[num].first = nullptr;
    if (num < 30)
        num++;
}

void Tree::addPath(int m, int n, int c)
{
    if(list[m].first==nullptr){
        list[m].first=new LinkNode(n, c);
        return;
    }
    LinkNode *node = list[m].first;
    while (node->next != nullptr)
    {
        node = node->next;
    }
    node->next = new LinkNode(n, c);
}

void Tree::print()
{
    string str;
    revprint(0, 0);
}

void Tree::revprint(int pos, int level)
{
    string str;
    for (int j = 0; j < level; j++)
    {
        str += "  ";
    }
    str += "├─";
    if (!visit[pos]){
        cout << str << list[pos].name << endl;
        visit[pos]=true;
    }
    LinkNode *node = list[pos].first;
    while (node != nullptr)
    {
        revprint(node->pos, level + 1);
        node = node->next;
    }
    //
}