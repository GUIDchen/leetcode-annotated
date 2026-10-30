# 题目：2223. 构造字符串的总得分和（Sum of Scores of Built Strings）
# 思路：用 Z 函数（扩展 KMP）求每个后缀 s[i:] 与 s 的最长公共前缀长度 z[i]，答案为 n + Σz[i]。
# 时间复杂度：O(n)，扩展指针不回退、总扩展量线性；空间复杂度：O(n)，z 数组与字符串等长。
class Solution:  # LeetCode 约定的题解类
    def sumScores(self, s: str) -> int:  # s：待求得分和的字符串，返回所有后缀与 s 的公共前缀长度之和
        n = len(s)  # 字符串长度
        z = [0] * n  # z[i] 表示 s[i:] 与 s 的最长公共前缀长度
        l = r = 0  # [l, r] 是当前已确认匹配的最右区间
        for i in range(1, n):  # 从下标 1 开始逐个计算 z[i]
            if i <= r:  # i 落在已知区间内，可以复用镜像位置的结果
                z[i] = min(r - i + 1, z[i - l])  # 取区间剩余长度与镜像 z 值中的较小者
            while i + z[i] < n and s[z[i]] == s[i + z[i]]:  # 从初值继续向后扩展，直到失配或越界
                z[i] += 1  # 匹配成功一个字符，公共前缀长度加一
            if i + z[i] - 1 > r:  # 新的右端点超出旧区间，需要更新区间
                l, r = i, i + z[i] - 1  # 左端点设为 i，右端点设为匹配到的最远位置
        return n + sum(z)  # 原串自身得分 n，加上所有后缀的 z 值之和
