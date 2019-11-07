#include"client.h"
using namespace std;

void Printmenu() {
	std::cout << "请输入表达式，输入0返回:" << endl;
}

bool Examine(std::string str) {
	return true;
}

int Pr(char ch) {
	switch (ch) {
	case '*':return 3;
	case '/':return 3;
	case '+':return 2;
	case '-':return 2;
	case '^':return 4;
	case '(':return 5;
	case ')':return 1;
	}
	return 0;
}

int Operate(int left, int right, char op) {
	int res = 0;
	switch (op) {
	case '+':
		res = left + right;
		break;
	case '-':
		res = left - right;
		break;
	case '*':
		res = left * right;
		break;
	case '/':
		res = left / right;
		break;
	case '^':
		res = pow(left, right);
		break;
	default:
		break;
	}
	return res;

}

void Operation(string str) {
	//先转为后缀表达式，更方便计算
	stack<string> s1;		//运算符栈
	stack<string> s2;		//中间结果栈
	string tmpch;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			tmpch = "";
			for (int j = i; str[j] >= '0' && str[j] <= '9'; j++, i++) {
				tmpch += str[i];
			}
			i--;
			s2.push(tmpch);
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
			while (true) {
				tmpch = "";
				if (s1.empty() || s1.top() == "(") {
					tmpch += str[i];
					s1.push(tmpch);
					break;
				}
				else if (Pr(str[i]) > Pr(s1.top()[0])) {
					tmpch += str[i];
					s1.push(tmpch);
					break;
				}
				else {
					tmpch = s1.top();
					s1.pop();
					s2.push(tmpch);
				}
			}
		}
		else {
			if (str[i] == '(') {
				s1.push("(");
			}
			else {
				tmpch = "";
				while (s1.top() != "(") {
					tmpch = s1.top();
					s1.pop();
					s2.push(tmpch);
				}
				s1.pop();
			}
		}
	}
	while (!s1.empty()) {
		tmpch = s1.top();
		s2.push(tmpch);
		s1.pop();
	}
	while (!s2.empty()) {
		tmpch = s2.top();
		s1.push(tmpch);
		s2.pop();
	}
	queue<string> mstr;
	while (!s1.empty()) {
		mstr.push(s1.top());
		s1.pop();
	}
	//再对后缀表达式进行求值
	stack<string> st;//操作数栈
	int size = mstr.size();
	for (int i = 0; i < size; i++) {
		if (mstr.front()[0] >= '0' && mstr.front()[0] <= '9') {
			st.push(mstr.front());
			mstr.pop();
		}
		else {
			int l = stoi(st.top());
			st.pop();
			int r = stoi(st.top());
			st.pop();
			st.push(to_string(Operate(r, l, mstr.front()[0])));
			mstr.pop();
		}
	}
	std::cout << "计算结果：" << st.top() << endl;
	std::cout << "请按任意键继续。。。" << endl;
	std::cin.ignore();
	getchar();
}