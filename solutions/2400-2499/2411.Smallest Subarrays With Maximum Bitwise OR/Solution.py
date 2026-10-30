# 题目：2411. 按位或最大的最小子数组长度（Smallest Subarrays With Maximum Bitwise OR）
# 思路：从右往左扫描，用 f[j] 记录第 j 位最近出现的下标；答案由所有出现过的位中距离最远的那一位决定。
# 时间复杂度：O(32n)，每个位置固定检查 32 位；空间复杂度：O(n)，用于存放答案数组（f 只占常数 32）。
class Solution:  # LeetCode 约定的题解类
    def smallestSubarrays(self, nums: List[int]) -> List[int]:  # nums 为输入数组，返回每个起点的最小长度
        n = len(nums)  # 数组长度
        ans = [1] * n  # 结果数组：每个位置的子数组至少包含自己，初值取 1
        f = [-1] * 32  # f[j] 记录第 j 位最近出现的下标，-1 表示尚未出现
        for i in range(n - 1, -1, -1):  # 从右往左遍历，保证右侧信息已经就绪
            t = 1  # 当前起点所需的最小长度，从只含自己开始
            for j in range(32):  # 逐位检查 32 个二进制位
                if (nums[i] >> j) & 1:  # 当前数的第 j 位是 1
                    f[j] = i  # 该位最近出现的下标更新为 i
                elif f[j] != -1:  # 当前数没有这一位，但右侧有元素带这一位
                    t = max(t, f[j] - i + 1)  # 必须延伸到 f[j]，才能把这一位纳入按位或
            ans[i] = t  # 记录当前起点的答案
        return ans  # 返回所有起点的最小子数组长度
