# 题目：893. 特殊等价字符串组（Groups of Special-Equivalent Strings）
# 核心思路：偶数位、奇数位字符各自排序后拼接成规范键，特殊等价的两串规范键相同，用集合去重计数。
# 时间复杂度：O(n·m log m)，m 为串长；空间复杂度：O(n·m)，集合保存所有规范键。
class Solution:  # LeetCode 约定的题解类
    def numSpecialEquivGroups(self, words: List[str]) -> int:  # words：字符串数组
        s = {''.join(sorted(word[::2]) + sorted(word[1::2])) for word in words}  # word[::2] 取偶数位、word[1::2] 取奇数位，排序后拼接成规范键；集合自动去重
        return len(s)  # 集合元素个数即分组数
