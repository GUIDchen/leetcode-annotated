# 题目：3261. 统计满足 K 约束的子字符串数量 II（Count Substrings That Satisfy K-Constraint II）
# 思路：先滑动窗口预处理。d[i] 记录以 i 为左端点时第一个使其不合法的右端点，pre 记录每个右端点对应合法起点数的前缀和；查询 [l, r] 时用 d[l] 定位分界点 p，起点恰为 l 的部分用等差数列求和，起点更大的部分用前缀和相减，两段相加即得答案。
# 时间复杂度：O(n + q)，预处理 O(n) 且每个查询 O(1)；空间复杂度：O(n)，d 与 pre 各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def countKConstraintSubstrings(  # 方法签名跨行书写：s 只含 '0'/'1'，k 为上限，queries 为若干 [l, r]
        self, s: str, k: int, queries: List[List[int]]  # 参数行：字符串 s、上限 k、查询列表 queries
    ) -> List[int]:  # 返回值类型是每个查询对应的答案列表
        cnt = [0, 0]  # cnt[0]、cnt[1] 统计当前窗口内 '0' 与 '1' 的个数
        i, n = 0, len(s)  # i 为窗口左端点，n 为字符串长度（链式赋值）
        d = [n] * n  # d[i]：以 i 为左端点时首个不合法的右端点，默认填 n 表示一直合法
        pre = [0] * (n + 1)  # pre[j+1] 为前 j+1 个右端点各自合法起点数的前缀和
        for j, x in enumerate(map(int, s)):  # j 为右端点，x 为当前字符转成的整数 0/1
            cnt[x] += 1  # 当前字符计入对应计数
            while cnt[0] > k and cnt[1] > k:  # 两种字符同时超过 k，窗口不合法
                d[i] = j  # 记录左端点 i 第一次不合法的右端点 j
                cnt[int(s[i])] -= 1  # 左端字符移出窗口
                i += 1  # 左端点右移一位
            pre[j + 1] = pre[j] + j - i + 1  # 以 j 结尾的合法起点共 j-i+1 个，累加进前缀和
        ans = []  # ans 存放每个查询的答案
        for l, r in queries:  # 逐个处理查询区间 [l, r]
            p = min(r + 1, d[l])  # p 为区间内第一个非法右端点，且不超过 r+1
            a = (1 + p - l) * (p - l) // 2  # 起点恰为 l 的部分：合法终点 l..p-1，共 (p-l)(p-l+1)/2 个
            b = pre[r + 1] - pre[p]  # 起点大于 l 的部分：由前缀和相减得到
            ans.append(a + b)  # 两部分相加得到该查询的答案
        return ans  # 返回全部查询的答案
