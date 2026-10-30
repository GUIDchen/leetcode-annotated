# 题目：1381. 设计一个支持增量操作的栈（Design a Stack With Increment Operation）
# 思路：用 stk 存栈体、add 存延迟增量；increment 只在第 min(k,i)-1 位打标记，pop 时把标记向栈底方向传递。
# 时间复杂度：push/pop/increment 均为 O(1)；空间复杂度：O(maxSize)，两个与容量等长的列表。
class CustomStack:  # 题目要求实现的类
    def __init__(self, maxSize: int):  # maxSize：栈的容量上限
        self.stk = [0] * maxSize  # 栈体数组，预分配 maxSize 个位置
        self.add = [0] * maxSize  # 延迟增量数组，下标与栈体一致
        self.i = 0  # 当前元素个数，也是下一个可写位置

    def push(self, x: int) -> None:  # x：要压入的元素
        if self.i < len(self.stk):  # 栈未满才允许写入
            self.stk[self.i] = x  # 写入栈顶位置
            self.i += 1  # 元素个数加一

    def pop(self) -> int:  # 弹出栈顶并返回真实值，空栈返回 -1
        if self.i <= 0:  # 栈空
            return -1  # 按题目约定返回 -1
        self.i -= 1  # 先回退到栈顶下标
        ans = self.stk[self.i] + self.add[self.i]  # 栈顶值叠加上该位置累积的增量
        if self.i > 0:  # 下面还有元素
            self.add[self.i - 1] += self.add[self.i]  # 把增量下传给下一个元素
        self.add[self.i] = 0  # 标记已消费，清零避免影响后续压入
        return ans  # 返回叠加后的栈顶值

    def increment(self, k: int, val: int) -> None:  # 把栈底 k 个元素各加 val
        i = min(k, self.i) - 1  # 实际要覆盖的最后一个元素下标，栈空时为 -1
        if i >= 0:  # 栈非空才有效
            self.add[i] += val  # 只在这一处打标记，pop 时再向下传递


# Your CustomStack object will be instantiated and called as such:
# obj = CustomStack(maxSize)
# obj.push(x)
# param_2 = obj.pop()
# obj.increment(k,val)
