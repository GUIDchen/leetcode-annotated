# 题目：3334. 数组的最大因子得分（Find the Maximum Factor Score of Array）
# 思路：预处理后缀 GCD/LCM，再从前往后维护前缀 GCD/LCM；枚举删除位置 i，用左前缀与右后缀的 GCD、LCM 相乘得到删除后的得分，同时保留不删除的情形。
# 时间复杂度：O(n log V)，V 为元素最大值；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, nums: List[int]) -> int:  # nums 是输入数组；返回删除至多一个元素后的最大因子得分
        n = len(nums)  # 数组长度
        suf_gcd = [0] * (n + 1)  # suf_gcd[i] 表示 nums[i:] 的 GCD
        suf_lcm = [0] * n + [1]  # suf_lcm[i] 表示 nums[i:] 的 LCM，末尾补 1 作为空后缀的单位元
        for i in range(n - 1, -1, -1):  # 从右往左构建后缀
            suf_gcd[i] = gcd(suf_gcd[i + 1], nums[i])  # 当前元素与右侧后缀的 GCD
            suf_lcm[i] = lcm(suf_lcm[i + 1], nums[i])  # 当前元素与右侧后缀的 LCM
        ans = suf_gcd[0] * suf_lcm[0]  # 不删除任何元素时的得分，作为答案初值
        pre_gcd, pre_lcm = 0, 1  # 前缀 GCD 初值 0、前缀 LCM 初值 1，分别是两种运算的单位元
        for i, x in enumerate(nums):  # 枚举被删除的元素下标 i
            ans = max(ans, gcd(pre_gcd, suf_gcd[i + 1]) * lcm(pre_lcm, suf_lcm[i + 1]))  # 删除 i 后由左前缀与右后缀合并出整体 GCD 与 LCM
            pre_gcd = gcd(pre_gcd, x)  # 把 x 并入左前缀 GCD
            pre_lcm = lcm(pre_lcm, x)  # 把 x 并入左前缀 LCM
        return ans  # 返回最大因子得分
