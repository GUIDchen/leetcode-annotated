# 题目：1822. 数组元素积的符号（Sign of the Product of an Array）
# 核心思路：不真算乘积以免溢出，只维护符号：遇到 0 立刻返回 0，遇到负数就把符号乘 -1。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def arraySign(self, nums: List[int]) -> int:  # 返回数组元素积的符号：1、0 或 -1
        ans = 1  # ans 只记录符号，取值 1 或 -1
        for v in nums:  # 遍历数组中的每个元素
            if v == 0:  # 出现 0 时乘积必为 0
                return 0  # 立即返回 0，后面的元素无需再看
            if v < 0:  # 遇到负数，符号翻转
                ans *= -1  # 乘 -1 即翻转正负号
        return ans  # 返回最终符号
