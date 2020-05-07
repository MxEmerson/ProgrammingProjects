#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <string>
//邻接多重表边
typedef struct Path
{
    Path(int cos, int v1, int v2) : mark(false), cost(cos), vtx1(v1), vtx2(v2), path1(nullptr), path2(nullptr)
    {
        //对path1 path2初始化
    }
    bool mark;   //标记
    int cost;    //权值
    int vtx1;    //第一个顶点
    int vtx2;    //第二个顶点
    Path *path1; //下一条依附于vtx1的边
    Path *path2; //下一条依附于vtx2的边
} Path;

//邻接多重表节点
typedef struct Vertex
{
    Vertex() {}
    Vertex(int _n, std::string _name, Path *_Fout) : n(_n), name(_name), Fout(_Fout)
    {
    }
    int n;
    std::string name; //节点名称
    Path *Fout;       //依附于第一条边的指针
} Vertex;

//邻接表表节点
typedef struct LinkNode
{
    LinkNode(int _pos,int _c):pos(_pos),cost(_c)
    {
        next=nullptr;
    }
    int pos;
    int cost;
    LinkNode *next;
} LinkNode;

//邻接表顶点节点
typedef struct VexNode
{
    std::string name;
    LinkNode *first;
} VexNode;

//邻接表，存储生成树
class Tree
{
private:
    int num; //节点数量
    VexNode list[30];
    bool visit[30];
public:
    Tree();
    ~Tree();
    void addVex(std::string name);     //添加顶点
    void addPath(int m, int n, int c); //添加m到n的通路
    void print();                      //输出树形
    void revprint(int i,int level);
};

//邻接多重表
class Graph
{
private:
    Vertex ver[30];      //存储顶点
    int vexnum, pathnum; //顶点数和边数
public:
    Graph();
    ~Graph();
    void addVex(std::string name);     //添加顶点
    void addPath(int m, int n, int c); //添加边
    void dfs(Tree &T);                 //深度优先遍历，非递归
    void bfs(Tree &T);                 //广度优先遍历
    void resetMark();                  //重置访问标记
};

#endif