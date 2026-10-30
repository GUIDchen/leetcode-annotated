# 题目：2562. 找出数组的串联值（Find the Array Concatenation Value）
# 核心思路：双指针从两端向中间，把右值转成字符串拼到左值字符串后面再转回整数累加；正中间元素单独加上。
# 时间复杂度：O(n log M)，每个元素只被拼接一次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findTheArrayConcVal(self, nums: List[int]) -> int:  # nums：输入数组
        ans = 0  # 串联值总和
        i, j = 0, len(nums) - 1  # i 是左指针，j 是右指针
        while i < j:  # 左右指针尚未相遇，每次拼一对
            ans += int(str(nums[i]) + str(nums[j]))  # 转字符串首尾拼接后调用 int 还原成整数，累加到答案
            i, j = i + 1, j - 1  # 左指针右移、右指针左移
        if i == j:  # 数组长度为奇数，正中间还剩一个元素
            ans += nums[i]  # 中间元素直接累加
        return ans  # 返回最终串联值
