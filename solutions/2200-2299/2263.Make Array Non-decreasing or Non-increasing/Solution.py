# 题目：2263. 数组变为有序的最小操作次数（Make Array Non-decreasing or Non-increasing）
# 思路：只需分别尝试非递减与非递增。把数组反转后求非递减就等价于求原数组的非递增；非递减用 DP，f[i][j] 表示前 i 个数非递减且第 i 个数取 j 的最小代价，配合上一行前缀最小值做 O(1) 转移。
# 时间复杂度：O(n * V)，V = 1001 为取值上界；空间复杂度：O(n * V)，两次求解同阶。
class Solution:  # LeetCode 约定的题解类
    def convertArray(self, nums: List[int]) -> int:  # nums 是原数组，返回变成非递减或非递增所需的最小操作次数
        def solve(nums):  # 内部辅助函数：求把 nums 变成非递减的最小代价
            n = len(nums)  # 元素个数
            f = [[0] * 1001 for _ in range(n + 1)]  # 二维 DP：f[i][j] 为前 i 个数非递减且第 i 个数取 j 的最小代价
            for i, x in enumerate(nums, 1):  # 从 1 开始编号，逐个处理原数组元素 x
                mi = inf  # 滚动维护上一行 f[i-1][0..j] 的前缀最小值
                for j in range(1001):  # 枚举当前元素的取值 j（题目保证 0 <= nums[i] <= 1000）
                    if mi > f[i - 1][j]:  # 用 f[i-1][j] 更新前缀最小值
                        mi = f[i - 1][j]  # 更新后 mi 就是前一个数取 0..j 时的最小代价
                    f[i][j] = mi + abs(x - j)  # 转移：前驱最小代价 + 把 x 改成 j 的代价
            return min(f[n])  # 最后一个数取任何值都合法，返回整行最小值

        return min(solve(nums), solve(nums[::-1]))  # 非递减与反转后的非递减（即原数组非递增）两种情况取较小值
