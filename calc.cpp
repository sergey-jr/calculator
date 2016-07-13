#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

template <class T>
class stack
{
	struct node
	{
		T info;
		node *next;
		node(T val):info(val),next(NULL){}
	};
	node *head, *tail;
public:
	stack():head(NULL),tail(NULL){}
	void push(T info)
	{
		node * tmp = new node(info);
		if (head == NULL)
		{
			tail = head = tmp;
		}
		else if (head == tail)
		{
			tmp->next = tail;
			head = tmp;
		}
		else
		{
			tmp->next = head;
			head = tmp;
		}
	}
	T get_next()
	{
		if(head!=tail)
		return head->next->info;
		else return head->info;
	}
	T pop()
	{
		node *tmp = head;
		head = head->next;
		return tmp->info;
	}
	bool empty()
	{
		return head == NULL;
	}
	T peack() {
		return head->info;
	}
};
int GetPriority(char val)
{
	switch (val)
	{
	case '(':
	case ')': return 0; break;
	case '+':
	case '-': return 1; break;
	case '*':
	case '/': return 2; break;
	case '^': return 3; break;
	default: return 4; break;
	}
}
int conv(char c) {
	return c - '0';
}
bool InStandart(char c)
{
	string standart = "+-*/()^";
	for(auto i:standart)
		if (c == i)
		{
			return true;
		}
	return false;
}
double res(char eq, double op1, double op2)
{
	switch(eq)
	{
	case '+':return (op1 + op2); break;
	case '-':return (op1 - op2); break;
	case '/':if (op2) return (op1 / op2); else { cout << "div by zero\n"; system("pause"); exit(-1); } break;
	case '*':return(op1*op2); break;
	case '^':return pow(op1, op2);
	default: exit(-1);
		break;
	}
}
void parse_operands(string line, stack<double> &operands, stack<char> &operators)
{
	int k,i=0; double n;
	char *check = new char[line.size()];
	for (int j = 0; j < line.size(); j++)
		check[j] = false;

	while(i<line.size())
	{
		k = 0; n = 0;
		while (isdigit(line[i]) && i<line.size())
		{
			n = n*10+conv(line[i]);
			k++;
			i++;
		}
		if (!check[i])
		{
			check[i] = true;
			i--;
		}
		if(!InStandart(line[i]))
		operands.push(n);
		if (check[i+1]) i++;
		if (i > line.size()-1) break;
		if (InStandart(line[i]))
		{
			if (operators.empty())
				operators.push(line[i]);
			else
			{
				if (line[i] != ')' && GetPriority(line[i]) > GetPriority(operators.peack()) || line[i]=='(')
					operators.push(line[i]);
				else if (GetPriority(line[i]) <= GetPriority(operators.peack()) && line[i] != '(' && line[i] != ')')
				{
					double op1, op2,s=0; char eq;
					while (GetPriority(line[i]) <= GetPriority(operators.peack()))
					{
						op2 = operands.pop();
						op1 = operands.pop();
						eq = operators.pop();
						s = res(eq, op1, op2);
						operands.push(s);
						if (operators.empty()) break;
					}
					operators.push(line[i]);
				}
				else if (line[i] == ')')
				{
					double op1, op2, s = 0; char c;
					do {
						c = operators.pop();
						if (c == '(')break;
						op2 = operands.pop();
						op1 = operands.pop();
						if(c!='(' && c!=')')
						s = res(c, op1, op2);
						operands.push(s);
					} while (c != '(');
				}
			}
			
		}
		i++;
	}
	double op1, op2,s=0; char c;
	while (!operators.empty())
	{
		c = operators.pop();
		op2 = operands.pop();
		op1 = operands.pop();
		s = res(c, op1, op2);
		operands.push(s);
	}
	cout <<line<<"=" << operands.peack()<<"\n";
}
int main()
{
	string s; 
	stack <char> op1; stack <double> op2;
	cin >> s;
	parse_operands(s, op2,op1);
	system("pause");
    return 0;
}

