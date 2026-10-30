# 题目：1960. 两个回文子字符串长度的最大乘积（Maximum Product of the Length of Two Palindromic Substrings）
# 思路：用 Manacher 求出以每个位置为中心的最长奇回文半长 hlen，把回文长度登记到左右端点，再分别向两侧做「收缩 -2」的传播与前缀/后缀最大值，最后枚举分割点取乘积最大。
# 时间复杂度：O(n)，几趟线性扫描；空间复杂度：O(n)，hlen、prefix、suffix 三个数组。
class Solution:  # LeetCode 约定的题解类
    def maxProduct(self, s: str) -> int:  # s 为输入字符串，返回两个不重叠回文子串长度的最大乘积
        n = len(s)  # 串长
        hlen = [0] * n  # hlen[i]：以 i 为中心的最长奇回文「半长」，回文长度为 2*hlen[i]+1
        center = right = 0  # 当前最右回文的中心 center 与右端点 right（right 为不含边界的右端）

        for i in range(n):  # Manacher：逐个中心计算最长奇回文半长
            if i < right:  # i 落在最右回文内部，可以利用对称点加速
                hlen[i] = min(right - i, hlen[2 * center - i])  # 对称点半径为 hlen[2*center-i]，但不能超过当前右边界
            while (  # 从已知半径继续向两侧暴力扩展
                0 <= i - 1 - hlen[i]  # 左端点越界就停止扩展
                and i + 1 + hlen[i] < len(s)  # 右端点越界就停止扩展
                and s[i - 1 - hlen[i]] == s[i + 1 + hlen[i]]  # 两侧字符相同才能继续扩展
            ):
                hlen[i] += 1  # 扩展成功，半长加一
            if right < i + hlen[i]:  # 当前回文的右端比已知最右回文更远，需要更新
                center, right = i, i + hlen[i]  # 记录新的中心与右端点

        prefix = [0] * n  # prefix[x]：右端点恰为 x 的最长回文长度（之后会改成前缀最大值）
        suffix = [0] * n  # suffix[x]：左端点恰为 x 的最长回文长度（之后会改成后缀最大值）

        for i in range(n):  # 把每个中心的最长回文登记到它的左右端点
            prefix[i + hlen[i]] = max(prefix[i + hlen[i]], 2 * hlen[i] + 1)  # 以 i 为中心的最长回文右端为 i+hlen[i]，长度为 2*hlen[i]+1
            suffix[i - hlen[i]] = max(suffix[i - hlen[i]], 2 * hlen[i] + 1)  # 同一个回文的左端点为 i-hlen[i]

        for i in range(1, n):  # 右端点收缩：~i 等于 -i-1，用负数下标从右往左遍历；右端左移一格，长度至多减 2
            prefix[~i] = max(prefix[~i], prefix[~i + 1] - 2)  # 用右端点为 ~i+1 的回文向左收缩一格到 ~i，长度减 2
            suffix[i] = max(suffix[i], suffix[i - 1] - 2)  # 左端点右移一格，长度同样减 2

        for i in range(1, n):  # 再做一遍前缀 / 后缀最大值，得到任意边界内的最长回文
            prefix[i] = max(prefix[i - 1], prefix[i])  # prefix[i] 变为右端点不超过 i 的最长回文长度
            suffix[~i] = max(suffix[~i], suffix[~i + 1])  # suffix[~i] 变为左端点不小于 ~i 的最长回文长度

        return max(prefix[i - 1] * suffix[i] for i in range(1, n))  # 枚举切分点 i，取左半最长与右半最长乘积的最大值
