# 题目：15. 三数之和（3Sum）
# 思路：排序后固定第一个数，用左右双指针夹逼找剩余两数；nums[i] > 0 时提前 break，靠相邻比较跳过重复解。
# 时间复杂度：O(n^2)，外层枚举 + 内层双指针；空间复杂度：O(1)，除返回值外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def threeSum(self, nums: List[int]) -> List[List[int]]:  # nums 是输入数组
        nums.sort()  # 先排序，才能用双指针并方便去重
        n = len(nums)  # 数组长度
        ans = []  # 收集所有不重复的三元组
        for i in range(n - 2):  # 枚举第一个数，后面至少还要留两个位置
            if nums[i] > 0:  # 排序后当前数已大于 0
                break  # 后面的数更大，不可能再凑成和为 0
            if i and nums[i] == nums[i - 1]:  # 与上一个数相同
                continue  # 跳过，避免重复三元组
            j, k = i + 1, n - 1  # 左右指针指向 i 右侧区间的最小值与最大值
            while j < k:  # 两指针未相遇就继续
                x = nums[i] + nums[j] + nums[k]  # 当前三数之和
                if x < 0:  # 和偏小
                    j += 1  # 左指针右移取更大的值
                elif x > 0:  # 和偏大
                    k -= 1  # 右指针左移取更小的值
                else:  # 恰好为 0
                    ans.append([nums[i], nums[j], nums[k]])  # 记录这一组三元组
                    j, k = j + 1, k - 1  # 两指针同时向内收缩
                    while j < k and nums[j] == nums[j - 1]:  # 跳过左指针处的重复值
                        j += 1
                    while j < k and nums[k] == nums[k + 1]:  # 跳过右指针处的重复值
                        k -= 1
        return ans  # 返回所有不重复的三元组
