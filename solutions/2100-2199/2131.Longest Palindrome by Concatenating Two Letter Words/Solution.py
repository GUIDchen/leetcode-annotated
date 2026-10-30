# 题目：2131. 连接两字母单词得到的最长回文串（Longest Palindrome by Concatenating Two Letter Words）
# 思路：用 Counter 统计每种两字母单词的出现次数；互为反序的单词成对放在回文串两端，两个字母相同的单词成对占两侧，最多留一个放中心。
# 时间复杂度：O(n + U)，n 为单词数、U 为不同单词数；空间复杂度：O(U)，Counter 保存每种单词的计数。
class Solution:  # LeetCode 约定的题解类
    def longestPalindrome(self, words: List[str]) -> int:  # words：由两字母单词组成的输入列表
        cnt = Counter(words)  # 统计每种单词出现的次数，缺键时按 0 处理
        ans = x = 0  # ans：已确定的字符总数；x：出现奇数次的「两字母相同」单词个数
        for k, v in cnt.items():  # 遍历每种单词 k 及其次数 v
            if k[0] == k[1]:  # 情况一：形如 "aa"，它自己就是回文片段
                x += v & 1  # 出现奇数次时多出 1 个，可以留作回文中心
                ans += v // 2 * 2 * 2  # 成对的 "aa" 左右各放一个，每对贡献 4 个字符
            else:  # 情况二：普通单词，尝试与它的反序配对
                ans += min(v, cnt[k[::-1]]) * 2  # 取与反序单词次数的较小值配对，当前方向计一半
        ans += 2 if x else 0  # 只要存在多余的 "aa"，就能在正中间再放一个，长度增加 2
        return ans  # 返回可以拼出的最长回文串长度
