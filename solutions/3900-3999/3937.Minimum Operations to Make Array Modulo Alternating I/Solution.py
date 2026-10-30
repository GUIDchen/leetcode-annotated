# 3937. 使数组变为模交替数组的最少操作次数 I / Minimum Operations to Make Array Modulo Alternating I
# 核心思路：先原地对 k 取模，再枚举偶数位与奇数位的两个不同目标模值，按模 k 最短距离累加操作次数并取最小值。
# 复杂度：时间 O(n * k^2)，空间 O(1)。
class Solution:  # 题解类定义
    def minOperations(self, nums: list[int], k: int) -> int:  # 主函数：返回最少操作次数
        for i, v in enumerate(nums):  # 遍历数组，准备原地取模
            nums[i] = v % k  # 每个元素先对 k 取模
        ans = inf  # 答案初始化为无穷大
        for x in range(k):  # 枚举偶数下标的模目标值 x
            for y in range(k):  # 枚举奇数下标的模目标值 y
                if x != y:  # 两个目标值必须不同
                    cnt = 0  # 当前方案的代价
                    for i, v in enumerate(nums):  # 遍历数组累加代价
                        target = x if i % 2 == 0 else y  # 按下标奇偶选择目标值
                        diff = abs(target - v)  # 当前值与目标的直接差值
                        cnt += min(diff, k - diff)  # 模 k 意义下取更短的距离
                    ans = min(ans, cnt)  # 更新全局最优答案
        return ans  # 返回最少操作次数
