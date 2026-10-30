# 题目：1239. 串联字符串的最大长度（Maximum Length of a Concatenated String with Unique Characters）
# 思路：用 26 位掩码表示每个字符串的字符集合，列表 s 维护所有可行组合，当前串只与无交集的组合合并并取最大位数。
# 时间复杂度：O(n·2^m)，组合数最坏是指数级；空间复杂度：O(2^m)，保存所有可行组合的掩码。
class Solution:  # LeetCode 约定的题解类
    def maxLength(self, arr: List[str]) -> int:  # arr 是候选字符串列表，返回拼接后字符互不重复的最大长度
        s = [0]  # 可行组合的掩码列表，0 代表空串，每个整数是一种字符集合
        for t in arr:  # 逐个处理候选字符串
            x = 0  # 用位掩码记录当前字符串用到的字符
            for b in map(lambda c: ord(c) - 97, t):  # 把每个字符映射成 0..25 的位下标后遍历
                if x >> b & 1:  # 该位已存在说明本串自身就有重复字符
                    x = 0  # 把 x 置 0，令这个串作废
                    break  # 提前结束内层循环
                x |= 1 << b  # 把字符对应的位置 1
            if x:  # 只有自身无重复字符的串（x 非 0）才参与拼接
                s.extend((x | y) for y in s if (x & y) == 0)  # 与已有组合无公共位时取并集；新并集必然含 x 的位，会被条件自身过滤，遍历能正常结束
        return max(x.bit_count() for x in s)  # 取所有组合中位数最多（长度最长）的一个
