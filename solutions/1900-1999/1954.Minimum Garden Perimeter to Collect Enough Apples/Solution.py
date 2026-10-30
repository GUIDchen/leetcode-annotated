# 题目：1954. 收集足够苹果的最小花园周长（Minimum Garden Perimeter to Collect Enough Apples）
# 思路：半边长 x 的方形花园中所有树的苹果数之和为 2x(x+1)(2x+1)（绝对值按行列求和），于是从小到大枚举 x，第一个满足需求的就是最优解。
# 时间复杂度：O(x)，x 为答案对应的半边长；空间复杂度：O(1)，只用了一个计数变量。
class Solution:  # LeetCode 约定的题解类
    def minimumPerimeter(self, neededApples: int) -> int:  # neededApples 是至少需要收集的苹果数，返回最小周长
        x = 1  # x 是花园的「半边长」，从 1 开始枚举，周长即 8x
        while 2 * x * (x + 1) * (2 * x + 1) < neededApples:  # 半边长 x 时苹果总数为 2x(x+1)(2x+1)，不足则继续扩大
            x += 1  # 扩大半边长；苹果总数单调递增，故首次满足即最小
        return x * 8  # 边长 2x 的正方形，周长为 8x
