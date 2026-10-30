# 题目：1910. 删除一个字符串中所有出现的给定子字符串（Remove All Occurrences of a Substring）
# 思路：只要 part 还出现在 s 中，就删掉它第一次出现的那一段；反复执行直到不再出现。
# 时间复杂度：O(n^2)，每轮 replace 为 O(n)，最多 n 轮；空间复杂度：O(n)，每轮生成新字符串。
class Solution:  # LeetCode 约定的题解类
    def removeOccurrences(self, s: str, part: str) -> str:  # s：原字符串；part：需要删除的子串
        while part in s:  # 只要 part 仍出现在 s 中，就继续删
            s = s.replace(part, '', 1)  # 第三个参数 1 表示只删掉第一个匹配，避免一次性删掉所有匹配
        return s  # 返回删干净后的字符串
