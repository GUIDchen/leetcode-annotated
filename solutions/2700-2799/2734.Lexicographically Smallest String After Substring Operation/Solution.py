# 题目：2734. 执行子串操作后的字典序最小字符串（Lexicographically Smallest String After Substring Operation）
# 思路：跳过开头的 'a'，找到之后第一段连续非 'a' 的区间 [i, j)，把区间内字符统一减一；若整串都是 'a'，则把最后一位改成 'z'。
# 时间复杂度：O(n)，i、j 各只走一遍；空间复杂度：O(n)，切片与 join 会构造新字符串。
class Solution:  # LeetCode 约定的题解类
    def smallestString(self, s: str) -> str:  # s 是输入字符串，返回操作一次后字典序最小的字符串
        n = len(s)  # 记录字符串长度，用于边界判断
        i = 0  # i 指向开头连续 'a' 段之后的位置
        while i < n and s[i] == "a":  # 跳过开头的 'a'：'a' 减一会变成 'z'，会让字典序变大，必须避开
            i += 1  # i 右移，寻找第一个可以减一的字符
        if i == n:  # 整串都是 'a'，没有可减的字符
            return s[:-1] + "z"  # 必须执行一次操作，只能把最后一个 'a' 变成 'z'
        j = i  # j 用来寻找第一段连续非 'a' 区间的右端点
        while j < n and s[j] != "a":  # 区间越长字典序越小，遇到 'a' 或串尾就停下
            j += 1  # j 右移，扩大减一区间
        return s[:i] + "".join(chr(ord(c) - 1) for c in s[i:j]) + s[j:]  # 用 chr(ord(c) - 1) 逐个减一，前后两段原样保留并拼接
