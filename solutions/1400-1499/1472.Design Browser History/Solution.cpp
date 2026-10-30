// 题目：1472. 设计浏览器历史记录（Design Browser History）
// 核心思路：用两个栈分别保存「可以后退的历史」与「可以前进的历史」，访问新页面时清空前进栈，后退/前进就是两个栈之间来回搬元素。
// 时间复杂度：单次操作 O(steps)；空间复杂度：O(总页面数)，两个栈合计保存全部记录。
class BrowserHistory {  // 浏览器历史记录类
public:  // 接口对外可见
    stack<string> stk1;  // stk1 的栈顶是当前页面，栈底是最早的页面（用于后退）
    stack<string> stk2;  // stk2 的栈顶是「后退一步后还能前进回去」的页面（用于前进）

    BrowserHistory(string homepage) {  // 构造函数：初始只打开 homepage
        visit(homepage);  // 复用 visit 完成初始化，顺便清空前进栈
    }  // 构造函数结束

    void visit(string url) {  // 访问新页面 url
        stk1.push(url);  // 新页面成为当前页
        stk2 = stack<string>();  // 新开页面后原来的前进记录全部作废，重新赋值即清空
    }  // visit 方法结束

    string back(int steps) {  // 最多后退 steps 步，返回最终所在页面
        for (; steps && stk1.size() > 1; --steps) {  // 还有步数可退且不是最早那一页时继续后退
            stk2.push(stk1.top());  // 当前页压入前进栈，之后还能再前进回来
            stk1.pop();  // 从后退栈弹出，露出上一页
        }  // 后退结束
        return stk1.top();  // stk1 栈顶就是当前页面
    }  // back 方法结束

    string forward(int steps) {  // 最多前进 steps 步，返回最终所在页面
        for (; steps && !stk2.empty(); --steps) {  // 还有步数且前进栈非空时继续前进
            stk1.push(stk2.top());  // 把前进栈顶的页面取回后退栈
            stk2.pop();  // 从前进栈弹出，避免重复前进
        }  // 前进循环结束
        return stk1.top();  // 返回当前页面
    }  // forward 方法结束
};  // 类定义结束

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */