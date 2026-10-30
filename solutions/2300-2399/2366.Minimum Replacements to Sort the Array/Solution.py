# 题目：2366. 将数组排序的最少替换次数（Minimum Replacements to Sort the Array）
# 思路：从右往左贪心，维护右侧最小值 mx；当前元素过大就尽量均分成 k = ceil(nums[i] / mx) 份，让最左一份尽可能大。
# 时间复杂度：O(n)，一次逆序扫描；空间复杂度：O(1)，只用到常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def minimumReplacement(self, nums: List[int]) -> int:  # nums 是输入数组，返回最少的替换次数
        ans = 0  # 替换次数总和，Python 整数不会溢出
        n = len(nums)  # 数组长度
        mx = nums[-1]  # 从最后一个元素开始，它是右侧已经确定的最小上界
        for i in range(n - 2, -1, -1):  # 从右往左遍历每个元素
            if nums[i] <= mx:  # 当前元素不大于右侧最小值，单调性已满足，无需拆分
                mx = nums[i]  # 更新右侧最小值，供更左边的元素参考
                continue  # 直接处理前一个元素
            k = (nums[i] + mx - 1) // mx  # 向上取整：至少切成 k 份才能让每份都不超过 mx
            ans += k - 1  # 切成 k 份需要 k - 1 次替换操作
            mx = nums[i] // k  # 平均分配后最左（最小）的一份就是向下取整的结果
        return ans  # 返回最少替换次数
