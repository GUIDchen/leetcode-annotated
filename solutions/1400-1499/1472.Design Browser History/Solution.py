# 题目：1472. 设计浏览器历史记录（Design Browser History）
# 核心思路：两个列表当栈用，stk1 保存可以后退的历史，stk2 保存可以前进的历史；访问新页面时清空 stk2。
# 时间复杂度：单次操作 O(steps)；空间复杂度：O(总页面数)，两个栈合计保存全部记录。
class BrowserHistory:  # 浏览器历史记录类
    def __init__(self, homepage: str):  # 构造函数：初始只打开 homepage
        self.stk1 = []  # 后退栈：末尾是当前页面
        self.stk2 = []  # 前进栈：末尾是下一步可以前进到的页面
        self.visit(homepage)  # 复用 visit 完成初始化

    def visit(self, url: str) -> None:  # 访问新页面，无返回值
        self.stk1.append(url)  # 新页面成为当前页
        self.stk2.clear()  # 前进记录全部作废

    def back(self, steps: int) -> str:  # 最多后退 steps 步，返回最终页面
        while steps and len(self.stk1) > 1:  # 还有步数且不是最早那一页时继续后退
            self.stk2.append(self.stk1.pop())  # 当前页搬到前进栈，之后还能再前进回来
            steps -= 1  # 消耗一步
        return self.stk1[-1]  # 返回当前页面

    def forward(self, steps: int) -> str:  # 最多前进 steps 步，返回最终页面
        while steps and self.stk2:  # 还有步数且前进栈非空时继续前进
            self.stk1.append(self.stk2.pop())  # 从前进栈取回页面，放回后退栈
            steps -= 1  # 消耗一步
        return self.stk1[-1]  # 返回当前页面


# Your BrowserHistory object will be instantiated and called as such:
# obj = BrowserHistory(homepage)
# obj.visit(url)
# param_2 = obj.back(steps)
# param_3 = obj.forward(steps)
