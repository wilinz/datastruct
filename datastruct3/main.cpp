#include<iostream>
#include<string>
using namespace std;

unsigned char Prior[7][7] =
        { // 运算符优先级表
                // '+' '-' '*' '/' '(' ')' '#'
                /*'+'*/'>','>','<','<','<','>','>',
                /*'-'*/'>','>','<','<','<','>','>',
                /*'*'*/'>','>','>','>','<','>','>',
                /*'/'*/'>','>','>','>','<','>','>',
                /*'('*/'<','<','<','<','<','=',' ',
                /*')'*/'>','>','>','>',' ','>','>',
                /*'#'*/'<','<','<','<','<',' ','='
        };

template<typename Datatype>
struct Node
{
    Datatype data;
    Node<Datatype> *next;
};

template <typename Datatype>
class LinkStack
{
private:
    Node<Datatype> *top;
public:
    LinkStack();
    ~LinkStack();
    void Push(Datatype x);
    Datatype Pop();
    Datatype GetTop();
    int empty();
    void printStack();
};

template <typename Datatype>
LinkStack<Datatype>::LinkStack()
{
    top = NULL;
}

template <typename Datatype>
LinkStack<Datatype>::~LinkStack()
{
    while(!empty())
    {
        Pop();
    }
}

template <typename Datatype>
void LinkStack<Datatype>::Push(Datatype x)
{
    Node<Datatype>* newNode = new Node<Datatype>;
    newNode->data = x;
    newNode->next = top;
    top = newNode;
}

template <typename Datatype>
Datatype LinkStack<Datatype>::Pop()
{
    if(empty())
    {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    Node<Datatype>* tempNode = top;
    Datatype tempData = top->data;
    top = top->next;
    delete tempNode;
    return tempData;
}

template <typename Datatype>
int LinkStack<Datatype>::empty()
{
    return top == NULL;
}

template <typename Datatype>
void LinkStack<Datatype>::printStack()
{
    Node<Datatype> *p = top;
    while(p)
    {
        cout<<p->data<<"\t";
        p = p->next;
    }
    cout<<endl;
}

template <typename Datatype>
Datatype LinkStack<Datatype>::GetTop()
{
    Datatype x;
    if(top==NULL)
    {
        cout<<"No data!"<<endl;
    }
    else
    {
        x = top->data;
    }
    return x;
}

int op2num(char op) {
    switch(op) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case '#': return 6;
        default: return -1;
    }
}

int CalExpression(string expstr) {
    LinkStack<int> numStack;
    LinkStack<char> opStack;
    expstr += '#'; // 追加结束符号
    opStack.Push('#'); // 将结束符号压入堆栈
    int i = 0;
    while(i < expstr.size()) {
        if(isdigit(expstr[i])) { // 如果它是一个数字
            int num = 0;
            while(isdigit(expstr[i])) {
                num = num * 10 + (expstr[i] - '0');
                i++;
            }
            numStack.Push(num);
        } else { // 如果它是一个 operator
            switch(Prior[op2num(opStack.GetTop())][op2num(expstr[i])]) {
                case '<': // 将运算符压入堆栈
                    opStack.Push(expstr[i]);
                    i++;
                    break;
                case '=': // pop '(' and ')' or '#' and '#'
                    opStack.Pop();
                    i++;
                    break;
                case '>': { // 弹出运算符并计算
                    int num2 = numStack.Pop();
                    if(numStack.empty()) { // 错误：缺少操作数
                        cout << "错误：缺少操作数！" << endl;
                        return -1;
                    }
                    int num1 = numStack.Pop();
                    char op = opStack.Pop();
                    int res = 0;
                    switch(op) {
                        case '+': res = num1 + num2; break;
                        case '-': res = num1 - num2; break;
                        case '*': res = num1 * num2; break;
                        case '/':
                            if(num2 == 0) { // 错误：除以零
                                cout << "错误：除以零！" << endl;
                                return -1;
                            }
                            res = num1 / num2;
                            break;
                    }
                    numStack.Push(res);
                    break;
                }
                default: // 错误：无效的运算符
                    cout << "错误：无效的运算符！" << endl;
                    return -1;
            }
        }
    }
    if(!opStack.empty()) { // 错误：括号不匹配
        cout << "错误：括号不匹配！" << endl;
        return -1;
    }
    return numStack.GetTop();
}


int main()
{
    int value;
    string expstr;
    cout<<"请输入表达式："<<endl;
    cin>>expstr;
    value = CalExpression(expstr);
    cout<<value<<endl;
    return 0;
}
