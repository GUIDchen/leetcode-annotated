// 题目：155. 最小栈（Min Stack）
// 思路：两个栈，stk1 正常存放所有元素，stk2 同步存放「当前栈顶位置对应的历史最小值」，两者同增同减。
// 时间复杂度：push/pop/top/getMin 均为 O(1)；空间复杂度：O(n)，每个元素在两个栈中各存一份。
class MinStack {  // 题目要求实现的 MinStack 类
public:  // 对外提供的接口
    MinStack() {  // 构造函数：初始化辅助栈
        stk2.push(INT_MAX);  // 给最小值栈压入 INT_MAX 作为哨兵，保证第一次取 min 时不会越界
    }  // 构造函数结束

    void push(int val) {  // 入栈：同时维护两个栈
        stk1.push(val);  // 数据栈照常压入新元素
        stk2.push(min(val, stk2.top()));  // 最小值栈压入「新元素」与「此前最小值」中的较小者
    }  // push 结束

    void pop() {  // 出栈：两栈同步弹出，保证最小值栈栈顶始终对应当前数据栈的最小值
        stk1.pop();  // 弹出数据栈栈顶
        stk2.pop();  // 弹出最小值栈栈顶
    }  // pop 结束

    int top() {  // 返回数据栈栈顶元素，即最后入栈的值
        return stk1.top();  // 直接取 stk1 的栈顶
    }  // top 结束

    int getMin() {  // 返回当前栈内最小元素
        return stk2.top();  // stk2 的栈顶始终是当前最小值
    }  // getMin 结束

private:  // 私有成员：外部不可见，封装两个栈
    stack<int> stk1;  // 数据栈，保存全部入栈元素
    stack<int> stk2;  // 最小值栈，保存与数据栈逐层对应的历史最小值
};  // 类定义结束

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */