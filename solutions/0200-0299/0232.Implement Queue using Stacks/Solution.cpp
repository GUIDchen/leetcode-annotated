// 题目：232. 用栈实现队列（Implement Queue using Stacks）
// 思路：两个栈分工，stk1 只负责入队；出队或取队首时若 stk2 为空，就把 stk1 全部倒进 stk2，顺序被翻正，stk2 栈顶即队首。
// 时间复杂度：均摊 O(1)，每个元素最多被搬动一次；空间复杂度：O(n)，两个栈合计存 n 个元素。
class MyQueue {  // 用两个栈模拟队列的类
public:  // 对外提供的队列接口
    MyQueue() {  // 构造函数：两个栈默认就是空的，无需额外操作
    }  // 构造函数结束

    void push(int x) {  // 入队：x 是待入队的元素
        stk1.push(x);  // 直接压入输入栈，入队永远是 O(1)
    }  // push 结束

    int pop() {  // 出队：返回并删除队首元素
        move();  // 先整理两个栈，保证 stk2 栈顶就是队首
        int ans = stk2.top();  // 记下队首的值
        stk2.pop();  // 真正把队首弹出
        return ans;  // 返回刚才记下的队首
    }  // pop 结束

    int peek() {  // 取队首：只读不删
        move();  // 同样先整理两个栈
        return stk2.top();  // 输出栈的栈顶就是队首
    }  // peek 结束

    bool empty() {  // 判空
        return stk1.empty() && stk2.empty();  // 两个栈都空，队列才空
    }  // empty 结束

private:  // 内部数据成员
    stack<int> stk1;  // 输入栈：只负责 push
    stack<int> stk2;  // 输出栈：负责 pop 与 peek

    void move() {  // 把输入栈的元素全部倒进输出栈，从而翻转元素顺序
        if (stk2.empty()) {  // 只有输出栈为空时才搬，避免打乱已经排好的顺序
            while (!stk1.empty()) {  // 逐个弹出输入栈的元素
                stk2.push(stk1.top());  // 压入输出栈，后进先出正好把顺序倒过来
                stk1.pop();  // 弹出已经搬走的元素
            }  // 循环结束
        }  // 搬移结束
    }  // move 结束
};  // 类结束

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */