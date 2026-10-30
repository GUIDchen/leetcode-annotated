# 题目：1196. 最多可以买到的苹果数量（How Many Apples Can You Put into the Basket）
# 思路：重量升序排序后从最轻的开始装，累加重量，一超过 5000 就返回已装个数。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，原地排序只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxNumberOfApples(self, weight: List[int]) -> int:  # weight 是每个苹果的重量，返回最多能装进容量 5000 的篮子的苹果个数
        weight.sort()  # 原地升序排序，贪心地先装最轻的
        s = 0  # s 记录已装苹果的总重量
        for i, x in enumerate(weight):  # 同时取得苹果下标 i 与重量 x
            s += x  # 把当前苹果重量计入总重
            if s > 5000:  # 总重超过篮子容量上限 5000
                return i  # 当前这个装不下，前面已装好的 i 个就是答案
        return len(weight)  # 全部装下，返回苹果总数
