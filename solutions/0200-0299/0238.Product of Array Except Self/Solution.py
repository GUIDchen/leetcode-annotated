# 题目：238. 除了自身以外数组的乘积（Product of Array Except Self）
# 思路：两趟前后缀积。第一趟让 ans[i] 等于 i 左侧所有元素的乘积，第二趟从右往左再乘上右侧所有元素的乘积。
# 时间复杂度：O(n)，两趟线性遍历；空间复杂度：O(1)，除返回数组外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def productExceptSelf(self, nums: List[int]) -> List[int]:  # nums 是输入数组，返回除自身以外所有元素的乘积
        n = len(nums)  # 数组长度
        ans = [0] * n  # 结果数组，先全部初始化为 0
        left = right = 1  # 左右两侧的累积乘积，初值取乘法单位元 1
        for i, x in enumerate(nums):  # 第一趟从左到右，同时拿到下标 i 与元素 x
            ans[i] = left  # 先只写入 i 左侧所有元素的乘积
            left *= x  # 再把 x 并入 left，供下一个下标使用
        for i in range(n - 1, -1, -1):  # 第二趟从右到左遍历每个下标
            ans[i] *= right  # 左侧乘积乘上右侧乘积，得到除自身以外的乘积
            right *= nums[i]  # 把当前元素并入 right，供更左边一个位置使用
        return ans  # 返回结果数组
