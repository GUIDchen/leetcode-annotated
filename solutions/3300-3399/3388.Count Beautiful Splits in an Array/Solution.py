# 题目：3388. 统计数组中的美丽分割（Count Beautiful Splits in an Array）
# 思路：先 DP 求出任意两个后缀的最长公共前缀 lcp[i][j]，再枚举两个切点 i、j，用 lcp 判断第一段或第二段是否为后一段的前缀。
# 时间复杂度：O(n^2)；空间复杂度：O(n^2)，保存 lcp 表。
class Solution:  # LeetCode 约定的题解类
    def beautifulSplits(self, nums: List[int]) -> int:  # nums 是输入数组，返回美丽分割的方案数
        n = len(nums)  # 数组长度
        lcp = [[0] * (n + 1) for _ in range(n + 1)]  # lcp[i][j]：从 i 开始与从 j 开始的后缀的最长公共前缀长度
        for i in range(n - 1, -1, -1):  # 从后往前推，保证 lcp[i+1][j+1] 已经算好
            for j in range(n - 1, i - 1, -1):  # j 从 n-1 递减到 i+1，保证 j > i
                if nums[i] == nums[j]:  # 两个位置字符相同才能延长公共前缀
                    lcp[i][j] = lcp[i + 1][j + 1] + 1  # 长度等于后一位的 lcp 加一
        ans = 0  # ans：美丽分割的方案数
        for i in range(1, n - 1):  # 枚举第一个切点 i，切成 nums[0..i) 与 nums[i..n) 两部分
            for j in range(i + 1, n):  # 枚举第二个切点 j，把后半段再切一刀
                a = i <= j - i and lcp[0][i] >= i  # 情况一：第一段是第二段的前缀（第一段长度不超过第二段且 lcp >= i）
                b = j - i <= n - j and lcp[i][j] >= j - i  # 情况二：第二段是第三段的前缀（第二段长度不超过第三段且 lcp >= j-i）
                ans += int(a or b)  # 两种情况任一成立就计入答案
        return ans  # 返回方案数
