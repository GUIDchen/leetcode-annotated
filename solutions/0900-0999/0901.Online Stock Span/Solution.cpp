// 题目：901. 股票价格跨度（Online Stock Span）
// 核心思路：单调递减栈保存 (价格, 该价格对应的跨度)，遇到不高于当前价格的历史项就弹出并累加其跨度。
// 时间复杂度：均摊 O(1)，每个元素最多入栈出栈各一次；空间复杂度：O(n) 保存栈内元素。
class StockSpanner {  // 股票价格跨度计算器
public:  // 构造函数与 next 方法对外可见
    StockSpanner() {  // 构造函数：栈是成员变量，无需额外初始化
    }

    int next(int price) {  // price：今天的新价格，返回以今天为结尾的跨度
        int cnt = 1;  // 跨度至少包含今天这一天
        while (!stk.empty() && stk.top().first <= price) {  // 栈顶价格不高于今天，就可以被今天「吃掉」
            cnt += stk.top().second;  // 累加被弹出元素自身的跨度
            stk.pop();  // 弹出这个元素，它不会再被后面的价格用到
        }
        stk.emplace(price, cnt);  // 把今天的价格与合并后的跨度压栈
        return cnt;  // 返回今天的跨度
    }

private:  // 以下为内部状态
    stack<pair<int, int>> stk;  // 单调栈：first 是价格，second 是该价格对应的跨度
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */