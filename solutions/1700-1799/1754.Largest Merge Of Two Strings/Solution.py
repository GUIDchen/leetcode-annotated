# 题目：1754. 构造字典序最大的合并字符串（Largest Merge Of Two Strings）
# 思路：双指针，每一步比较两串剩余后缀的字典序（Python 切片可直接比较），取更大一侧的首字符。
# 时间复杂度：O((m+n)^2)，每次切片比较是 O(m+n)；空间复杂度：O(m+n)，列表 ans 与切片临时串。
class Solution:  # LeetCode 约定的题解类
    def largestMerge(self, word1: str, word2: str) -> str:  # 两个待合并的字符串
        i = j = 0  # i、j 分别是 word1、word2 中下一个待取字符的下标
        ans = []  # 用列表收集结果字符，最后一次性 join，避免字符串反复拼接
        while i < len(word1) and j < len(word2):  # 两串都还有字符时继续贪心选择
            if word1[i:] > word2[j:]:  # 比较两个剩余后缀：word1 的后缀更大就取 word1 的首字符
                ans.append(word1[i])  # 把 word1 的当前字符放进结果
                i += 1  # word1 指针后移
            else:  # 否则（word2 后缀更大或相等）取 word2 的首字符
                ans.append(word2[j])  # 把 word2 的当前字符放进结果
                j += 1  # word2 指针后移
        ans.append(word1[i:])  # word2 用完了，把 word1 剩下的整段后缀接上
        ans.append(word2[j:])  # word1 用完了（或两者都已空），把 word2 剩下的整段后缀接上
        return "".join(ans)  # 拼接所有片段，得到最终答案
