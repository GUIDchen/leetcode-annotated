# 题目：2048. 下一个更大的数值平衡数（Next Greater Numerically Balanced Number）
# 思路：用 count 生成从 n+1 开始的递增序列，对每个数统计各数字出现次数，再判断每个数字 d 是否恰好出现 d 次，第一个满足的数就是答案。
# 时间复杂度：O(k · log n)，k 为跳过的候选数个数；空间复杂度：O(1)，只用了固定长度 10 的计数数组。
class Solution:  # LeetCode 约定的题解类
    def nextBeautifulNumber(self, n: int) -> int:  # n 是下界，返回严格大于 n 的最小数值平衡数
        for x in count(n + 1):  # itertools.count 生成从 n+1 开始的无限递增序列，逐个检查
            y = x  # 用副本 y 做数位拆解，保留 x 用来返回
            cnt = [0] * 10  # cnt[d] 记录数字 d 在这数中出现的次数
            while y:  # 只要还有位就继续拆
                y, v = divmod(y, 10)  # divmod 同时得到去掉最低位后的数与最低位数字 v
                cnt[v] += 1  # 数字 v 的计数加一
            if all(v == 0 or i == v for i, v in enumerate(cnt)):  # 对每个数字 d：要么没出现（v == 0），要么出现次数恰好等于 d
                return x  # 第一个满足条件的数就是答案
