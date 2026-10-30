# 题目：2521. 数组乘积中的不同质因数数目（Distinct Prime Factors of Product of Array）
# 核心思路：乘积的质因数集合等于各元素质因数集合的并集，所以逐个元素试除分解质因数，把质因子放进集合去重，集合大小即答案。
# 时间复杂度：O(n * √m)，m 为元素最大值；空间复杂度：O(p)，p 为不同质因数的个数。
class Solution:  # LeetCode 约定的题解类
    def distinctPrimeFactors(self, nums: List[int]) -> int:  # nums：输入数组；返回所有元素乘积中不同质因数的个数
        s = set()  # 用集合收集质因数，天然去重
        for n in nums:  # 逐个元素分解质因数
            i = 2  # 试除因子从最小的质数 2 开始
            while i <= n // i:  # 只需试到 √n，i <= n // i 等价于 i * i <= n 且不会溢出
                if n % i == 0:  # i 能整除 n，说明 i 是质因子
                    s.add(i)  # 加入集合，重复出现也只记一次
                    while n % i == 0:  # 把 n 中所有因子 i 除干净，避免同一质因子重复统计
                        n //= i  # 继续除，直到 i 不再是因子
                i += 1  # 试除下一个因子
            if n > 1:  # 若剩下 n > 1，说明它本身就是最后一个质因数
                s.add(n)  # 把它也加入集合
        return len(s)  # 集合大小即不同质因数的个数
