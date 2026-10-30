# 题目：1309. 解码字母到整数映射（Decrypt String from Alphabet to Integer Mapping）
# 核心思路：顺序扫描，遇到 "dd#" 形式的两位编码就取两个数字，否则取一位数字，再用 chr 映射成字母收集起来。
# 时间复杂度：O(n)，每个字符只被访问一次；空间复杂度：O(n)，结果列表保存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def freqAlphabets(self, s: str) -> str:  # s 是待解码的编码串
        ans = []  # 用列表逐个收集解码出的字符
        i, n = 0, len(s)  # i 是读指针，n 是串长
        while i < n:  # 读指针未到末尾就继续
            if i + 2 < n and s[i + 2] == "#":  # 三位窗口形如 "dd#"，说明是两位数
                ans.append(chr(int(s[i : i + 2]) + ord("a") - 1))  # 两位切片转整数，再映射成 1~26 对应的字母
                i += 3  # 连同 '#' 一起跳过三位
            else:  # 否则当前只是一位数
                ans.append(chr(int(s[i]) + ord("a") - 1))  # 单个数字映射成字母
                i += 1  # 只前进一位
        return "".join(ans)  # 把字符列表拼成字符串返回
