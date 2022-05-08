#include <iostream>
#include <string>
#include<vector>
#define SIZE 4
using namespace std;
struct Rectangle
{
    int x;
    int y;
    //重载输入和输出
    friend ostream& operator<<(ostream&, const Rectangle&);
    friend istream& operator>>(istream&, Rectangle&);
};
ostream& operator<<(ostream& os, const Rectangle& p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
istream& operator>>(istream& is, Rectangle& p)
{
    is >> p.x;
    is.get();
    is >> p.y;
    //输入判断
    if (!is)
        p = Rectangle(); //如果失败，默认初始化
    return is;
}
template<typename T>
class Stack {
private:
    T  elems[SIZE];
    int head = 0;
public:
    void push(const T& elem) throw(char*)
    {
        if (!isFull())
            elems[head++] = elem;
        else
            //栈满了则抛出错误
            throw "Stack is full!";
    }
    T pop() throw(char*)
    {
        if (!isEmpty())
        {
            head--;
            return elems[head];
        }
        else
        {
            //栈为空则抛出错误
            throw "Stack is empty!";
        }
    }
    bool isEmpty() {
        return head == 0;
    }
    bool isFull() {
        return head == SIZE;
    }
    void print() {
        cout << "[";
        for (int i = 0; i < head; i++)
        {
            cout << elems[i] << ",";
        }
        cout << "]";
    }
};
template<typename T>
class Queue {
private:
    Stack<T> stackA;
    Stack<T> stackB;
public:
    void inQueue(const T& elem) throw(char*)
    {
        if (isFull())
        {
            //队列已满
            throw "Queue is full!";
        }
        else
        {
            stackA.push(elem);
        }
    }
    T deQueue() throw(char*)
    {
        if (stackB.isEmpty())
        {
            if (stackA.isEmpty())
            {
                //队列为空
                throw "Queue is empty!";
            }
            else
            {
                while (!stackA.isEmpty())
                {
                    stackB.push(stackA.pop());
                }
                return stackB.pop();
            }
        }
        else
        {
            return stackB.pop();
        }
    }
    bool isEmpty()
    {
        return stackA.isEmpty() && stackB.isEmpty();
    }
    bool isFull()
    {
        return stackA.isFull();
    }
    void print()
    {
        cout << "[";
        while (!stackB.isEmpty())
        {
            cout << stackB.pop() << ",";
        }
        vector<T> arr;
        while (!stackA.isEmpty())
        {
            arr.push_back(stackA.pop());
        }
        for (auto i = arr.rbegin(); i != arr.rend(); i++)
        {
            cout << *i << ",";
        }
        cout << "]";
    }
};
//循环的函数
template<typename T>
void loop(Queue<T> queue)
{
    int operate;
    T temp;
    while (cin >> operate)
    {
        if (operate == 0)
        {
            queue.print();
            break;
        }
        else if (operate == 1)
        {
            cin >> temp;
            try
            {
                queue.inQueue(temp);
            }
            catch (const char* msg)
            {
                cout << msg << endl;
            }
        }
        else if (operate == 2)
        {
            try
            {
                temp = queue.deQueue();
                cout << temp << " is deQueued" << endl;
            }
            catch (const char* msg)
            {
                cout << msg << endl;
            }
        }
    }
}
int main()
{
    int type;
    cin >> type;
    if (type == 0)
    {
        Queue<int> stack;
        loop(stack);
    }
    else if (type == 1)
    {
        Queue<string> stack;
        loop(stack);
    }
    else if (type == 2)
    {
        Queue<Rectangle> stack;
        loop(stack);
    }
    else
    {
        cout << "输入错误" << endl;
        return 1;
    }
    return 0;
}


