# 题目：2781. 最长合法子字符串的长度（Length of the Longest Valid Substring）
# 核心思路：滑动窗口 + 集合。右端 j 从左到右扩展，只枚举以 j 结尾、长度不超过 10 的子串（禁用串长度上限为 10），命中就把左端 i 跳到命中起点之后。
# 时间复杂度：O(n * L^2)，n 为串长、L = 10 为禁用串长度上限（切片还要 O(L)）；空间复杂度：O(mL)，集合保存全部禁用串。
class Solution:  # LeetCode 约定的题解类
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:  # word：待检查的字符串；forbidden：禁用子串列表；返回最长合法子串长度
        s = set(forbidden)  # 用集合加速：O(1) 判断某个子串是否被禁用
        ans = i = 0  # ans 存答案；i 是滑动窗口左端，初始为 0（对应 j 也从 0 开始）
        for j in range(len(word)):  # 右端点 j 从左到右逐格扩展
            for k in range(j, max(j - 10, i - 1), -1):  # 只枚举以 j 结尾、长度 ≤10 且不越过左端 i 的子串起点 k（range 含头不含尾，故下界写成 i-1）
                if word[k : j + 1] in s:  # 切片 word[k..j] 若在禁用集合中，说明这个窗口非法
                    i = k + 1  # 冲突子串从 k 开始，左端要跳到 k+1 才能把它整体排除
                    break  # 更短的子串必然也非法，直接跳出内层循环
            ans = max(ans, j - i + 1)  # 用当前合法窗口长度更新答案
        return ans  # 返回最长合法子串长度
