# 题目：2012. 数组美丽值求和（Sum of Beauty in the Array）
# 思路：先倒序求出后缀最小值表 right，再正序扫描并用 l 维护前缀最大值，按题目两类条件累加美丽值。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，right 列表保存后缀最小值。
class Solution:  # LeetCode 约定的题解类
    def sumOfBeauties(self, nums: List[int]) -> int:  # nums：整数列表；返回所有下标美丽值之和
        n = len(nums)  # n 为数组长度
        right = [nums[-1]] * n  # right[i] 用来保存 nums[i..n-1] 的最小值，先全部填成最后一个元素
        for i in range(n - 2, -1, -1):  # 从 n-2 开始、步长 -1 一直倒序到下标 0
            right[i] = min(right[i + 1], nums[i])  # 后缀最小值递推：当前元素与右侧后缀最小值的较小者
        ans = 0  # ans 累加所有下标的美丽值
        l = nums[0]  # l 维护 nums[0..i-1] 的最大值，初始为第一个元素
        for i in range(1, n - 1):  # 只遍历中间下标 1..n-2
            r = right[i + 1]  # r 是 nums[i+1..n-1] 的最小值
            if l < nums[i] < r:  # 第一类：严格大于左侧所有元素且严格小于右侧所有元素
                ans += 2  # 这种情况美丽值为 2
            elif nums[i - 1] < nums[i] < nums[i + 1]:  # 第二类：只要求严格大于左邻且严格小于右邻
                ans += 1  # 这种情况美丽值为 1
            l = max(l, nums[i])  # 把当前元素并入前缀最大值，供下一轮使用
        return ans  # 返回美丽值总和
