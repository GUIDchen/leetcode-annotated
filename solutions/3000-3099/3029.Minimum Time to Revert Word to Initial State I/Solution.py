# 题目：3029. 将单词恢复初始状态所需的最短时间 I（Minimum Time to Revert Word to Initial State I）
# 思路：第 t 秒后留下的恰好是删掉 t*k 个字符的后缀；该后缀若等于原串同长度前缀，就能靠补字符还原，找最小的 t。
# 时间复杂度：O(n^2 / k)，最多做 n/k 次切片比较；空间复杂度：O(n)，切片会产生临时字符串。
class Solution:  # LeetCode 约定的题解类
    def minimumTimeToInitialState(self, word: str, k: int) -> int:  # word：初始单词；k：每秒删除的字符数
        n = len(word)  # 单词长度，后面切片要用
        for i in range(k, n, k):  # i 是已删除的字符数，按 k 的整数倍递增
            if word[i:] == word[:-i]:  # 剩余后缀等于原串等长前缀，补齐后即可复原
                return i // k  # 删掉 i 个字符需要 i // k 秒，直接返回最早的答案
        return (n + k - 1) // k  # 单词删空后仍要补满一段字符，向上取整得到总秒数
