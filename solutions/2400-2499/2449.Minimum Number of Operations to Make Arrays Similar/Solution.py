# 题目：2449. 使数组相似的最少操作次数（Minimum Number of Operations to Make Arrays Similar）
# 思路：两个数组都按「奇偶性优先、大小其次」排序，奇数只与奇数配对、偶数只与偶数配对，逐位绝对差之和再整除 4。
# 时间复杂度：O(n log n)，两次排序主导；空间复杂度：O(n)，排序需要的临时空间。
class Solution:  # LeetCode 约定的题解类
    def makeSimilar(self, nums: List[int], target: List[int]) -> int:  # nums：待调整数组；target：目标数组
        nums.sort(key=lambda x: (x & 1, x))  # 元组键先比奇偶位（偶数 0 在前、奇数 1 在后）再比大小，使同奇偶元素按序聚在一起
        target.sort(key=lambda x: (x & 1, x))  # target 用相同的排序规则，保证两个数组的同奇偶分组一一对应
        return sum(abs(a - b) for a, b in zip(nums, target)) // 4  # 一次操作让两个元素各变 2，最多消去 4 点总差，故总和整除 4
