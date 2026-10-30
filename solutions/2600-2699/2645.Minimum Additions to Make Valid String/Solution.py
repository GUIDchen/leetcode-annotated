# 题目：2645. 构造有效字符串的最少插入数（Minimum Additions to Make Valid String）
# 思路：把 word 与循环串 "abc" 对齐，期望字符缺失就插入一个，匹配成功则前进；末尾再补齐循环串剩余部分。
# 时间复杂度：O(|word|)，每个字符均摊只处理一次；空间复杂度：O(1)，只用了常量个变量。
class Solution:  # LeetCode 约定的题解类
    def addMinimum(self, word: str) -> int:  # word：给定字符串；返回最少插入次数
        s = 'abc'  # 目标循环串 "abc"，s[i] 是当前期望的字符
        ans, n = 0, len(word)  # ans：插入次数；n：word 长度
        i = j = 0  # i 在 "abc" 上循环；j 在 word 上扫描
        while j < n:  # word 还没匹配完就继续
            if word[j] != s[i]:  # 当前字符不是期望字符，需要插入一个
                ans += 1  # 插入 s[i]，j 不动
            else:  # 当前字符恰好是期望字符
                j += 1  # 匹配成功，word 前进
            i = (i + 1) % 3  # 无论插入还是匹配，都推进到循环串的下一个字符
        if word[-1] != 'c':  # 末尾没有走到 'c'，剩余字符要补齐
            ans += 1 if word[-1] == 'b' else 2  # 'b' 缺 'c' 补 1 个；'a' 缺 'b','c' 补 2 个
        return ans  # 返回最少插入次数
