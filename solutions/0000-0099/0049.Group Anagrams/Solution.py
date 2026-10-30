# 题目：49. 字母异位词分组（Group Anagrams）
# 核心思路：把每个字符串按字符排序，互为异位词的串排序后会完全相同，用它当哈希表的键就能自然分组。
# 时间复杂度：O(n·k log k)，k 为串长，主要开销是排序；空间复杂度：O(n·k)，存放所有字符串。
class Solution:  # LeetCode 约定的题解类
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:  # strs 是字符串数组，把互为字母异位词的串分到同一组
        d = defaultdict(list)  # 哈希表：键是排序后的字符串（异位词共用的签名），值默认是空列表
        for s in strs:  # 逐个处理输入字符串
            k = ''.join(sorted(s))  # 排序后异位词得到同一串代码，正好当作分组键
            d[k].append(s)  # 用这个键把原串追加到对应分组里
        return list(d.values())  # 取出所有分组并转成列表返回，顺序不影响判题
