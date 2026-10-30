# 题目：548. 将数组分割成和相等的子数组（Split Array with Equal Sum）🔒
# 思路：前缀和 O(1) 求区间和，枚举第二段右端点 j；用集合记下能与 j 凑出相等前两段的段和，再从右侧枚举 k 检查后两段是否相等且该和已在集合中。
# 时间复杂度：O(n^2)，外层枚举 j、内层分别枚举 i 与 k；空间复杂度：O(n)，前缀和数组与集合。
class Solution:  # LeetCode 约定的题解类
    def splitArray(self, nums: List[int]) -> bool:  # 判断能否把数组切成四段非空子数组且四段和相等
        n = len(nums)  # 数组长度 n
        s = [0] * (n + 1)  # 前缀和数组：s[i] 表示前 i 个元素之和
        for i, v in enumerate(nums):  # 遍历数组，同时取得下标 i 与元素值 v
            s[i + 1] = s[i] + v  # 递推得到前缀和
        for j in range(3, n - 3):  # 枚举第二段右端点 j：左右各留至少 3 个元素才放得下四段
            seen = set()  # 记录能与 j 组成相等前两段的段和
            for i in range(1, j - 1):  # 枚举前两段的切点 i（第一段 [0, i-1]，第二段 [i+1, j]）
                if s[i] == s[j] - s[i + 1]:  # 第一段和 s[i] 等于第二段和 s[j]-s[i+1]
                    seen.add(s[i])  # 这个段和可行，记入集合
            for k in range(j + 2, n - 1):  # 枚举后两段的切点 k（第三段 [j+1, k-1]，第四段 [k+1, n-1]）
                if s[n] - s[k + 1] == s[k] - s[j + 1] and s[n] - s[k + 1] in seen:  # 后两段之和相等，且该和在前两段里也出现过（四段全等）
                    return True  # 找到合法切法，立即返回
        return False  # 所有切法都不满足
