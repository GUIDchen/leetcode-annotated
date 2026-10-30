# 题目：1668. 最大重复子字符串（Maximum Repeating Substring）
# 思路：从理论上限 len(sequence) // len(word) 开始倒序枚举 k，第一个满足 word*k 是子串的 k 就是答案。
# 时间复杂度：O(n²/m)，每次子串查找 O(n·k)；空间复杂度：O(n)，临时构造 word*k 字符串。
class Solution:  # LeetCode 约定的题解类
    def maxRepeating(self, sequence: str, word: str) -> int:  # sequence：主串；word：要重复的子串，返回最大重复次数
        for k in range(len(sequence) // len(word), -1, -1):  # 从理论上限倒序枚举重复次数，第一个可行解就是最大值
            if word * k in sequence:  # word 重复 k 次后是 sequence 的子串
                return k  # 因为 k 从大到小枚举，直接返回当前 k 即可
