# 题目：555. 分割连接字符串（Split Concatenated Strings）
# 核心思路：每个串先取正序/逆序中较大者；再枚举环上的切开位置，把切开后的两段与其余串拼起来取最大。
# 时间复杂度：O(L*sumLen)，L 为最长串长度；空间复杂度：O(sumLen)，用于构造候选答案。
class Solution:  # LeetCode 约定的题解类
    def splitLoopedString(self, strs: List[str]) -> str:  # strs 为字符串列表，首尾相接成环后切开，返回字典序最大的结果
        strs = [s[::-1] if s[::-1] > s else s for s in strs]  # 列表推导：每个串都替换成「正序与逆序」中较大的那个
        ans = ''.join(strs)  # 全环直接拼起来作为初始答案
        for i, s in enumerate(strs):  # 枚举环上从第 i 个串内部切开
            t = ''.join(strs[i + 1 :]) + ''.join(strs[:i])  # t 是除去第 i 个串之后、按环形顺序排列的其余部分
            for j in range(len(s)):  # 枚举第 i 个串内部的下标 j 作为切口
                a = s[j:]  # a 是切口之后的后缀，会成为答案开头
                b = s[:j]  # b 是切口之前的前缀，会成为答案结尾
                ans = max(ans, a + t + b)  # 正序情形：后缀 + 其余串 + 前缀，取较大者更新答案
                ans = max(ans, b[::-1] + t + a[::-1])  # 反向情形：反转后的前缀 + 其余串 + 反转后的后缀
        return ans  # 返回字典序最大的字符串
