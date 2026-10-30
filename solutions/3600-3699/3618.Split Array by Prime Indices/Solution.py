# 3618. Split Array by Prime Indices / 根据质数下标分割数组
# 核心思路：模块加载时用埃氏筛预处理质数表，再按下标是否为质数给元素赋正负号求和，最后取绝对值。
# 复杂度：筛法预处理 O(M log log M) 且只做一次，单次查询 O(n)；空间复杂度 O(M)。
m = 10**5 + 10  # 质数表上界，略大于数组可能的最大长度
primes = [True] * m  # primes[i] 表示下标 i 是否为质数，初始全为 True
primes[0] = primes[1] = False  # 0 和 1 不是质数
for i in range(2, m):  # 从 2 开始枚举
    if primes[i]:  # 只有质数才需要筛掉它的倍数
        for j in range(i + i, m, i):  # 从 i 的两倍开始标记合数
            primes[j] = False  # 标记为非质数


class Solution:  # 定义题解类
    def splitArray(self, nums: List[int]) -> int:  # 按下标是否为质数分组求和后返回两组的绝对差
        return abs(sum(x if primes[i] else -x for i, x in enumerate(nums)))  # 质数下标取正、非质数下标取负，求和后取绝对值
