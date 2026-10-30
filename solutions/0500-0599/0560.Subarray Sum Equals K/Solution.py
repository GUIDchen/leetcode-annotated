# 题目：560. 和为 K 的子数组（Subarray Sum Equals K）
# 核心思路：前缀和 + 哈希计数，走到每个位置时把「等于 s-k 的历史前缀和次数」累加进答案。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，哈希表最多保存 n 个前缀和。
class Solution:  # LeetCode 约定的题解类
    def subarraySum(self, nums: List[int], k: int) -> int:  # nums 为整数数组（可含负数），k 为目标和，返回和为 k 的连续子数组个数
        cnt = Counter({0: 1})  # 前缀和计数器，{0: 1} 代表空前缀，使从下标 0 开始的子数组也能被统计
        ans = s = 0  # ans 记录答案个数，s 是当前前缀和，用链式赋值同时初始化
        for x in nums:  # 逐个元素遍历
            s += x  # 累加当前元素，得到新的前缀和
            ans += cnt[s - k]  # 历史前缀和中等于 s-k 的次数，就是以当前位置结尾且和为 k 的子数组个数
            cnt[s] += 1  # 当前前缀和的计数加一，供后续位置使用
        return ans  # 返回统计结果
