# 题目：2716. 最小化字符串长度（Minimize String Length）
# 思路：重复字符都能通过操作删掉，最终每种出现过的字符只留一个，答案即不同字符的种数。
# 时间复杂度：O(n)，只遍历一次字符串；空间复杂度：O(Σ)，Σ 为字符集大小（本题 26）。
class Solution:  # LeetCode 约定的题解类
    def minimizedStringLength(self, s: str) -> int:  # s：输入字符串，返回最少能剩下的字符个数
        return len(set(s))  # set 自动去重，len 得到不同字符的种数并直接返回
