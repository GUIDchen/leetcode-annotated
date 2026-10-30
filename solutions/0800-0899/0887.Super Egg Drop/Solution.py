# 题目：887. 鸡蛋掉落（Super Egg Drop）
# 思路：dfs(i, j) 表示 j 个鸡蛋、i 层楼的最少操作次数；在第一次扔的楼层上二分，取两侧代价的较大值加 1，并用 @cache 记忆化。
# 时间复杂度：O(k * n * log n)，每个状态一次二分；空间复杂度：O(k * n)，缓存所有已求状态。
class Solution:  # LeetCode 约定的题解类
    def superEggDrop(self, k: int, n: int) -> int:  # k 个鸡蛋，n 层楼
        @cache  # 记忆化装饰器：相同参数只计算一次（LeetCode 环境已提供 cache）
        def dfs(i: int, j: int) -> int:  # i 层楼、j 个鸡蛋时确定答案所需的最少操作次数
            if i < 1:  # 0 层楼不需要任何操作
                return 0  # 直接返回 0
            if j == 1:  # 只有一个鸡蛋时只能逐层往上试
                return i  # 最坏情况要试 i 次
            l, r = 1, i  # 在 1..i 层之间二分「第一次扔的楼层」
            while l < r:  # 二分查找最优楼层
                mid = (l + r + 1) >> 1  # 取上中点，保证区间收缩且不死循环
                a = dfs(mid - 1, j - 1)  # 碎了：用 j-1 个鸡蛋去试下面 mid-1 层
                b = dfs(i - mid, j)  # 没碎：仍用 j 个鸡蛋去试上面 i-mid 层
                if a <= b:  # 碎了的代价不大于没碎的代价，可以往更高层扔
                    l = mid  # 下界抬到 mid
                else:  # 否则最优楼层在更低的区间
                    r = mid - 1  # 上界降到 mid-1
            return max(dfs(l - 1, j - 1), dfs(i - l, j)) + 1  # 最坏情况取两侧最大值，加本次这一扔

        return dfs(n, k)  # 从 k 个鸡蛋、n 层楼的初始状态求解
