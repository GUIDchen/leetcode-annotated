# 题目：2224. 转化时间需要的最少操作数（Minimum Number of Operations to Convert Time）
# 思路：把两个时刻都换算成分钟，再按 60、15、5、1 从大到小贪心扣除差值。
# 时间复杂度：O(1)，只遍历 4 种固定增量；空间复杂度：O(1)，仅使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def convertTime(self, current: str, correct: str) -> int:  # current：当前时间；correct：目标时间，格式 "HH:MM"
        a = int(current[:2]) * 60 + int(current[3:])  # 当前时间折算成分钟
        b = int(correct[:2]) * 60 + int(correct[3:])  # 目标时间折算成分钟
        ans, d = 0, b - a  # ans 记录操作次数，d 表示还差多少分钟
        for i in [60, 15, 5, 1]:  # 依次尝试四种增量，从大到小保证用量最少
            ans += d // i  # 当前增量最多能使用的次数
            d %= i  # 用完后剩余的分钟数
        return ans  # 返回最少操作次数
