# 题目：2506. 统计相似字符串对的数目（Count Pairs Of Similar Strings）
# 思路：把每个字符串压成 26 位「字母是否出现过」的位掩码，掩码相同即相似；用 Counter 累计同掩码的历史出现次数，逐个累加配对数。
# 时间复杂度：O(L)，L 为所有字符串字符总数；空间复杂度：O(n)，Counter 最多保存 n 个不同的掩码。
class Solution:  # LeetCode 约定的题解类
    def similarPairs(self, words: List[str]) -> int:  # words 是输入字符串数组，返回相似字符串对的数目
        ans = 0  # 答案计数器：累计相似下标对的个数
        cnt = Counter()  # 计数器：键是位掩码，值是该掩码此前出现的次数
        for s in words:  # 依次处理每一个字符串
            x = 0  # 26 位掩码：记录该字符串中出现过哪些小写字母
            for c in map(ord, s):  # 把每个字符转成 ASCII 码再逐个遍历
                x |= 1 << (c - ord("a"))  # 把对应字母的位置 1；重复字母不会影响结果
            ans += cnt[x]  # 此前每个同掩码的字符串都与当前串相似，先累加旧次数
            cnt[x] += 1  # 再把当前字符串的掩码计数加一，供后面的字符串配对
        return ans  # 返回相似字符串对的总数
