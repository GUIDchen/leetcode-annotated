# 题目：3116. 单面值组合的第 K 小金额（Kth Smallest Amount With Single Denomination Combination）
# 思路：对答案二分，用容斥原理统计不超过 mx 的合法金额个数，再用 bisect_left 找第一个满足「个数 >= k」的 mx。
# 时间复杂度：O(2^m·m·log(1e11))，m 为面值个数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findKthSmallest(self, coins: List[int], k: int) -> int:  # coins：面值数组；k：要求的第 k 小金额
        def check(mx: int) -> bool:  # 闭包：判断不超过 mx 的合法金额是否至少有 k 个
            cnt = 0  # 统计 [1, mx] 内能被至少一种面值整除的金额个数
            for i in range(1, 1 << len(coins)):  # 枚举所有非空子集，用容斥去重
                v = 1  # 当前子集面值的最小公倍数
                for j, x in enumerate(coins):  # 逐位检查子集里包含哪些面值
                    if i >> j & 1:  # 第 j 个面值属于当前子集
                        v = lcm(v, x)  # 把该面值并入最小公倍数
                        if v > mx:  # 公倍数已超过 mx，后续倍数都不会有贡献
                            break  # 提前退出内层枚举
                m = i.bit_count()  # 子集大小决定容斥的符号
                if m & 1:  # 奇数个面值：加
                    cnt += mx // v  # 不超过 mx 的 v 的倍数共有 mx // v 个
                else:  # 偶数个面值：减
                    cnt -= mx // v  # 容斥去掉重复计数的部分
            return cnt >= k  # 合法金额够 k 个，说明答案不超过 mx

        return bisect_left(range(10**11), True, key=check)  # 在 [0, 1e11) 上二分第一个 check 为真的位置，即第 k 小金额
