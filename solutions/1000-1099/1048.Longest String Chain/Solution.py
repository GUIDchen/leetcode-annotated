# 题目：1048. 最长字符串链（Longest String Chain）
# 思路：按长度升序排序后做动态规划，f[i] 为以 words[i] 结尾的最长链长；对每个更短的前驱用贪心双指针判断能否插入一个字符变过来。
# 时间复杂度：O(n^2 * L)，n 为单词数、L 为单词最大长度；空间复杂度：O(n)，一维 dp 数组。
class Solution:  # LeetCode 约定的题解类
    def longestStrChain(self, words: List[str]) -> int:  # words：单词表；返回最长字符串链的长度
        def check(a: str, b: str) -> bool:  # 判断 a 是否为 b 删掉一个字符后得到的串
            if len(a) + 1 != len(b):  # 长度必须恰好相差 1
                return False  # 长度不符直接否定
            i = 0  # i 为 a 中已经匹配到的位置
            for c in b:  # 按序遍历 b，尝试顺序匹配 a 的字符，多出的那个就是被插入的字符
                if i < len(a) and a[i] == c:  # 当前字符正好等于 a 的待匹配字符
                    i += 1  # 匹配成功，前进一位
            return i == len(a)  # a 被完整顺序匹配，说明 a 是 b 的子序列

        words.sort(key=len)  # 按长度升序排序，保证前驱一定排在当前单词前面
        n = len(words)  # 单词个数
        f = [1] * n  # f[i] 表示以 words[i] 结尾的最长链长，初始至少包含自己，故全为 1
        for i in range(n):  # 按长度从小到大依次转移
            for j in range(i):  # 枚举所有可能的前驱（长度不超过当前单词）
                if check(words[j], words[i]):  # 前驱能通过插入一个字符变成当前单词
                    f[i] = max(f[i], f[j] + 1)  # 用前驱的链长 + 1 更新当前最优
        return max(f)  # 所有单词中链长的最大值
