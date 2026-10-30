# 题目：2913. 子数组不同元素数目的平方和 I（Subarrays Distinct Element Sum of Squares I）
# 思路：枚举子数组左端点，右端点逐步右移并维护窗口内不同元素个数，边扩边累加其平方。
# 时间复杂度：O(n^2)，枚举所有子数组；空间复杂度：O(n)，集合最多存 n 个不同元素。
class Solution:  # LeetCode 约定的题解类
    def sumCounts(self, nums: List[int]) -> int:  # nums 是输入数组；返回所有子数组『不同元素个数的平方』之和
        ans, n = 0, len(nums)  # ans 累加答案，n 是数组长度，用元组一次性赋值
        for i in range(n):  # 枚举子数组的左端点 i
            s = set()  # 集合保存当前子数组里出现过的数值，其长度就是不同元素个数
            for j in range(i, n):  # 枚举右端点 j，当前窗口为 nums[i..j]
                s.add(nums[j])  # 把 nums[j] 放进集合，重复元素会被自动去重
                ans += len(s) * len(s)  # 把当前窗口不同元素个数的平方计入答案
        return ans  # 返回所有子数组的平方和
