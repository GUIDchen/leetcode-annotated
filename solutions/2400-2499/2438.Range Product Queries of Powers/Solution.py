# 题目：2438. 二的幂数组中查询范围内的乘积（Range Product Queries of Powers）
# 思路：用 lowbit（n & -n）不断剥出最低位的 1，得到递增的 2 的幂数组；再对每个查询区间累乘并取模。
# 时间复杂度：O(log n + Σ(r-l+1))；空间复杂度：O(log n)，powers 最多保存 log2(n)+1 个元素。
class Solution:  # LeetCode 约定的题解类
    def productQueries(self, n: int, queries: List[List[int]]) -> List[int]:  # n：被分解的正整数；queries：若干 [l, r] 查询区间
        powers = []  # 存放 n 的二进制分解出的 2 的幂，从小到大
        while n:  # 只要 n 还有二进制位就继续剥
            x = n & -n  # lowbit：取出最低位的 1 所代表的 2 的幂
            powers.append(x)  # 按从小到大的顺序收集这个幂
            n -= x  # 去掉这一位，下一轮取更高位
        mod = 10**9 + 7  # 题目要求的取模常量
        ans = []  # 保存每个查询的答案
        for l, r in queries:  # 逐个处理查询区间（左右端点均为闭区间）
            x = 1  # 区间乘积的累乘器
            for i in range(l, r + 1):  # 遍历区间内的每个 2 的幂
                x = x * powers[i] % mod  # 边乘边取模，Python 大整数天然不会溢出
            ans.append(x)  # 记录本查询的乘积
        return ans  # 返回所有查询的结果
