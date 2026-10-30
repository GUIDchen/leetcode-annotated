# 题目：2405. 子字符串的最优划分（Optimal Partition of String）
# 思路：贪心加 26 位掩码：当前段不重复就继续延伸，遇到重复字母立即切分并重开一段。
# 时间复杂度：O(n)，每个字符只处理一次；空间复杂度：O(1)，只用一个掩码和一个计数器。
class Solution:  # LeetCode 约定的题解类
    def partitionString(self, s: str) -> int:  # s：待划分的字符串，返回最少需要划分出的子串个数
        ans, mask = 1, 0  # ans 至少为 1 段；mask 用二进制位记录当前段里已经出现过的字母
        for x in map(lambda c: ord(c) - ord("a"), s):  # 把每个字符映射成 0~25 的编号，对应 mask 的第几位
            if mask >> x & 1:  # 该位为 1 说明本段已出现过这个字母，必须切分
                ans += 1  # 段数加一
                mask = 0  # 清空掩码，开始记录新的一段
            mask |= 1 << x  # 把当前字母标记进本段的字母集合
        return ans  # 返回最少段数
