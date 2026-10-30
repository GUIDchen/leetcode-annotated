# 题目：3016. 输入单词需要的最少按键次数 II（Minimum Number of Pushes to Type Word II）
# 思路：用 Counter 统计每个字母的出现次数，按频次降序排序；前 8 个高频字母按 1 次，接下来 8 个按 2 次，第 i 名（0 起）需按 i//8+1 次，乘频次累加即为答案。
# 时间复杂度：O(n + 26log26)，n 为单词长度；空间复杂度：O(1)，哈希表最多 26 个键、外加常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumPushes(self, word: str) -> int:  # word 是待输入的单词，返回打完它所需的最少按键总次数
        cnt = Counter(word)  # Counter 统计每个字母的出现次数：键是字母，值是频次
        ans = 0  # ans 累计按键总次数
        for i, x in enumerate(sorted(cnt.values(), reverse=True)):  # 把频次降序排列，enumerate 同时给出排名 i（0 起）与该字母的频次 x
            ans += (i // 8 + 1) * x  # 第 i 名落在第 i//8+1 轮键位上，需按 i//8+1 下，乘频次即它的总按键数
        return ans  # 返回最少按键总次数
