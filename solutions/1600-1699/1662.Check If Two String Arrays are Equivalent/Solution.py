# 题目：1662. 检查两个字符串数组是否相等（Check If Two String Arrays are Equivalent）
# 思路：str.join 把每个列表的单词按顺序拼成一个字符串，再比较两个结果是否相同。
# 时间复杂度：O(L)，L 为拼接后总长度；空间复杂度：O(L)，需要保存拼接出的两个字符串。
class Solution:  # LeetCode 约定的题解类
    def arrayStringsAreEqual(self, word1: List[str], word2: List[str]) -> bool:  # word1/word2 是字符串列表，判断拼接结果是否相等
        return ''.join(word1) == ''.join(word2)  # 空串作分隔符 join，等价于直接相连；比较两个拼接结果
