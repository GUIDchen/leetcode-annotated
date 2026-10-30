# 题目：1172. 餐盘栈（Dinner Plate Stacks）
# 思路：用列表存每摞盘子，再用有序集合 not_full 记录所有未满栈的下标；push 放进最左未满栈，pop 从最右栈弹出并回收尾部空栈。
# 时间复杂度：push / pop / popAtStack 均为 O(log n)；空间复杂度：O(n)，即所有盘子的数量。
class DinnerPlates:  # 题目要求实现的餐盘栈类
    def __init__(self, capacity: int):  # 构造：记录容量，初始化栈列表与「未满栈下标集合」
        self.capacity = capacity  # 每个栈的容量上限
        self.stacks = []  # 所有栈，按从左到右的顺序保存
        self.not_full = SortedSet()  # 未满栈的下标集合，SortedSet 保证能取到最左的那个

    def push(self, val: int) -> None:  # 把 val 压入最左边的未满栈
        if not self.not_full:  # 当前没有任何未满的栈
            self.stacks.append([val])  # 在最右边新开一个栈并放入盘子
            if self.capacity > 1:  # 新栈还没有满
                self.not_full.add(len(self.stacks) - 1)  # 把新栈下标加入未满集合
        else:  # 否则存在未满的栈
            index = self.not_full[0]  # 取下标最小的未满栈
            self.stacks[index].append(val)  # 把盘子压入该栈
            if len(self.stacks[index]) == self.capacity:  # 压入后该栈刚好满了
                self.not_full.discard(index)  # 从「未满集合」中移除

    def pop(self) -> int:  # 弹出最右（下标最大）的栈顶
        return self.popAtStack(len(self.stacks) - 1)  # 复用 popAtStack 完成

    def popAtStack(self, index: int) -> int:  # 弹出指定下标栈的栈顶
        if index < 0 or index >= len(self.stacks) or not self.stacks[index]:  # 下标越界或该栈为空时返回 -1
            return -1  # 返回 -1 表示无法弹出
        val = self.stacks[index].pop()  # 弹出并记下栈顶元素
        if index == len(self.stacks) - 1 and not self.stacks[-1]:  # 弹出的是最右边的栈，且它被弹空了
            while self.stacks and not self.stacks[-1]:  # 从右往左清理所有空栈
                self.not_full.discard(len(self.stacks) - 1)  # 同步从未满集合中移除该下标
                self.stacks.pop()  # 删除这个空栈
        else:  # 否则当前栈仍有盘子，现在变为未满
            self.not_full.add(index)  # 加入未满集合
        return val  # 返回弹出的值


# Your DinnerPlates object will be instantiated and called as such:
# obj = DinnerPlates(capacity)
# obj.push(val)
# param_2 = obj.pop()
# param_3 = obj.popAtStack(index)
