# 题目：1513. 仅含 1 的子串数（Number of Substrings With Only 1s）
# 思路：cur 记录以当前字符结尾的全 1 段长度，该位置新增 cur 个仅含 1 的子串，累加取模。
# 时间复杂度：O(n)，单次扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numSub(self, s: str) -> int:  # s：只含 '0' 和 '1' 的字符串，返回仅含 1 的子串个数对 1e9+7 取模
        mod = 10**9 + 7  # mod：题目要求的取模常数
        ans = cur = 0  # ans：答案；cur：以当前字符结尾的全 1 连续段长度（链式赋值同时初始化）
        for c in s:  # 逐字符扫描
            if c == "0":  # 遇到 '0'，连续段被打断
                cur = 0  # 段长清零
            else:  # 否则当前字符是 '1'
                cur += 1  # 连续段长度加一
                ans = (ans + cur) % mod  # 以当前位置结尾的仅含 1 的子串恰有 cur 个，累加并取模
        return ans  # 返回答案
