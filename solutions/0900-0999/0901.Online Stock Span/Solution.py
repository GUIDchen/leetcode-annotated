# 题目：901. 股票价格跨度（Online Stock Span）
# 核心思路：单调递减栈保存 (价格, 跨度)，遇到不高于当前价格的历史项就弹出并累加其跨度。
# 时间复杂度：均摊 O(1)，每个元素最多入栈出栈各一次；空间复杂度：O(n) 保存栈内元素。
class StockSpanner:  # 股票价格跨度计算器
    def __init__(self):  # 构造函数：用一个列表模拟栈
        self.stk = []  # 栈元素为 (价格, 该价格对应的跨度)

    def next(self, price: int) -> int:  # price：今天的新价格，返回以今天为结尾的跨度
        cnt = 1  # 跨度至少包含今天这一天
        while self.stk and self.stk[-1][0] <= price:  # 栈顶价格不高于今天，就可以被合并
            cnt += self.stk.pop()[1]  # 弹出栈顶并累加它记录的跨度
        self.stk.append((price, cnt))  # 把今天的价格与合并后的跨度压栈
        return cnt  # 返回今天的跨度


# Your StockSpanner object will be instantiated and called as such:
# obj = StockSpanner()
# param_1 = obj.next(price)
