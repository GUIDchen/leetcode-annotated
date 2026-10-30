# 题目：2457. 美丽整数的最小增量（Minimum Addition to Make Integer Beautiful）
# 思路：n 的数位和已 ≤ target 时答案为 0；否则每次把「最低非零位」清零并向高位进一，得到下一个候选数，
# 这样跳过了所有中间值（中间值的数位和只会更大），首次满足数位和条件的增量就是最小值。
# 时间复杂度：O((log n)^2) 级别，迭代次数与位数同阶、每次求数位和为 O(log n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def makeIntegerBeautiful(self, n: int, target: int) -> int:  # n：初始整数；target：数位和上限；返回最小增量
        def f(x: int) -> int:  # 内部函数：计算十进制各位数字之和
            y = 0  # 累计数位和，初值为 0
            while x:  # 只要 x 非 0 就继续取位
                y += x % 10  # 取出最低位数字累加
                x //= 10  # 去掉最低位
            return y  # 返回数位和

        x = 0  # 需要增加的最小量，从 0（即不做改动）开始试探
        while f(n + x) > target:  # 候选数的数位和仍超过 target，需要继续进位取整
            y = n + x  # 当前候选数
            p = 10  # 进位后最低位的权重，初始为 10（进到十位）
            while y % 10 == 0:  # 末位为 0 的位加 1 不改变数位和，跳过它们
                y //= 10  # 去掉末位 0
                p *= 10  # 权重扩大 10 倍
            x = (y // 10 + 1) * p - n  # 把最低非零位清零并向更高一位进一，得到下一个候选数的增量
        return x  # 此时 x 即最小增量
