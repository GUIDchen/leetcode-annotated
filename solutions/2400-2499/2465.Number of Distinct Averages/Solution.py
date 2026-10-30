# 题目：2465. 不同的平均值数目（Number of Distinct Averages）
# 核心思路：排序后每次取最小值与最大值配对，用集合统计这些配对的和；配对个数固定，和相同与平均值相同等价，用整数和避免浮点误差。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，集合最多存 n/2 个和。
class Solution:  # LeetCode 约定的题解类
    def distinctAverages(self, nums: List[int]) -> int:  # nums：输入数组；返回不同平均值的个数
        nums.sort()  # 就地排序，方便首尾配对：最小值配最大值
        return len(set(nums[i] + nums[-i - 1] for i in range(len(nums) >> 1)))  # 生成 n//2 对首尾元素之和，set 去重后取个数（和相同即平均值相同）
