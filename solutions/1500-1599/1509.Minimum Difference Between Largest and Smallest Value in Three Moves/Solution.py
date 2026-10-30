# 题目：1509. 三次操作后最大值与最小值的最小差（Minimum Difference Between Largest and Smallest Value in Three Moves）
# 思路：排序后，3 次操作等价于删掉「最小的 l 个 + 最大的 3-l 个」，枚举 l=0..3 取剩余区间首尾差的最小值。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(1)（排序为原地进行）。
class Solution:  # LeetCode 约定的题解类
    def minDifference(self, nums: List[int]) -> int:  # nums：输入数组，允许把至多 3 个元素替换成任意值
        n = len(nums)  # n：数组长度
        if n < 5:  # 不足 5 个元素时，3 次操作足以把所有元素调成相同
            return 0  # 因此最小极差一定是 0，提前返回
        nums.sort()  # 原地升序排序，之后极差就是「尾 - 首」
        ans = inf  # ans：最小极差，初值取正无穷 inf
        for l in range(4):  # 枚举从最小值一侧替换掉的元素个数 l = 0,1,2,3
            r = 3 - l  # r：从最大值一侧替换掉的个数，保证 l + r = 3
            ans = min(ans, nums[n - 1 - r] - nums[l])  # 剩余区间为 [l, n-1-r]，它的首尾差是一种候选答案
        return ans  # 返回四种划分方案中的最小极差
