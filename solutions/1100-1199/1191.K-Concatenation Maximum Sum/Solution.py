# 题目：1191. K 次串联后最大子数组之和（K-Concatenation Maximum Sum）
# 思路：一次扫描求出单段最大子数组和、最大前缀和、最大后缀和与总和的符号，再按 k==1、跨两段、跨中间整段三种情况取最大。
# 时间复杂度：O(n)，只扫一遍原数组；空间复杂度：O(1)，常数个变量。
class Solution:  # LeetCode 约定的题解类
    def kConcatenationMaxSum(self, arr: List[int], k: int) -> int:  # arr 重复 k 次后求最大子数组和，结果对 1e9+7 取模
        s = mx_pre = mi_pre = mx_sub = 0  # s 是前缀和；mx_pre/mi_pre 是前缀和最值；mx_sub 是单段内最大子数组和
        for x in arr:  # 只需扫描原数组一遍
            s += x  # 累加前缀和
            mx_pre = max(mx_pre, s)  # 更新最大前缀和
            mi_pre = min(mi_pre, s)  # 更新最小前缀和
            mx_sub = max(mx_sub, s - mi_pre)  # 当前前缀和减去历史最小前缀和 = 以当前位置结尾的最大子数组和
        ans = mx_sub  # k == 1 时答案就是单段最大值
        mod = 10**9 + 7  # 题目要求的模数
        if k == 1:  # 只有一段，无法跨段拼接
            return ans % mod  # 直接取模返回
        mx_suf = s - mi_pre  # 最大后缀和 = 总和 - 最小前缀和
        ans = max(ans, mx_pre + mx_suf)  # 跨两段：首段最大前缀 + 第二段最大后缀
        if s > 0:  # 总和为正时，中间夹着的整段都值得计入
            ans = max(ans, (k - 2) * s + mx_pre + mx_suf)  # 首段前缀 + 中间 (k-2) 个整段 + 末段后缀
        return ans % mod  # 取模后返回
