# 题目：2840. 判断通过操作能否让字符串相等 II（Check if Strings Can be Made Equal With Operations II）
# 思路：操作可在同奇偶下标之间任意交换字符，故只需比较两个字符串偶数下标、奇数下标上的字符计数器是否分别相等。
# 时间复杂度：O(n)，两次切片各扫一遍并建计数器；空间复杂度：O(1)，字母表只有 26 个字符。
class Solution:  # LeetCode 约定的题解类
    def checkStrings(self, s1: str, s2: str) -> bool:  # 判断能否通过若干次操作把 s1 变成 s2
        return Counter(s1[::2]) == Counter(s2[::2]) and Counter(s1[1::2]) == Counter(  # 先比较偶数下标字母多重集，再比较
            s2[1::2]  # 奇数下标字母多重集，两者都相同才返回 True
        )  # 整个表达式作为返回值
