# 题目：2016. 增量元素之间的最大差值（Maximum Difference Between Increasing Elements）
# 思路：一次遍历，mi 维护已扫描部分的最小值；当前元素比 mi 大就更新答案，否则让它成为新的最小值。
# 时间复杂度：O(n)，只遍历一次；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumDifference(self, nums: List[int]) -> int:  # nums：整数列表；返回满足 i < j 且 nums[i] < nums[j] 的最大差值，不存在则返回 -1
        mi = inf  # mi 保存已扫描元素的最小值，初值取正无穷（inf 由判题环境提供）
        ans = -1  # ans 保存最大差值，-1 表示不存在
        for x in nums:  # 顺序遍历每个元素
            if x > mi:  # 当前元素严格大于之前的最小值，构成合法数对
                ans = max(ans, x - mi)  # 更新最大差值
            else:  # 否则当前元素不大于 mi
                mi = x  # 把当前元素作为新的最小值
        return ans  # 返回最大差值，可能为 -1
