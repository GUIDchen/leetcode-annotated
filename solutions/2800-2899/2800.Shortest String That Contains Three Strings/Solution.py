# 题目：2800. 包含三个字符串的最短字符串（Shortest String That Contains Three Strings）
# 思路：枚举三个串的 6 种排列，用内嵌函数 f 求两串的最短合并串，按长度、字典序取最优。
# 时间复杂度：O(L^2)，L 为串长（f 最多比较 L 次、每次 O(L)）；空间复杂度：O(L)，用于存放候选串。
class Solution:  # LeetCode 约定的题解类
    def minimumString(self, a: str, b: str, c: str) -> str:  # a、b、c：三个待包含的字符串
        def f(s: str, t: str) -> str:  # 求同时包含 s 与 t 的最短合并串（s 在前、t 在后）
            if s in t:  # t 里已经包含 s
                return t  # 那么 t 就同时包含两者，直接返回 t
            if t in s:  # s 里已经包含 t
                return s  # 那么 s 就同时包含两者，直接返回 s
            m, n = len(s), len(t)  # m、n：两个串的长度
            for i in range(min(m, n), 0, -1):  # 从可能的最大重叠长度开始递减
                if s[-i:] == t[:i]:  # s 长度为 i 的后缀与 t 长度为 i 的前缀相同
                    return s + t[i:]  # 保留重叠部分，只把 t 多出来的部分接在后面
            return s + t  # 完全没有重叠，直接首尾相接

        ans = ""  # 当前最优答案，空串表示还没找到
        for a, b, c in permutations((a, b, c)):  # 遍历三个串的 6 种排列；可迭代对象在进入循环前已求值，循环变量与外层同名也不会互相干扰
            s = f(f(a, b), c)  # 先合并前两个，再与第三个合并，得到候选答案
            if ans == "" or len(s) < len(ans) or (len(s) == len(ans) and s < ans):  # 更短，或等长但字典序更小
                ans = s  # 更新最优答案
        return ans  # 返回最短且字典序最小的合并串
