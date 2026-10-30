# 3460. 最多删除一次后的最长公共前缀 / Longest Common Prefix After at Most One Removal
# 核心思路：双指针同步扫描，字符不一致时消耗唯一一次删除机会（跳过 s 的当前字符），再次不一致即停止。
# 复杂度：时间 O(n + m)，空间 O(1)。
class Solution:  # 定义题解类
    def longestCommonPrefix(self, s: str, t: str) -> int:  # 返回从 t 开头可匹配的最长前缀长度
        n, m = len(s), len(t)  # 两串的长度
        i = j = 0  # i 扫描 s，j 记录 t 已匹配的前缀长度
        rem = False  # 标记唯一一次删除机会是否已用掉
        while i < n and j < m:  # 任一串耗尽即结束扫描
            if s[i] != t[j]:  # 当前字符不一致
                if rem:  # 删除机会已经用完
                    break  # 前缀无法继续延长，跳出循环
                rem = True  # 消耗删除机会，相当于从 s 中删掉 s[i]
            else:  # 当前字符一致
                j += 1  # t 的匹配前缀长度加一
            i += 1  # 无论是否删除，i 都后移一位
        return j  # j 即可匹配的最长前缀长度
