# 题目：2847. 给定数字乘积的最小数字（Smallest Number With Given Digit Product）
# 思路：从大到小用 9..2 贪心分解 n，尽量用大因子使数位最少；再把因子按升序拼接，得到数值最小的答案。
# 时间复杂度：O(9 * log n)，因子分解近似对数级；空间复杂度：O(1)，只用到长度 10 的计数数组与结果串。
class Solution:  # LeetCode 约定的题解类
    def smallestNumber(self, n: int) -> str:  # n：给定的数位乘积
        cnt = [0] * 10  # cnt[d] 记录因子 d 使用了多少次
        for i in range(9, 1, -1):  # 从 9 递减到 2，优先用大因子
            while n % i == 0:  # 只要 n 还能被 i 整除就继续拆
                n //= i  # 把因子 i 从 n 中除掉
                cnt[i] += 1  # 因子 i 的使用次数加一
        if n > 1:  # 除剩下的 n 大于 1，说明含大于等于 11 的质因子，无法由单个数字拼出
            return "-1"  # 无解，按题目要求返回 "-1"
        ans = "".join(str(i) * cnt[i] for i in range(2, 10))  # 按因子从小到大的顺序重复拼接，得到数值最小的答案
        return ans if ans else "1"  # 空串时说明 n 等价于 1，答案取 "1"
