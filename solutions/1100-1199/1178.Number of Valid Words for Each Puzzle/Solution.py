# 题目：1178. 猜字谜（Number of Valid Words for Each Puzzle）
# 思路：把每个单词压成 26 位字母集合掩码并计数；对每个谜面求出掩码后枚举其全部非空子集，
#       只累加含谜面首字母的子集，其计数之和就是答案。时间复杂度 O(2^7 * 谜面数)，空间 O(单词数)。
class Solution:  # LeetCode 约定的题解类
    def findNumOfValidWords(self, words: List[str], puzzles: List[str]) -> List[int]:  # words 为候选词表，puzzles 为字谜列表
        cnt = Counter()  # 计数器：键是字母集合掩码，值是该掩码对应的单词数量
        for w in words:  # 逐个单词压缩成掩码
            mask = 0  # mask 的第 b 位为 1 表示该词含字母 b
            for c in w:  # 遍历单词中的每个字符
                mask |= 1 << (ord(c) - ord("a"))  # 把当前字母对应位置 1，重复字母自然去重
            cnt[mask] += 1  # 相同字母集合的单词合并计数，便于之后按掩码批量取数

        ans = []  # 按谜面顺序保存答案
        for p in puzzles:  # 逐个谜面处理
            mask = 0  # 重新构造当前谜面的字母集合掩码
            for c in p:  # 遍历谜面的每个字符
                mask |= 1 << (ord(c) - ord("a"))  # 置入对应字母位
            x, i, j = 0, ord(p[0]) - ord("a"), mask  # x 累计合法单词数，i 为谜面首字母位号，j 从完整掩码开始枚举子集
            while j:  # 枚举 mask 的所有非空子集（j 为 0 时退出）
                if j >> i & 1:  # 子集必须含谜面首字母，否则对应的词不合法
                    x += cnt[j]  # 累加该掩码上记录的单词数
                j = (j - 1) & mask  # 子集枚举递推：得到下一个更小的子集
            ans.append(x)  # 答案写入结果数组，顺序与 puzzles 一致
        return ans  # 返回每个谜面的合法单词数
