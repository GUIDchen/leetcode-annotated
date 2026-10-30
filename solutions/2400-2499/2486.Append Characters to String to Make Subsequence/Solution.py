# 题目：2486. 追加字符以获得子序列（Append Characters to String to Make Subsequence）
# 思路：双指针贪心，让 s 去匹配 t 的最长前缀，t 中没匹配上的后缀只能原样追加。
# 时间复杂度：O(|s|)，s 只扫一遍；空间复杂度：O(1)，只用两个指针。
class Solution:  # LeetCode 约定的题解类
    def appendCharacters(self, s: str, t: str) -> int:  # s：已有字符串；t：目标字符串；返回最少还需要追加的字符数
        n, j = len(t), 0  # n 是 t 的长度；j 是 t 中已经匹配到的位置
        for c in s:  # 按顺序扫描 s 的每个字符
            if j < n and c == t[j]:  # j 还没到最后且当前字符与 t[j] 相同，说明又匹配上一位
                j += 1  # 匹配成功，t 的指针后移
        return n - j  # t 中剩余未匹配的后缀必须原样追加到末尾
