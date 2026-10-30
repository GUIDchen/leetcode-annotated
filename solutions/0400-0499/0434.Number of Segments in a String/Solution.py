# 题目：434. 字符串中的单词数（Number of Segments in a String）
# 思路：不带参数的 str.split() 按任意连续空白切分，并自动忽略首尾空白，切出的列表长度就是段数。
# 时间复杂度：O(n)，只需扫描一遍字符串；空间复杂度：O(n)，split 会生成单词列表。
class Solution:  # LeetCode 约定的题解类
    def countSegments(self, s: str) -> int:  # 统计 s 中被空白分隔出的非空段（单词）个数
        return len(s.split())  # 无参数的 split() 把连续空白视为一个分隔符，并丢弃首尾空白
