# 题目：2744. 最大字符串配对数目（Find Maximum Number of String Pairs）
# 核心思路：用哈希表统计已出现过的字符串，遍历时直接查找当前字符串的反转形式，出现过几次就能配成几对。
# 时间复杂度：O(n)，每次查询与插入均摊 O(1)；空间复杂度：O(n)，哈希表保存所有出现过的字符串。
class Solution:  # LeetCode 约定的题解类
    def maximumNumberOfStringPairs(self, words: List[str]) -> int:  # words：长度均为 2 的互不相同的字符串数组
        cnt = Counter()  # 记录每个字符串已经出现的次数
        ans = 0  # 累计能形成的配对数
        for w in words:  # 逐个处理每个字符串
            ans += cnt[w[::-1]]  # w[::-1] 是反转后的字符串，它出现过几次就能与 w 配成几对
            cnt[w] += 1  # 把当前字符串计入哈希表，供后面的字符串配对
        return ans  # 返回最多能配对的对数
