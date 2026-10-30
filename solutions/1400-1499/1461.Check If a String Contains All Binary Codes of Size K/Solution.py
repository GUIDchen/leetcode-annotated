# 题目：1461. 检查一个字符串是否包含所有长度为 K 的二进制子串（Check If a String Contains All Binary Codes of Size K）
# 思路：长度为 k 的二进制串共 2^k 种，用集合推导式收集所有滑窗子串并去重，再看集合大小是否等于 2^k；先用子串个数做可行性剪枝。
# 时间复杂度：O(n×k)，每个窗口切片长度 k；空间复杂度：O(n×k)，集合最多存 n-k+1 个 k 长子串。
class Solution:  # LeetCode 约定的题解类
    def hasAllCodes(self, s: str, k: int) -> bool:  # s：二进制字符串；k：子串长度
        n = len(s)  # 字符串长度
        m = 1 << k  # 长度为 k 的二进制串共有 2^k 种
        if n - k + 1 < m:  # 子串总数不足 2^k，一定无法覆盖所有编码
            return False  # 提前返回 False
        ss = {s[i : i + k] for i in range(n - k + 1)}  # 集合推导式收集所有长度为 k 的子串，重复的自动去掉
        return len(ss) == m  # 去重后数量达到 2^k 即为真
