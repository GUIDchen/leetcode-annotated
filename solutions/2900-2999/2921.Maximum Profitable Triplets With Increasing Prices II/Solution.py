# 题目：2921. 价格递增的最大利润三元组 II（Maximum Profitable Triplets With Increasing Prices II）
# 思路：对每个中间位置 i，用树状数组分别预处理左侧价格更小、右侧价格更大的最大利润，再枚举 i 取三段利润之和的最大值。
# 时间复杂度：O(n log m)，两次扫描各一次查询与更新；空间复杂度：O(n + m)，两个树状数组与两个辅助数组。
class BinaryIndexedTree:  # 树状数组：维护前缀最大值
    def __init__(self, n: int):  # n 为下标上限（价格最大值 + 1）
        self.n = n  # 保存下标上限
        self.c = [0] * (n + 1)  # 树状数组从下标 1 开始，初始化为 0

    def update(self, x: int, v: int):  # 把位置 x 的贡献更新为 max(原值, v)
        while x <= self.n:  # 沿父链向上跳
            self.c[x] = max(self.c[x], v)  # 覆盖 x 的区间都取最大值
            x += x & -x  # lowbit 跳到下一个覆盖位置

    def query(self, x: int) -> int:  # 查询区间 [1, x] 的最大值
        mx = 0  # 利润均为正，0 表示空集
        while x:  # 不断去掉最低位的 1
            mx = max(mx, self.c[x])  # 用当前区间更新答案
            x -= x & -x  # lowbit 跳到前一个区间
        return mx  # 返回前缀最大值


class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int], profits: List[int]) -> int:  # 找 i<j<k 且价格递增时利润和最大的三元组
        n = len(prices)  # 商品个数
        left = [0] * n  # left[i]：i 左边价格更小商品的最大利润
        right = [0] * n  # right[i]：i 右边价格更大商品的最大利润

        m = max(prices)  # 价格最大值，用来确定树状数组大小
        tree1 = BinaryIndexedTree(m + 1)  # 从左往右扫描时使用的树状数组
        tree2 = BinaryIndexedTree(m + 1)  # 从右往左扫描时使用的树状数组

        for i, x in enumerate(prices):  # 第一遍：从左到右
            left[i] = tree1.query(x - 1)  # 查询价格严格小于 x 的已出现商品的最大利润
            tree1.update(x, profits[i])  # 把当前商品按价格插入树状数组
        for i in range(n - 1, -1, -1):  # 第二遍：从右到左
            x = m + 1 - prices[i]  # 反向映射价格，使「更大」变成「更小」
            right[i] = tree2.query(x - 1)  # 查询右侧价格严格更大的商品的最大利润
            tree2.update(x, profits[i])  # 把当前商品插入树状数组

        return max(  # 枚举中间元素，取总利润最大值
            (l + x + r for l, x, r in zip(left, profits, right) if l and r), default=-1  # 左右都存在的三元组才参与比较，无解时用 -1
        )  # max 调用结束
