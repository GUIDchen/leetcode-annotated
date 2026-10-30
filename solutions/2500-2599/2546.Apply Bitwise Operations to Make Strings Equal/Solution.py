# 题目：2546. 执行逐位运算使字符串相等（Apply Bitwise Operations to Make Strings Equal）
# 思路：两个串都含 1 时可互相变换，都不含 1 时本来就相等，故只需比较「是否含 1」。
# 时间复杂度：O(n)，两次子串查找；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def makeStringsEqual(self, s: str, target: str) -> bool:  # 判断 s 能否通过逐位运算变成 target
        return ("1" in s) == ("1" in target)  # 两侧「是否含字符 1」的布尔值相等时答案为真，不等则无解
