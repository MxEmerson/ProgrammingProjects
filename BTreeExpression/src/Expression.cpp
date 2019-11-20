#include "Expression.h"
#include <iostream>
#include <string>
#include <cmath>

Expression::Expression()
{
    root = NULL;
}

Expression::Expression(std::string str){
    ReadExpr(str);
}

Expression::~Expression()
{
    //
}

std::string Expression::getStr()
{
    return instr;
}

void Expression::ReadExpr(std::string str)
{
    int i = 0;
    root = ReadTree(str, i);
}

void Expression::WriteExpr()
{
    instr="";
    if(root->ch=='0'){
        instr+=std::to_string(root->value);
        return;
    }
    WriteTree(root, '+');
}

void Expression::DelExpr()
{
    Node *node = root;
    DelTree(node);
}

void Expression::Assign(char var, int c)
{
    AssignTree(root, var, c);
}

int Expression::Value()
{
    int i = 0;
//    ValueTree(root, i);
    //
    return i;
}

Expression Expression::operator+(Expression& R)
{
    Expression NewEx;
    NewEx.root = new Node;
    NewEx.root->left = this->root;
    NewEx.root->right = R.root;
    NewEx.root->ch = '+';
    return NewEx;
}

Expression Expression::operator-(Expression& R)
{
    Expression NewEx;
    NewEx.root = new Node;
    NewEx.root->left = this->root;
    NewEx.root->right = R.root;
    NewEx.root->ch = '-';
    return NewEx;
}

Expression Expression::operator*(Expression& R)
{
    Expression NewEx;
    NewEx.root = new Node;
    NewEx.root->left = this->root;
    NewEx.root->right = R.root;
    NewEx.root->ch = '*';
    return NewEx;
}

Expression Expression::operator/(Expression& R)
{
    Expression NewEx;
    NewEx.root = new Node;
    NewEx.root->left = this->root;
    NewEx.root->right = R.root;
    NewEx.root->ch = '/';
    return NewEx;
}

void Expression::MergeConst()
{
    MergeTree(root);
}

void Expression::DelTree(Node *node)
{
    if (node == NULL)
        return;
    DelTree(node->left);
    DelTree(node->right);
    delete node;
}

Node *Expression::ReadTree(std::string str, int &i)
{
    Node *newnode = NULL;
    if (i >= str.size())
        return newnode;
    newnode = new Node(str[i]);
    i++;
    if (!((str[i - 1] >= '0' && str[i - 1] <= '9') || (str[i - 1] >= 'a' && str[i - 1] <= 'z')))
    {
        newnode->left = ReadTree(str, i);
        newnode->right = ReadTree(str, i);
    }
    return newnode;
}

void Expression::WriteTree(Node *node, char last)
{
    if (node == NULL)
        return;
    if (Oper(node->ch) < Oper(last))
    {
        instr += '(';
    }
    WriteTree(node->left, node->ch);
    if (node->ch == '0')
    {
        instr += std::to_string(node->value);
    }
    else
    {
        instr += node->ch;
    }
    WriteTree(node->right, node->ch);
    if (Oper(node->ch) < Oper(last))
    {
        instr += ')';
    }
}

void Expression::AssignTree(Node *node, char var, int c)
{
    if (node == NULL)
        return;
    AssignTree(node->left, var, c);
    AssignTree(node->right, var, c);
    if (node->ch == var)
    {
        node->ch = '0';
        node->value = c;
    }
}

void Expression::ValueTree(Node *node, int &i)
{
    if (node == NULL)
    {
        return;
    }
    ValueTree(node->left, i);
    ValueTree(node->right, i);
    switch (node->ch)
    {
    case '+':
        node->ch = '0';
        node->value = node->left->value + node->right->value;
        break;
    case '-':
        node->ch = '0';
        node->value = node->left->value - node->right->value;
        break;
    case '*':
        node->ch = '0';
        node->value = node->left->value * node->right->value;
        break;
    case '/':
        node->ch = '0';
        node->value = node->left->value / node->right->value;
        break;
    case '^':
        node->ch = '0';
        node->value = pow(node->left->value, node->right->value);
        break;
    default:
        break;
    }
    return;
}

void Expression::MergeTree(Node *node)
{
    if (node == NULL)
        return;
    MergeTree(node->left);
    MergeTree(node->right);
    if (node->left!=NULL&&Oper(node->left->ch) == 5 && Oper(node->right->ch) == 5)
    {
        switch (node->ch)
        {
        case '+':
            node->ch = '0';
            node->value = node->left->value + node->right->value;
            break;
        case '-':
            node->ch = '0';
            node->value = node->left->value - node->right->value;
            break;
        case '*':
            node->ch = '0';
            node->value = node->left->value * node->right->value;
            break;
        case '/':
            node->ch = '0';
            node->value = node->left->value / node->right->value;
            break;
        case '^':
            node->ch = '0';
            node->value = pow(node->left->value, node->right->value);
            break;
        default:
            break;
        }
        delete node->left;
        delete node->right;
    }
}

int Expression::Oper(char ch)
{
    switch (ch)
    {
    case '*':
        return 3;
    case '/':
        return 3;
    case '+':
        return 2;
    case '-':
        return 2;
    case '^':
        return 4;
    }
    return 5;
}