# 题目：3210. 找出加密后的字符串（Find the Encrypted String）
# 思路：按题意第 i 个字符取自原串下标 (i + k) mod n，因此先把原串拷成字符列表，再逐位覆盖。
# 时间复杂度：O(n)；空间复杂度：O(n)，用于存放结果字符列表。
class Solution:  # LeetCode 约定的题解类
    def getEncryptedString(self, s: str, k: int) -> str:  # s：原字符串；k：加密时的循环右移位数
        cs = list(s)  # 复制一份原串用于写入，保证读到的仍是原字符
        n = len(s)  # 字符串长度
        for i in range(n):  # 逐个位置计算加密后的字符
            cs[i] = s[(i + k) % n]  # 下标 (i + k) 对 n 取模，实现循环取字符
        return "".join(cs)  # 把字符列表拼回字符串返回
