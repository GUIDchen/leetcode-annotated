# 题目：3781. 二进制交换后的最大分数（Maximum Score After Binary Swaps）
# 核心思路：操作只能把 '1' 向左移动，第 k 个 '1' 最终只能落在它原位置或更左侧；从左到右扫描，用大根堆维护前缀中的数字，遇到 s[i]=='1' 就弹出堆顶作为该位置的值。
# 复杂度：时间 O(n log n)，每个元素至多入堆出堆各一次；空间 O(n)，堆最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, nums: List[int], s: str) -> int:  # 长度为 n 的 nums 与 01 串 s，求操作后所有 s[i]=='1' 位置上的 nums[i] 之和的最大值
        ans = 0  # 累加答案，初值 0
        pq = []  # 用取负的方式模拟大根堆，堆顶即当前前缀最大值
        for x, c in zip(nums, s):  # 从左到右扫描，堆里是前缀中尚未分配给某个 '1' 的数字
            heappush(pq, -x)  # 把 -x 入堆，堆顶保存当前前缀的最大值
            if c == "1":  # s[i] 为 '1' 时，把前缀中最大的数字分配给这个位置
                ans -= heappop(pq)  # 弹出堆顶（负数）并取反后累加进答案
        return ans  # 返回最大得分
