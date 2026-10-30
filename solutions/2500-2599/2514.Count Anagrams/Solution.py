# 题目：2514. 统计同位异构字符串数目（Count Anagrams）
# 思路：各单词的异位词数互相独立，答案是各单词方案数之积；长度 L、各字母计数为 c 的单词有 L! / ∏c! 种排列。
# 时间复杂度：O(|s| + log mod)，一次遍历加一次求模逆；空间复杂度：O(1) 额外空间（忽略输入串本身）。
class Solution:  # LeetCode 约定的题解类
    def countAnagrams(self, s: str) -> int:  # s 是空格分隔的单词串
        mod = 10**9 + 7  # 取模常数
        ans = mul = 1  # ans 累积长度阶乘，mul 累积重复字母计数阶乘
        for w in s.split():  # 按空白切分，逐个单词统计
            cnt = Counter()  # 当前单词的字母计数器
            for i, c in enumerate(w, 1):  # 下标从 1 开始，i 直接当作阶乘的乘数
                cnt[c] += 1  # 当前字母出现次数加一
                mul = mul * cnt[c] % mod  # 该字母第几次出现就乘几，累乘得 ∏c!
                ans = ans * i % mod  # 累乘 1⋯L 得到长度阶乘 L!
        return ans * pow(mul, -1, mod) % mod  # 用模逆把除以 ∏c! 变成乘 ∏c! 的逆元
