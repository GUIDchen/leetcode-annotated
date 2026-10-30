# 题目：3258. 统计满足 K 约束的子字符串数量 I（Count Substrings That Satisfy K-Constraint I）
# 思路：滑动窗口。窗口 [l, r] 内 '0' 与 '1' 的个数都不超过 k 时才合法；右端每扩张一格，若两种字符同时超过 k 就让左端收缩，此时以 r 结尾的合法子串恰有 r-l+1 个，累加即为答案。
# 时间复杂度：O(n)，l 与 r 各自只向右移动；空间复杂度：O(1)，只用一个长度为 2 的计数数组。
class Solution:  # LeetCode 约定的题解类
    def countKConstraintSubstrings(self, s: str, k: int) -> int:  # s 只含 '0' 和 '1'，k 为每种字符个数上限；返回满足 K 约束的子串数量
        cnt = [0, 0]  # cnt[0]、cnt[1] 分别统计窗口内 '0' 与 '1' 的个数
        ans = l = 0  # ans 累计答案，l 为滑动窗口左端点（链式赋值）
        for r, x in enumerate(map(int, s)):  # r 为右端点，x 为当前字符转成的整数 0/1
            cnt[x] += 1  # 当前字符计入对应计数
            while cnt[0] > k and cnt[1] > k:  # 两种字符同时超过 k 时窗口不合法，需要收缩左端点
                cnt[int(s[l])] -= 1  # 左端字符移出窗口
                l += 1  # 左端点右移一位
            ans += r - l + 1  # 以 r 结尾、起点在 [l, r] 内的子串都合法，共 r-l+1 个
        return ans  # 返回满足 K 约束的子字符串总数
