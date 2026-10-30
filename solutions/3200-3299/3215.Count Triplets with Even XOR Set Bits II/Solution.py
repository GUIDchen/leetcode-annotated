# 题目：3215. 用偶数异或设置位计数三元组 II（Count Triplets with Even XOR Set Bits II）
# 思路：三个数异或后的设置位个数奇偶性等于三者设置位个数奇偶性之和的奇偶性，因此只按奇偶统计各数组元素个数，再枚举 2×2×2 种奇偶组合相乘累加。
# 时间复杂度：O(|a| + |b| + |c|)，只需线性扫一遍；空间复杂度：O(1)，仅两个计数桶。
class Solution:  # LeetCode 约定的题解类
    def tripletCount(self, a: List[int], b: List[int], c: List[int]) -> int:  # a、b、c：三个整数数组
        cnt1 = Counter(x.bit_count() & 1 for x in a)  # 按设置位个数的奇偶性统计 a 中元素个数
        cnt2 = Counter(x.bit_count() & 1 for x in b)  # 按设置位个数的奇偶性统计 b 中元素个数
        cnt3 = Counter(x.bit_count() & 1 for x in c)  # 按设置位个数的奇偶性统计 c 中元素个数
        ans = 0  # 满足条件的三元组计数
        for i in range(2):  # 枚举 a 中元素设置位个数的奇偶性
            for j in range(2):  # 枚举 b 中元素设置位个数的奇偶性
                for k in range(2):  # 枚举 c 中元素设置位个数的奇偶性
                    if (i + j + k) & 1 ^ 1:  # 先取最低位得到奇偶性，再异或 1 得到「偶数」判定
                        ans += cnt1[i] * cnt2[j] * cnt3[k]  # 该组合下三种取值的任意搭配都满足条件，缺失的键按 0 计
        return ans  # 返回满足条件的三元组总数
