# 题目：3817. 数字字符串中的好索引（Good Indices in a Digit String）
# 思路：直接枚举每个下标 i，把 i 转成十进制字符串 t，再取 s 中以 i 结尾、长度为 len(t) 的子串，若该子串恰好等于 t，则 i 就是好索引。
# 时间复杂度：O(n log n)，共 n 个下标，每次转串与比较的长度为 O(log n)；空间复杂度：O(log n)，只用到 t 这一个小字符串。
class Solution:  # LeetCode 约定的题解类
    def goodIndices(self, s: str) -> List[int]:  # s：只包含数字字符的字符串，返回其中所有好索引
        ans = []  # ans 收集所有好索引，天然按升序排列
        for i in range(len(s)):  # 从小到大枚举每个可能的好索引 i
            t = str(i)  # 把下标 i 转成十进制字符串
            k = len(t)  # k 是 i 的十进制位数，也就是要比较的子串长度
            if s[i + 1 - k : i + 1] == t:  # 切片从 i + 1 - k 到 i + 1，得到的子串正好以 i 结尾且长度为 k
                ans.append(i)  # 子串与 i 的十进制表示相等，说明 i 是好索引
        return ans  # 返回所有好索引
