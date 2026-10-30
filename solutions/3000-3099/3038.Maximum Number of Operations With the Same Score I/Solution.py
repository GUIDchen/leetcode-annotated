# 题目：3038. 相同分数的最大操作数目 I（Maximum Number of Operations With the Same Score I）
# 思路：所有操作的分数都必须相同，首两个元素之和定下目标分数，之后每两个一组从前往后检查是否仍等于该分数。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个局部变量。
class Solution:  # LeetCode 约定的题解类
    def maxOperations(self, nums: List[int]) -> int:  # nums 是输入数组，长度至少为 2
        s = nums[0] + nums[1]  # 第一次操作的分数就确定了后续所有操作必须相同的目标分数
        ans, n = 0, len(nums)  # ans 记录操作次数，n 是数组长度
        for i in range(0, n, 2):  # 每两个元素一组，i 是当前待删除那一对的首个下标
            if i + 1 == n or nums[i] + nums[i + 1] != s:  # 剩余不足两个元素，或这一对的分数与目标不同
                break  # 无法继续操作，立即结束
            ans += 1  # 这一对可以删除，操作次数加一
        return ans  # 返回最多可执行的操作次数
