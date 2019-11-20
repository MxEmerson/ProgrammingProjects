#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>

struct Node
{
    char ch;
    int value;
    Node *left;
    Node *right;
    Node(){
        left=NULL;
        right=NULL;
        ch='0';
        value=0;
    }
    Node(char chr){
        left=NULL;
        right=NULL;
        if(chr>='0'&&chr<='9'){
            value=chr-48;
            ch='0';
        }
        else{
            ch=chr;
            value=0;
        }
    }
};
class Expression
{
public:
    Expression();
    Expression(std::string str);
    ~Expression();
    std::string getStr();
    void ReadExpr(std::string str);
    void WriteExpr();
    void DelExpr();
    void Assign(char var, int c);
    int Value();
    Expression operator+(Expression& R);
    Expression operator-(Expression& R);
    Expression operator*(Expression& R);
    Expression operator/(Expression& R);
    Expression Diff(char var);
    void MergeConst();

    void DelTree(Node *node);
    Node* ReadTree(std::string str, int &i);
    void WriteTree(Node *node,char last);

    void AssignTree(Node *node,char var, int c);
    void ValueTree(Node *node,int& i);
    void MergeTree(Node *node);

    int Oper(char ch);

private:
    Node *root;
    std::string instr;
};

#endif