# 题目：2340. 生成有效数组的最少交换次数（Minimum Adjacent Swaps to Make a Valid Array）
# 思路：有效数组只要求队首是最小值、队尾是最大值，所以只需把最小值移到最前、最大值移到最后；贪心取最小值最左下标 i 与最大值最右下标 j，答案为 i + (len-1-j)，i > j 时两条路径交叉、有一次交换被共用，需减 1。
# 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，仅几个下标变量。
class Solution:  # LeetCode 约定的题解类
    def minimumSwaps(self, nums: List[int]) -> int:  # nums：输入数组；返回最少的相邻交换次数
        i = j = 0  # i 记录最小值的最左下标，j 记录最大值的最右下标
        for k, v in enumerate(nums):  # 一次遍历，同时拿到下标 k 与元素值 v
            if v < nums[i] or (v == nums[i] and k < i):  # 更小，或值相同但更靠左，就更新 i
                i = k  # 贪心取最小值的最左出现位置，移到队首的步数最少
            if v >= nums[j] or (v == nums[j] and k > j):  # v >= 且同值只看下标更大，等价于“更大或同值更靠右”，所以更新 j
                j = k  # 贪心取最大值的最右出现位置，移到队尾的步数最少
        return 0 if i == j else i + len(nums) - 1 - j - (i > j)  # 最值重合返回 0；否则 i 步换到队首、len-1-j 步换到队尾，i > j 时减掉被共用的那一次交换
