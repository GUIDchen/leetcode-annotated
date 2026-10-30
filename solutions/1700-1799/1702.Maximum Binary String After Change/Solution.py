# 题目：1702. 修改后的最大二进制字符串（Maximum Binary String After Change）
# 思路：第一个 0 之前的 1 保持不动；其后每出现一个 0，就能把最靠前的那个 0 往后推一位，最终只剩一个 0 位于 k 位置。
# 时间复杂度：O(n)，字符串扫描与计数各一次；空间复杂度：O(n)，用于构造返回的字符串。
class Solution:  # LeetCode 约定的题解类
    def maximumBinaryString(self, binary: str) -> str:  # binary 是只含 '0'/'1' 的字符串
        k = binary.find('0')  # 第一个 '0' 的下标，它左边的 '1' 都无法被改动
        if k == -1:  # find 返回 -1 表示字符串里没有 '0'
            return binary  # 全 1 本身就是最大字典序，原样返回
        k += binary[k + 1 :].count('0')  # 第一个 0 之后每多一个 0，最终那个 0 的位置就右移一位
        return '1' * k + '0' + '1' * (len(binary) - k - 1)  # 拼成 k 个 1 + 一个 0 + 剩余的 1
