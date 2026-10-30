# 题目：2135. 统计追加字母可以获得的单词数（Count Words Obtained After Adding a Letter）
# 思路：每个单词用 26 位整数做字母掩码（题目保证单词内字母互不相同），起始单词掩码存入集合；对每个目标单词枚举被追加的字母，用异或清掉该字母位后查集合，命中即说明该目标单词可被得到。
# 时间复杂度：O(L·(n + m))，L 为单词长度；空间复杂度：O(n)，集合保存 n 个起始单词的掩码。
class Solution:  # LeetCode 约定的题解类
    def wordCount(self, startWords: List[str], targetWords: List[str]) -> int:  # startWords：起始单词表；targetWords：目标单词表
        s = {sum(1 << (ord(c) - 97) for c in w) for w in startWords}  # 集合 s 保存每个起始单词的 26 位字母掩码（字母互不相同，求和等价于按位或）
        ans = 0  # ans 统计可由起始单词追加一个字母得到的目标单词数
        for w in targetWords:  # 逐个检查目标单词
            x = sum(1 << (ord(c) - 97) for c in w)  # 目标单词的字母掩码
            for c in w:  # 枚举「被追加的那个字母」c，等价于从掩码中把它去掉
                if x ^ (1 << (ord(c) - 97)) in s:  # 用异或清掉该字母位，若剩余掩码在集合中则说明可以追加得到
                    ans += 1  # 计数加一
                    break  # 同一个目标单词只计一次
        return ans  # 返回可获得的单词数
