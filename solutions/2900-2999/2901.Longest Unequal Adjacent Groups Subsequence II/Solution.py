# 题目：2901. 最长相邻不相等子序列 II（Longest Unequal Adjacent Groups Subsequence II）
# 思路：动态规划，f[i] 表示以 i 结尾的最长合法链长，转移要求分组不同且两词只差一个字符，再用前驱数组回溯出整条链。
# 时间复杂度：O(n^2 * m)，n 为词数、m 为词长（check 逐位比较）；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def getWordsInLongestSubsequence(  # words 是候选词，groups 是对应的分组号
        self, words: List[str], groups: List[int]
    ) -> List[str]:  # 返回最长的合法词序列
        def check(s: str, t: str) -> bool:  # 判断两个词是否长度相同且恰好只差一个字符
            return len(s) == len(t) and sum(a != b for a, b in zip(s, t)) == 1  # 长度相同且不同字符个数恰为 1 才返回 True

        n = len(groups)  # 元素个数
        f = [1] * n  # f[i]：以 i 结尾的最长合法子序列长度，初值 1 表示至少含自己
        g = [-1] * n  # g[i]：子序列中 i 的前驱下标，-1 表示没有前驱
        mx = 1  # 记录全局最长长度，最后用来定位终点
        for i, x in enumerate(groups):  # 依次枚举子序列的结尾下标 i（x 为其分组号）
            for j, y in enumerate(groups[:i]):  # 枚举 i 之前的可能前驱 j（y 为其分组号）
                if x != y and f[i] < f[j] + 1 and check(words[i], words[j]):  # 分组不同、能延长当前链、且两词只差一个字符时转移
                    f[i] = f[j] + 1  # 更新以 i 结尾的最长长度
                    g[i] = j  # 记录前驱，供最后回溯路径
                    mx = max(mx, f[i])  # 同步维护全局最大值
        ans = []  # 保存最终答案
        for i in range(n):  # 找到第一个长度等于全局最大的终点
            if f[i] == mx:  # 该下标就是某条最长链的末尾
                j = i  # 从终点开始沿前驱回溯
                while j >= 0:  # 前驱存在时继续
                    ans.append(words[j])  # 收集路径上的单词（此时是逆序）
                    j = g[j]  # 跳到前驱
                break  # 只需一条最长链，找到后立即跳出
        return ans[::-1]  # 回溯结果逆序，切片翻转成正序返回
