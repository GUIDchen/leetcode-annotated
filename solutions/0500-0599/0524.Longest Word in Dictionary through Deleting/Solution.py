# 题目：524. 通过删除字母匹配到字典里最长单词（Longest Word in Dictionary through Deleting）
# 思路：词典中的词若能由 s 删字符得到（即是 s 的子序列），取最长者，同长取字典序最小。
# 时间复杂度：O(n·L)，每个单词做一次双指针扫描；空间复杂度：O(1)，只保存答案字符串。
class Solution:  # LeetCode 约定的题解类
    def findLongestWord(self, s: str, dictionary: List[str]) -> str:  # s：可删除字符的源串；dictionary：候选词典；返回最长且字典序最小的可匹配单词
        def check(s: str, t: str) -> bool:  # 内层函数：判断 s 是否为 t 的子序列
            m, n = len(s), len(t)  # m、n 分别是两个串的长度
            i = j = 0  # i 指向 s、j 指向 t，都从 0 开始
            while i < m and j < n:  # 任一串走完即停止扫描
                if s[i] == t[j]:  # 字符相同表示匹配成功
                    i += 1  # s 的指针前进
                j += 1  # t 的指针每轮都前进
            return i == m  # s 全部匹配完说明它是 t 的子序列

        ans = ""  # 当前最优答案，空串表示还没找到
        for t in dictionary:  # 遍历词典中的每个单词
            if check(t, s) and (len(ans) < len(t) or (len(ans) == len(t) and ans > t)):  # 是 s 的子序列，并且更长，或同长但字典序更小
                ans = t  # 更新最优答案
        return ans  # 返回最优答案，找不到时是空串
