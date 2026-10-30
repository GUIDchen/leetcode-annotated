# 题目：541. 反转字符串 II（Reverse String II）
# 思路：以 2k 为步长从头扫描，每个区间内只反转前 k 个字符；末尾不足 k 个时切片会自动截断，把剩余全部反转。
# 时间复杂度：O(n)，每个字符至多被移动一次；空间复杂度：O(n)，因为字符串不可变，先转成字符列表。
class Solution:  # LeetCode 约定的题解类
    def reverseStr(self, s: str, k: int) -> str:  # s 是待处理的字符串，k 是每 2k 个字符中需要反转的前缀长度
        cs = list(s)  # Python 字符串不可变，先转成字符列表以便原地修改
        for i in range(0, len(cs), 2 * k):  # i 每轮前进 2k，即跳过一个「反转前 k 个」的区块
            cs[i : i + k] = reversed(cs[i : i + k])  # 切片 cs[i:i+k] 在末尾不足 k 个时会自动截断，正好实现「剩余全部反转」
        return "".join(cs)  # 把字符列表拼回字符串返回
