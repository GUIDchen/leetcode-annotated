# 题目：2055. 蜡烛之间的盘子（Plates Between Candles）
# 思路：预处理盘子数量的前缀和，以及每个位置左右最近的蜡烛下标；对每个查询取区间内左右两根蜡烛，用前缀和差值统计中间的盘子。
# 时间复杂度：O(n + q)，n 为字符串长度、q 为查询数；空间复杂度：O(n)，前缀和与左右蜡烛下标数组。
class Solution:  # 题解类
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:  # s 是蜡烛/盘子串，queries 是一组区间
        n = len(s)  # 串长
        presum = [0] * (n + 1)  # presum[i] 表示前 i 个字符中盘子的个数
        for i, c in enumerate(s):  # 从左到右统计盘子的前缀和
            presum[i + 1] = presum[i] + (c == '*')  # 是盘子就加一，bool 结果可直接当 0/1

        left, right = [0] * n, [0] * n  # left[i]、right[i]：i 左右两侧最近的蜡烛下标
        l = r = -1  # -1 表示该侧还没有蜡烛
        for i, c in enumerate(s):  # 从左往右扫，维护最近蜡烛位置
            if c == '|':  # 遇到蜡烛
                l = i  # 更新最近蜡烛下标
            left[i] = l  # 记下 i 左侧最近的蜡烛
        for i in range(n - 1, -1, -1):  # 从右往左扫，维护右侧最近蜡烛
            if s[i] == '|':  # 遇到蜡烛
                r = i  # 更新最近蜡烛下标
            right[i] = r  # 记下 i 右侧最近的蜡烛

        ans = [0] * len(queries)  # 每个查询的答案
        for k, (l, r) in enumerate(queries):  # 逐个处理查询区间 [l, r]
            i, j = right[l], left[r]  # i 是区间内的左蜡烛，j 是区间内的右蜡烛
            if i >= 0 and j >= 0 and i < j:  # 两端都找到蜡烛且左在右之前
                ans[k] = presum[j] - presum[i + 1]  # 前缀和差值即两根蜡烛之间的盘子数
        return ans  # 返回全部答案
