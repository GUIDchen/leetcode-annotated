# 3591. 检查元素频次是否为质数（Check if Any Element Has Prime Frequency）
# 核心思路：用 Counter 统计每个元素的出现次数，再对每个频次做试除质数判定；命中任一质数频次即返回 true。
# 复杂度：时间 O(n + U·√n)，空间 O(U)，其中 U 为不同元素的个数。
class Solution:  # 主解类
    def checkPrimeFrequency(self, nums: List[int]) -> bool:  # 判断数组中是否存在出现次数为质数的元素
        def is_prime(x: int) -> bool:  # 辅助函数：判断 x 是否为质数
            if x < 2:  # 小于 2 的数不是质数
                return False  # 返回假
            return all(x % i for i in range(2, int(sqrt(x)) + 1))  # 试除 2 到 sqrt(x)，全都不整除即质数

        cnt = Counter(nums)  # 统计每个元素的出现次数
        return any(is_prime(x) for x in cnt.values())  # 任一频次为质数就返回真
