# 3756. 连接非零数字并乘以其数字和 II（Concatenate Non-Zero Digits and Multiply by Sum II）
# 核心思路：预处理“非零数字拼接前缀值”“数字和前缀”“非零数字个数前缀”，区间拼接值 = 前缀差乘 10 的非零数字个数次幂，再乘区间数字和即可 O(1) 回答每个查询。
# 复杂度：时间 O(n + q)（n 为串长、q 为查询数），空间 O(n + MX)。
mx = 10**5 + 1  # 预处理范围上界，覆盖题目允许的最大字符串长度
mod = 10**9 + 7  # 题目要求的取模值 1e9 + 7
pow10 = [1] * mx  # pow10[i] 表示 10 的 i 次幂对 mod 取模的结果
for i in range(1, mx):  # 从 1 次幂开始递推
    pow10[i] = pow10[i - 1] * 10 % mod  # 逐级乘 10 并取模，避免大整数开销


class Solution:  # 定义解法类
    def sumAndMultiply(self, s: str, queries: List[List[int]]) -> List[int]:  # 接口：返回每个查询区间的答案（拼接值乘数字和）
        n = len(s)  # n 为字符串长度，前缀数组统一开到 n + 1
        sum_d = [0] * (n + 1)  # sum_d 存数字和前缀
        cnt_n0 = [0] * (n + 1)  # cnt_n0 存非零数字个数前缀
        p = [0] * (n + 1)  # p 存把非零数字依次拼接后的前缀值（取模）
        for i, d in enumerate(map(int, s), 1):  # 从下标 1 开始逐字符建立前缀数组，d 为字符的数字值
            sum_d[i] = sum_d[i - 1] + d  # 数字和前缀：加上当前位的数字（零不影响和）
            cnt_n0[i] = cnt_n0[i - 1] + int(d > 0)  # 非零数字个数前缀：当前位大于 0 时加一
            p[i] = (p[i - 1] * 10 + d) % mod if d else p[i - 1]  # 零不参与拼接，前缀值保持；非零则左移一位加上该数字并取模

        ans = []  # 准备存放每个查询的答案
        for l, r in queries:  # 逐个处理查询区间 [l, r]
            n0 = cnt_n0[r + 1] - cnt_n0[l]  # 区间内非零数字的个数，用来确定拼接位数
            sd = sum_d[r + 1] - sum_d[l]  # 区间内的数字和
            x = p[r + 1] - p[l] * pow10[n0] % mod  # 前缀差去掉低位残留再乘 10 的幂次，得到区间拼接值（可能为负）
            ans.append(x * sd % mod)  # Python 取模会把负数归一到非负，乘区间数字和后再取模
        return ans  # 返回所有查询的答案
