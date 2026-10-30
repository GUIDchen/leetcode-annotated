# 题目：2137. 通过倒水操作让所有的水桶所含水量相等（Pour Water Between Buckets to Make Water Levels Equal）
# 思路：二分答案水位 v，统计高于 v 可倒出的水量 a 与低于 v 需补入的水量 b（倒水有 loss% 损耗），a >= b 即 v 可达。
# 时间复杂度：O(n log(r / 1e-5))，二分约 50 次、每次 O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def equalizeWater(self, buckets: List[int], loss: int) -> float:  # buckets：各桶当前水量；loss：倒水损耗百分比；返回能拉平的最大水位
        def check(v):  # 内嵌判定函数：给定目标水位 v，判断是否可行
            a = b = 0  # 同时初始化两个累加器：a 为富余水量，b 为需要补入的水量
            for x in buckets:  # 逐个水桶统计
                if x >= v:  # 高于目标水位的水桶可以把多余的水倒出去（等于 v 时差值为 0，归到哪边都无影响）
                    a += x - v  # 多余部分计入可倒出的总量
                else:  # 低于目标水位的水桶需要补水
                    b += (v - x) * 100 / (100 - loss)  # 倒水有 loss% 损耗，需补 v-x 就得从富余侧多取，按比例放大
            return a >= b  # 富余水够填缺口即可行

        l, r = 0, max(buckets)  # 二分下界 0，上界取当前最高水位（答案不会超过最大的那一桶）
        while r - l > 1e-5:  # 浮点数二分：区间不够小就继续
            mid = (l + r) / 2  # 取中点为候选水位
            if check(mid):  # mid 可行，说明答案不小于 mid
                l = mid  # 抬高下界
            else:  # mid 不可行，说明答案更小
                r = mid  # 压低上界
        return l  # 返回收敛后的可行下界
