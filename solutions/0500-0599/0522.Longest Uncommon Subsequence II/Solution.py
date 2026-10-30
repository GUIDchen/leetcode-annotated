# 题目：522. 最长特殊序列 II（Longest Uncommon Subsequence II）
# 思路：答案一定来自某个完整字符串；某串若是其它串的子序列就不合法，在合法串中取最长。
# 时间复杂度：O(n²·L)，每对字符串做一次双指针子序列判断；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findLUSlength(self, strs: List[str]) -> int:  # strs：字符串列表；返回最长特殊序列长度，没有则返回 -1
        def check(s: str, t: str):  # 内层辅助函数：判断 s 是否为 t 的子序列
            i = j = 0  # 两个指针：i 指向 s、j 指向 t，都从 0 开始
            while i < len(s) and j < len(t):  # 任一字符串走完就结束扫描
                if s[i] == t[j]:  # 字符相同表示匹配到 s 的一个字符
                    i += 1  # s 的指针前进，消耗掉这次匹配
                j += 1  # 无论是否匹配，t 的指针每轮都要前进
            return i == len(s)  # i 走到 len(s) 说明 s 的全部字符都在 t 中按序出现

        ans = -1  # ans 记录最大长度，-1 表示暂时没有答案
        for i, s in enumerate(strs):  # 枚举每个候选串 s 及其下标 i
            for j, t in enumerate(strs):  # 与所有其它串 t 比较
                if i != j and check(s, t):  # 跳过自己，并检查 s 是否被 t 包含
                    break  # s 是 t 的子序列而不合法，跳出内层循环
            else:  # for-else：内层循环没有被 break 时才执行
                ans = max(ans, len(s))  # 没有 break 说明 s 特殊，用它的长度更新答案
        return ans  # 返回最大的合法长度
