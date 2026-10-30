# 题目：1759. 统计同质子字符串的数目（Count Number of Homogenous Substrings）
# 思路：按连续相同字符分段，长度为 cnt 的段贡献 cnt*(cnt+1)/2 个子串，逐段累加并取模。
# 时间复杂度：O(n)，i 与 j 都只向右前进；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countHomogenous(self, s: str) -> int:  # s：只含小写字母的字符串
        mod = 10**9 + 7  # 题目要求的取模常数
        i, n = 0, len(s)  # i 是当前连续段的起点，n 是字符串长度
        ans = 0  # 累计答案
        while i < n:  # 还有未处理的连续段
            j = i  # 从段起点开始向右探测
            while j < n and s[j] == s[i]:  # 只要字符与段首相同就继续右移
                j += 1  # 右移探测指针
            cnt = j - i  # 这一段连续相同字符的长度
            ans += (1 + cnt) * cnt // 2  # 长度为 cnt 的段贡献 cnt*(cnt+1)/2 个同质子串
            ans %= mod  # 立即取模，避免数值膨胀
            i = j  # 跳到下一段的起点
        return ans  # 返回总数目
