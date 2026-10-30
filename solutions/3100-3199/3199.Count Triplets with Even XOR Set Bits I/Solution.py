# 3199. 用偶数异或设置位计数三元组 I（Count Triplets with Even XOR Set Bits I）
# 核心思路：x^y^z 的 popcount 奇偶性等于三者 popcount 奇偶性之和的奇偶性；用 Counter 统计 a、b、c 中奇/偶的个数，枚举组合后乘法原理累加。
# 复杂度：时间 O(|a|+|b|+|c|)，空间 O(1)

class Solution:  # 定义题解类
    def tripletCount(self, a: List[int], b: List[int], c: List[int]) -> int:  # 返回满足异或结果 popcount 为偶数的三元组数量
        cnt1 = Counter(x.bit_count() & 1 for x in a)  # 统计 a 中元素 bit_count 奇偶性的频次
        cnt2 = Counter(x.bit_count() & 1 for x in b)  # 统计 b 中元素 bit_count 奇偶性的频次
        cnt3 = Counter(x.bit_count() & 1 for x in c)  # 统计 c 中元素 bit_count 奇偶性的频次
        ans = 0  # 满足条件的三元组数量
        for i in range(2):  # 枚举 a 中元素 popcount 的奇偶性
            for j in range(2):  # 枚举 b 中元素 popcount 的奇偶性
                for k in range(2):  # 枚举 c 中元素 popcount 的奇偶性
                    if (i + j + k) & 1 ^ 1:  # 三者奇偶性之和为偶数（等价于异或结果 popcount 为偶数）
                        ans += cnt1[i] * cnt2[j] * cnt3[k]  # 乘法原理：累加三类元素的可选数量乘积
        return ans  # 返回结果
