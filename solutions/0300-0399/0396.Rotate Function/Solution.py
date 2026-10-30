# 题目：396. 旋转函数（Rotate Function）
# 思路：先按定义算出 F(0)，再用递推式 F(i) = F(i-1) + sum - n·nums[n-i] 依次推出其余 F 值并取最大。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只保存当前 F 值、总和与答案。
class Solution:  # LeetCode 约定的题解类
    def maxRotateFunction(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有旋转方式中 F 的最大值
        f = sum(i * v for i, v in enumerate(nums))  # 按定义直接算出 F(0) = 0*nums[0] + 1*nums[1] + ...
        n, s = len(nums), sum(nums)  # n 是数组长度，s 是元素总和，供递推使用
        ans = f  # 答案先用 F(0) 初始化
        for i in range(1, n):  # 从 1 开始递推到 n-1
            f = f + s - n * nums[n - i]  # 递推式：F(i) = F(i-1) + sum - n * nums[n-i]
            ans = max(ans, f)  # 用当前 F 值更新最大值
        return ans  # 返回所有旋转函数值中的最大值
