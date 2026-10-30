# 题目：1927. 求和游戏（Sum Game）
# 思路：分别统计左右半边的数字和与问号数；问号总数为奇数时先手必胜，偶数时只有 s1-s2 == 9*(cnt2-cnt1)/2 才判先手输。
# 时间复杂度：O(n)，只需扫描两半各一次；空间复杂度：O(1)，仅使用四个计数器。
class Solution:  # LeetCode 约定的题解类
    def sumGame(self, num: str) -> bool:  # num：由数字和 '?' 组成的字符串，长度保证为偶数
        n = len(num)  # 字符串总长度
        cnt1 = num[: n // 2].count("?")  # 左半边的问号个数
        cnt2 = num[n // 2 :].count("?")  # 右半边的问号个数
        s1 = sum(int(x) for x in num[: n // 2] if x != "?")  # 左半边所有数字字符之和
        s2 = sum(int(x) for x in num[n // 2 :] if x != "?")  # 右半边所有数字字符之和
        return (cnt1 + cnt2) % 2 == 1 or s1 - s2 != 9 * (cnt2 - cnt1) // 2  # 问号总数为奇数先手必赢；否则看差值是否为 9*(cnt2-cnt1)/2
