# 题目：890. 查找和替换模式（Find and Replace Pattern）
# 思路：双射校验——逐位比较两串中字符「上一次出现的位置」，位置始终一致即为同构，与双向字典等价但只用两个数组。
# 时间复杂度：O(n·m)，n 为单词数、m 为单词长度；空间复杂度：O(1)，只用了两个固定长度 128 的数组。
class Solution:  # LeetCode 约定的题解类
    def findAndReplacePattern(self, words: List[str], pattern: str) -> List[str]:  # words：候选单词列表；pattern：模式串；返回所有与 pattern 同构的单词
        def match(s, t):  # 内层函数：判断 s 与 t 是否同构（字符一一对应）
            m1, m2 = [0] * 128, [0] * 128  # m1/m2 分别记录 s、t 中每个字符最近一次出现的位置，0 表示还没出现
            for i, (a, b) in enumerate(zip(s, t), 1):  # enumerate 的起点设为 1，让位置与「未出现」的 0 区分；zip 逐位配对两个串
                if m1[ord(a)] != m2[ord(b)]:  # 同一位置上两串字符的「上次出现位置」不同，说明对应关系冲突
                    return False  # 冲突则立即判定不匹配，无需再看后面的字符
                m1[ord(a)] = m2[ord(b)] = i  # 同步写入两侧的位置，保证映射双向一致
            return True  # 循环正常结束，说明每一位都对得上，返回同构

        return [word for word in words if match(word, pattern)]  # 列表推导：筛选出所有与模式同构的单词
