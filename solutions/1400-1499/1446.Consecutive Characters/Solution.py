# 题目：1446. 连续字符（Consecutive Characters）
# 核心思路：一次线性扫描，用 t 记录当前连续相同字符的段长，用 ans 维护历史最大段长。
# 时间复杂度：O(n)，只遍历字符串一遍；空间复杂度：O(1)，只用两个整型变量。
class Solution:  # LeetCode 约定的题解类
    def maxPower(self, s: str) -> int:  # 返回 s 中最长的一段连续相同字符的长度
        ans = t = 1  # ans 保存历史最长段长；t 保存当前连续段长，字符串非空时至少为 1
        for a, b in pairwise(s):  # pairwise 依次产出相邻字符对 (a, b)，其中 a 在前、b 在后（Python 3.10+）
            if a == b:  # 相邻两个字符相同，连续段继续延伸
                t += 1  # 当前段长加一
                ans = max(ans, t)  # 用当前段长刷新历史最大值
            else:  # 相邻两个字符不同，连续段在此断开
                t = 1  # 从当前字符重新开始计数
        return ans  # 返回最长连续段的长度
