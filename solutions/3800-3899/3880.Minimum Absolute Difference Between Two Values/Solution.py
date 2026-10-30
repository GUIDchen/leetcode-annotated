# 3880. 两个值之间的最小绝对差值 / Minimum Absolute Difference Between Two Values
# 核心思路：只有 1 与 2 构成“两个不同值”，扫描时用 last 记录各值上次出现的下标并更新最小间距。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义题解类
    def minAbsoluteDifference(self, nums: list[int]) -> int:  # 返回两个值出现位置的最小下标差
        n = len(nums)  # 数组长度
        ans = n + 1  # 答案先置为哨兵值 n + 1
        last = [-inf] * 3  # 记录每个值上次出现的下标，初值为负无穷
        for i, x in enumerate(nums):  # 从左到右扫描数组
            if x:  # 0 不参与配对
                ans = min(ans, i - last[3 - x])  # 用配对值 3 - x 的上次出现位置更新最小距离
                last[x] = i  # 更新当前值的最新下标
        return -1 if ans > n else ans  # 没有找到配对则返回 -1
