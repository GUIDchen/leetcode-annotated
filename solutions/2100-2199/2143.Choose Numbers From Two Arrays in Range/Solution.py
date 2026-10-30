# 题目：2143. 在两个数组的区间中选取数字（Choose Numbers From Two Arrays in Range）
# 思路：按区间右端点做 DP，f[i][j] 表示以 i 结尾、每个位置选 nums1 记 +、选 nums2 记 -、偏移后总和为 j 的区间个数；总和为 0 的计入答案。
# 时间复杂度：O(n (s1 + s2))，n 为数组长度，s1/s2 为两数组元素和；空间复杂度：O(n (s1 + s2))。
class Solution:  # LeetCode 约定的题解类
    def countSubranges(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个等长数组，区间内每个位置各取一个数
        n = len(nums1)  # 数组长度
        s1, s2 = sum(nums1), sum(nums2)  # 两个数组各自的总和：s1 为加法方向的上界，s2 作为偏移量基准
        f = [[0] * (s1 + s2 + 1) for _ in range(n)]  # 二维 DP 表：f[i][j] 表示以 i 结尾、偏移后总和为 j 的区间个数
        ans = 0  # 累计合法区间（总和为 0）的数量
        mod = 10**9 + 7  # 方案数很多，按 1e9+7 取模
        for i, (a, b) in enumerate(zip(nums1, nums2)):  # 枚举右端点 i，同时取出当前位置的两个候选值 a、b
            f[i][a + s2] += 1  # 区间只含 i 且选 nums1：总和为 a（加 s2 偏移）
            f[i][-b + s2] += 1  # 区间只含 i 且选 nums2：总和为 -b（加 s2 偏移）
            if i:  # 长度大于 1 的区间要从右端点 i-1 转移
                for j in range(s1 + s2 + 1):  # 枚举所有可能的偏移后总和
                    if j >= a:  # 前一段总和 j-a 不越下界才可以转移
                        f[i][j] = (f[i][j] + f[i - 1][j - a]) % mod  # 在 i 处选 nums1，总和增加 a
                    if j + b < s1 + s2 + 1:  # 前一段总和 j+b 不越上界（等价于 j + b <= s1 + s2）
                        f[i][j] = (f[i][j] + f[i - 1][j + b]) % mod  # 在 i 处选 nums2，总和减少 b
            ans = (ans + f[i][s2]) % mod  # 偏移 s2 对应真实总和 0，把以 i 结尾的合法区间计入答案
        return ans  # 返回答案
