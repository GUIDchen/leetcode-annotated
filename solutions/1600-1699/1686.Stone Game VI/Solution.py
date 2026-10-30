# 题目：1686. 石子游戏 VI（Stone Game VI）
# 思路：按「Alice 得分 + Bob 得分」降序排出取石顺序，双方轮流取收益和最大的石子，累计总分后比较大小。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，额外的 (得分和, 下标) 列表。
class Solution:  # LeetCode 约定的题解类
    def stoneGameVI(self, aliceValues: List[int], bobValues: List[int]) -> int:  # aliceValues / bobValues 分别是两人取走同一颗石子能拿到的分
        vals = [(a + b, i) for i, (a, b) in enumerate(zip(aliceValues, bobValues))]  # 生成 (双方得分之和, 原下标)，下标用于之后回查原始得分
        vals.sort(reverse=True)  # 降序排序：收益和越大的石子越应该先被取走
        a = sum(aliceValues[i] for _, i in vals[::2])  # Alice 取第 0、2、4… 颗（切片 ::2）
        b = sum(bobValues[i] for _, i in vals[1::2])  # Bob 取第 1、3、5… 颗（切片 1::2）
        if a > b:  # Alice 总分更高
            return 1  # 返回 1 表示 Alice 获胜
        if a < b:  # Alice 总分更低
            return -1  # 返回 -1 表示 Bob 获胜
        return 0  # 两队总分相同返回 0
