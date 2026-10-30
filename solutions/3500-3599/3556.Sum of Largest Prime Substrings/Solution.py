# 题目：3556. 最大质数子字符串之和（Sum of Largest Prime Substrings）
# 思路：枚举每个起点并向右滚动累积子串数值，逐个试除判断是否为质数，把质数子串放进集合去重；最后对集合升序排序，取最大的至多三个不同质数求和即为答案。
# 时间复杂度：O(n² · √V)，n 为串长、V 为最大子串数值（质数判定试除到 √x）；空间复杂度：O(n²)，集合中最多存放 n(n+1)/2 个不同质数。
class Solution:  # LeetCode 约定的题解类
    def sumOfLargestPrimes(self, s: str) -> int:  # s：数字字符串；返回其中最大的三个不同质数子串之和
        def is_prime(x: int) -> bool:  # is_prime：判断 x 是否为质数
            if x < 2:  # 小于 2 的数不是质数
                return False  # 直接返回假
            return all(x % i for i in range(2, int(sqrt(x)) + 1))  # 试除 2..⌊√x⌋，全都除不尽才是质数

        st = set()  # st：去重存放所有质数子串的数值
        n = len(s)  # n：字符串长度
        for i in range(n):  # 枚举子串起点 i
            x = 0  # x：以 i 为起点的子串数值，逐位滚动累积
            for j in range(i, n):  # 枚举子串终点 j，把子串向右扩展
                x = x * 10 + int(s[j])  # 追加一位数字，形成新的子串数值
                if is_prime(x):  # 当前子串的数值是质数
                    st.add(x)  # 去重后加入集合
        return sum(sorted(st)[-3:])  # 升序排序后取最大的至多三个不同质数求和
