# 题目：2983. 回文串重新排列查询（Palindrome Rearrangement Queries）
# 核心思路：把右半段翻转后与左半段逐位对齐，用两套 26 字母前缀和与「不匹配前缀个数」diff，把每个查询按区间包含/分离/相交三种情况在 O(1) 内判定。
# 时间复杂度：O((n + q) · 26)，建表 O(26n) 后每次查询做常数次前缀差；空间复杂度：O(26n)，两套前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def canMakePalindromeQueries(self, s: str, queries: List[List[int]]) -> List[bool]:  # s 为偶数长度串，queries 每项给出两段可任意重排的区间，返回每个查询是否可行
        def count(pre: List[List[int]], i: int, j: int) -> List[int]:  # 用前缀和取出闭区间 [i, j] 的 26 字母频次
            return [x - y for x, y in zip(pre[j + 1], pre[i])]  # 前缀和下标右移一位后逐字母作差

        def sub(cnt1: List[int], cnt2: List[int]) -> List[int]:  # 逐字母作差；出现负数说明字符不足，用空列表表示失败
            res = []  # 存放差值的结果列表
            for x, y in zip(cnt1, cnt2):  # 同步遍历两个频次向量
                if x - y < 0:  # 该字母的需求为负
                    return []  # 返回空列表标记不可行
                res.append(x - y)  # 记录该字母的剩余需求
            return res  # 全部字母都非负，返回差值向量

        def check(  # 判断两侧区间 [a, b] 与 [c, d] 重排后能否逐位相等（调用前已保证 a <= c）
            pre1: List[List[int]], pre2: List[List[int]], a: int, b: int, c: int, d: int  # pre1/pre2 分别是左半段、翻转右半段的字母频次前缀和
        ) -> bool:  # 返回该查询是否可行
            if diff[a] > 0 or diff[m] - diff[max(b, d) + 1] > 0:  # 区间之外的前缀 [0, a) 与后缀 (max(b, d), m) 无法被改动，必须本来就匹配
                return False  # 存在补不回来的不匹配位置，失败
            if d <= b:  # 情况一：右区间被左区间完全包含
                return count(pre1, a, b) == count(pre2, a, b)  # 两段字母多重集相同即可重排成逐位相等
            if b < c:  # 情况二：两区间完全不重叠
                return (  # 下面三个条件必须同时成立：
                    diff[c] - diff[b + 1] == 0  # 中间空档 [b+1, c) 必须已匹配
                    and count(pre1, a, b) == count(pre2, a, b)  # 左段的多重集自洽
                    and count(pre1, c, d) == count(pre2, c, d)  # 右段的多重集自洽
                )  # 条件组合结束
            cnt1 = sub(count(pre1, a, b), count(pre2, a, c - 1))  # 左段独有部分的需求：左半段减去右段已覆盖的 [a, c-1]
            cnt2 = sub(count(pre2, c, d), count(pre1, b + 1, d))  # 右段独有部分的需求：右半段减去左段已覆盖的 [b+1, d]
            return bool(cnt1) and bool(cnt2) and cnt1 == cnt2  # 两侧都不缺字符（列表非空），且剩余需求完全吻合

        n = len(s)  # 原串长度，用于把右半段下标映射到翻转坐标
        m = n // 2  # 一半长度，左右两半逐位对齐
        t = s[m:][::-1]  # 右半段翻转，t[i] 与 s[i] 互为镜像字符
        s = s[:m]  # s 只保留左半段，后续都在长度 m 的坐标上比较
        pre1 = [[0] * 26 for _ in range(m + 1)]  # 左半段的字母频次前缀和
        pre2 = [[0] * 26 for _ in range(m + 1)]  # 翻转右半段的字母频次前缀和
        diff = [0] * (m + 1)  # diff[i]：前 i 位上两半不相等的个数
        for i, (c1, c2) in enumerate(zip(s, t), 1):  # 下标从 1 开始，同时取出两半的同位字符
            pre1[i] = pre1[i - 1][:]  # 切片复制上一项的频次，避免变成同一个列表对象的别名
            pre2[i] = pre2[i - 1][:]  # 右半段同样复制上一项
            pre1[i][ord(c1) - ord("a")] += 1  # 把 c1 计入左半段频次
            pre2[i][ord(c2) - ord("a")] += 1  # 把 c2 计入右半段频次
            diff[i] = diff[i - 1] + int(c1 != c2)  # 两半字符不相等则前缀不匹配数加一
        ans = []  # 逐个查询收集答案
        for a, b, c, d in queries:  # 解包当前查询的四元组
            c, d = n - 1 - d, n - 1 - c  # 把右半段区间映射到翻转坐标：原下标 x 对应 n-1-x
            ok = (  # 按左区间是否更靠前选择视角，check 的逻辑是对称的
                check(pre1, pre2, a, b, c, d)  # 左区间在前，直接判定
                if a <= c  # 条件：a 不大于 c
                else check(pre2, pre1, c, d, a, b)  # 否则交换左右半段的角色再判定
            )  # 条件表达式结束
            ans.append(ok)  # 记录该查询的结论
        return ans  # 返回全部结论
