# 3722. Lexicographically Smallest String After Reverse（反转后字典序最小的字符串）
# 核心思路：枚举翻转长度 k，分别尝试“翻转长度为 k 的前缀”和“翻转长度为 k 的后缀”，在所有候选串中取字典序最小者。
# 复杂度：时间 O(n^2)（枚举 n 种长度，每次切片 O(n)），空间 O(n)。

class Solution:
    def lexSmallest(self, s: str) -> str:  # 返回一次反转（翻转某个前缀或某个后缀）后字典序最小的字符串
        ans = s  # ans 记录当前最优答案，初始为原串（相当于翻转长度 0）
        for k in range(1, len(s) + 1):  # 枚举翻转长度 k，从 1 到 n
            t1 = s[:k][::-1] + s[k:]  # 方案一：翻转长度为 k 的前缀，再拼上剩余后缀
            t2 = s[:-k] + s[-k:][::-1]  # 方案二：保留前 n-k 个字符，翻转长度为 k 的后缀
            ans = min(ans, t1, t2)  # 在三者中取字典序最小者
        return ans  # 返回字典序最小的结果
