# 题目：1897. 重新分配字符使所有字符串都相等（Redistribute Characters to Make All Strings Equal）
# 思路：字符总数固定且位置自由，因此每种字符的出现次数都能被字符串个数 n 整除时，才能把每个字符串都凑成同一份字符集合。
# 时间复杂度：O(L)，L 为全部字符数；空间复杂度：O(1)，计数器最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def makeEqual(self, words: List[str]) -> bool:  # words：待重新分配字符的字符串数组
        cnt = Counter()  # 计数器：统计每个字符的总出现次数
        for w in words:  # 逐个字符串遍历
            for c in w:  # 逐个字符累加
                cnt[c] += 1  # 字符 c 的出现次数加一
        n = len(words)  # 字符串个数
        return all(v % n == 0 for v in cnt.values())  # 每种字符的次数都能被 n 整除，则可以均分
