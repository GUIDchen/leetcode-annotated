# 题目：2746. 字符串连接删减字母（Decremental String Concatenation）
# 思路：记忆化搜索，状态为 (待处理单词下标 i, 当前拼接串首字母 a, 尾字母 b)，每次把单词接在左边或右边并减去 1 个重叠字符。
# 时间复杂度：O(n * 26 * 26)，每个状态只算一次；空间复杂度：O(n * 26 * 26)，缓存表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimizeConcatenatedLength(self, words: List[str]) -> int:  # words：需要拼接的单词列表；返回拼接后字符串的最小长度
        @cache  # cache 装饰器给 dfs 做记忆化，相同状态只计算一次
        def dfs(i: int, a: str, b: str) -> int:  # dfs(i, a, b)：从第 i 个单词开始，当前串首字母 a、尾字母 b 时的最小总长
            if i >= len(words):  # 递归出口：所有单词都处理完
                return 0  # 没有单词可拼，追加长度为 0
            s = words[i]  # 当前要拼接的单词
            x = dfs(i + 1, a, s[-1]) - int(s[0] == b)  # 方案一：接在右边，若 s 首字母与当前串尾字母 b 相同则重叠 1 个字符
            y = dfs(i + 1, s[0], b) - int(s[-1] == a)  # 方案二：接在左边，若 s 尾字母与当前串首字母 a 相同则重叠 1 个字符
            return len(s) + min(x, y)  # 两种接法取较小值，加上 s 自身长度

        return len(words[0]) + dfs(1, words[0][0], words[0][-1])  # 第一个单词的长度固定，再以它的首尾字母为状态从第 1 个单词开始递归
