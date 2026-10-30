# 题目：2168. 每个数字的频率都相同的不同子字符串的数量（Unique Substrings With Equal Digit Frequency）
# 思路：用二维前缀和 O(1) 求出任意区间内每个数字的出现次数，枚举所有子串检查非零频率是否全相同，再用集合去重计数。
# 时间复杂度：O(n^2)，枚举 O(n^2) 个区间、每次检查 10 个数字；空间复杂度：O(n^2)，前缀和表 O(n) 加最多 O(n^2) 个子串的去重集合。
class Solution:  # LeetCode 约定的题解类
    def equalDigitFrequency(self, s: str) -> int:  # s：只含数字字符的字符串；返回频率全相同的不同子串个数
        def check(i, j):  # 内部函数：判断闭区间 [i, j] 内各数字的出现频率是否全部相同
            v = set()  # v 收集出现过的不同频率值，一旦出现两种就说明不满足条件
            for k in range(10):  # 十个数字依次检查
                cnt = presum[j + 1][k] - presum[i][k]  # 借助前缀和在 O(1) 时间里求出数字 k 在区间 [i, j] 中的出现次数
                if cnt > 0:  # 只统计出现过的数字，次数为 0 的数字不参与比较
                    v.add(cnt)  # 把这个频率记进集合
                if len(v) > 1:  # 频率种类超过一种，说明各数字频率不同
                    return False  # 提前返回，省掉剩余数字的检查
            return True  # 所有出现过的数字频率都相同，满足条件

        n = len(s)  # n：字符串长度
        presum = [[0] * 10 for _ in range(n + 1)]  # presum[i][k]：前 i 个字符中数字 k 出现的次数
        for i, c in enumerate(s):  # 逐字符构建前缀和表
            presum[i + 1][int(c)] += 1  # 把当前字符转成数字，它在前 i+1 个字符里的计数先加一
            for j in range(10):  # 再把上一行（前 i 个字符）的统计全部继承过来
                presum[i + 1][j] += presum[i][j]  # 继承数字 j 到当前行，形成完整前缀和
        vis = set(s[i : j + 1] for i in range(n) for j in range(i, n) if check(i, j))  # 枚举所有起点 i 与终点 j，用 check 过滤后放进集合，重复子串自动抵消
        return len(vis)  # 集合的大小就是频率全相同的不同子串数量
