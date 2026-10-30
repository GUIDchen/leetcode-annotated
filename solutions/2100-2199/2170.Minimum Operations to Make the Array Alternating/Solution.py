# 题目：2170. 使数组变成交替数组的最少操作数（Minimum Operations to Make the Array Alternating）
# 思路：按奇偶下标分别统计出现次数最多的两个值；两侧最优值不同就各取最大，相同时枚举「一取最大、另一取次大」两种搭配。
# 时间复杂度：O(n)，切片与计数各扫一遍；空间复杂度：O(n)，Counter 保存频次。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, nums: List[int]) -> int:  # nums 是输入数组；返回最少操作数，每次可把任意一个元素改成任意值
        def f(i: int) -> Tuple[int, int, int, int]:  # 内部函数 f(i)：统计下标 i, i+2, i+4, ... 上的元素，返回 (最优值, 次数, 次优值, 次数)
            k1 = k2 = 0  # k1、k2 分别是出现最多与次多的值；0 表示「还没有」
            cnt = Counter(nums[i::2])  # 用切片 nums[i::2] 取出同奇偶的所有元素，Counter 一次性统计频次
            for k, v in cnt.items():  # 打擂台：遍历每个 (值, 次数)
                if cnt[k1] < v:  # Counter 对缺失键返回 0，所以 k1 仍为 0 时也能安全比较
                    k2, k1 = k1, k  # 当前次数更大：原来的最大值降级为次大值，k 成为新的最大值
                elif cnt[k2] < v:  # 没超过最大值，再单独判断能否成为新的次大值（同样借助 Counter 的默认 0）
                    k2 = k  # 更新次大值
            return k1, cnt[k1], k2, cnt[k2]  # 返回最优值与次优值以及各自的次数

        a, b = f(0), f(1)  # 分别分析偶数下标 a 与奇数下标 b：a[0]/a[2] 是值，a[1]/a[3] 是对应次数
        n = len(nums)  # 数组长度，也就是最多能保留的元素个数
        if a[0] != b[0]:  # 两侧最优值不同，可以同时保留，互不冲突
            return n - (a[1] + b[1])  # 其余元素全部需要修改
        return n - max(a[1] + b[3], a[3] + b[1])  # 最优值相同时只能一取最大、一取次大，两种搭配保留更多的那种
