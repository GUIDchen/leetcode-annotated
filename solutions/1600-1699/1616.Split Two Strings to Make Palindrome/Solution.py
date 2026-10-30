# 题目：1616. 分割两个字符串得到回文串（Split Two Strings to Make Palindrome）
# 思路：先双指针匹配 a 的前缀与 b 的后缀，指针交错则直接成立；否则检查夹在中间的剩余段能否由 a 或 b 自己构成回文。
# 时间复杂度：O(n)，每个字符只会被比较常数次；空间复杂度：O(1)（切片产生的临时串属于实现细节，算法本身只用下标）。
class Solution:  # LeetCode 约定的题解类
    def checkPalindromeFormation(self, a: str, b: str) -> bool:  # a、b：两个等长字符串
        def check1(a: str, b: str) -> bool:  # 尝试用 a 的前缀与 b 的后缀拼成回文
            i, j = 0, len(b) - 1  # i 从 a 头部出发，j 从 b 尾部出发
            while i < j and a[i] == b[j]:  # 两端字符相等就继续向中间收缩
                i, j = i + 1, j - 1  # 元组同时赋值：左指针右移、右指针左移
            return i >= j or check2(a, i, j) or check2(b, i, j)  # 指针已交错，或中间剩余段由 a（或 b）自己构成回文

        def check2(a: str, i: int, j: int) -> bool:  # 判断 a 的 [i, j] 区间是否为回文
            return a[i : j + 1] == a[i : j + 1][::-1]  # 切片取出区间，[::-1] 反转后比较

        return check1(a, b) or check1(b, a)  # 两种切分方式任意一种成立即可
