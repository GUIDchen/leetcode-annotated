// 题目：225. 用队列实现栈（Implement Stack using Queues）
// 思路：push 时先把新元素放进辅助队列 q2，再把 q1 的旧元素整体搬到 q2 尾部，最后交换两队列，使 q1 的队头始终是栈顶。
// 时间复杂度：push 为 O(n)（要搬动全部元素），pop/top/empty 为 O(1)；空间复杂度：O(n)，两个队列共存 n 个元素。
class MyStack {  // 只用队列模拟出的栈
public:  // 接口对外可见
    MyStack() {  // 构造函数：两个队列默认构造为空即满足要求
    }  // 无需额外初始化，函数体留空

    void push(int x) {  // 入栈：x 是待压入的元素
        q2.push(x);  // 新元素先进入辅助队列 q2，它将变成新的栈顶
        while (!q1.empty()) {  // 把 q1 里已有的元素按原顺序全部搬到 q2 尾部
            q2.push(q1.front());  // 取出 q1 的队头元素
            q1.pop();  // 该元素已搬走，从 q1 弹出
        }
        swap(q1, q2);  // 交换后 q1 持有完整数据且队头是新元素，q2 变回空队列
    }

    int pop() {  // 出栈：返回并删除栈顶元素
        int x = q1.front();  // q1 的队头就是栈顶
        q1.pop();  // 删除这个栈顶元素
        return x;  // 返回被删除的值
    }

    int top() {  // 返回栈顶元素但不删除
        return q1.front();  // q1 队头即栈顶，直接读取
    }

    bool empty() {  // 判断栈是否为空
        return q1.empty();  // 队列为空等价于栈为空
    }

private:  // 两个队列都是私有成员，外部不可见
    queue<int> q1;  // q1 始终保存全部元素，队头是栈顶
    queue<int> q2;  // q2 只在 push 过程中临时使用
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */