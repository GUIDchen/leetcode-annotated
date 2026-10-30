# 题目：2560. 打家劫舍 IV（House Robber IV）
# 核心思路：二分答案 x，用贪心把「不相邻」变成上一间偷的位置 + 1 的检查，统计能力值为 x 时最多能偷几间。
# 时间复杂度：O(n log M)，M 为金额最大值；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minCapability(self, nums: List[int], k: int) -> int:  # nums：每间房的金额；k：至少要偷的间数
        def f(x):  # 可行性函数：能力值为 x 时能否偷满 k 间
            cnt, j = 0, -2  # cnt 是已偷间数；j 是上一次偷的下标，初值 -2 表示还没偷过
            for i, v in enumerate(nums):  # 同时拿到下标 i 与金额 v
                if v > x or i == j + 1:  # 金额超过能力值，或与上一次偷的房相邻
                    continue  # 这间不能偷，跳过
                cnt += 1  # 偷下这间
                j = i  # 记录本次偷的位置，供下一次相邻性判断
            return cnt >= k  # 能偷到 k 间就说明 x 可行

        return bisect_left(range(max(nums) + 1), True, key=f)  # 在单调布尔序列上二分，直接定位第一个 True（key= 需 Python 3.10+）
