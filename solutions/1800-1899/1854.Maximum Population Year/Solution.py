# 题目：1854. 人口最多的年份（Maximum Population Year）
# 思路：差分数组记录出生年 +1、死亡年 −1，再做前缀和得到每年人口，取第一个最大值对应的年份。
# 时间复杂度：O(n + 101)，遍历日志加一次 101 年扫描；空间复杂度：O(1)，差分数组固定 101 长。
class Solution:  # LeetCode 约定的题解类
    def maximumPopulation(self, logs: List[List[int]]) -> int:  # logs：每条记录是 [出生年, 死亡年]
        d = [0] * 101  # 差分数组，覆盖 1950..2050 共 101 年
        offset = 1950  # 基准年，把年份映射到 0..100 的下标
        for a, b in logs:  # 逐条处理每个人的出生与死亡
            a, b = a - offset, b - offset  # 出生年与死亡年分别映射为下标
            d[a] += 1  # 出生年人口 +1
            d[b] -= 1  # 死亡年人口 −1（该年此人已不计入人口）
        s = mx = j = 0  # s 为当前人口；mx 为历史最大人口；j 为最大人口对应下标
        for i, x in enumerate(d):  # 按下标顺序扫描每一年
            s += x  # 前缀和还原出该年的实际人口
            if mx < s:  # 只有严格更大才更新，从而保留最早的年份
                mx, j = s, i  # 同时更新最大人口与对应下标
        return j + offset  # 下标换回真实年份
