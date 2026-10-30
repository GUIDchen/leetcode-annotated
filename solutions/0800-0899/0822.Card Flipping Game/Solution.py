# 题目：822. 翻转卡片游戏（Card Flipping Game）
# 思路：正反面数字相同的卡片无论怎么翻都会露出这个数，永远不能作为答案，先收集成「坏数字」集合；再在正反面所有数字里找不属于该集合的最小值。
# 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，坏数字集合。
class Solution:  # LeetCode 约定的题解类
    def flipgame(self, fronts: List[int], backs: List[int]) -> int:  # fronts/backs：每张卡片的正面与反面
        s = {a for a, b in zip(fronts, backs) if a == b}  # 正反面相同的数字无法避开，构成「坏数字」集合
        return min((x for x in chain(fronts, backs) if x not in s), default=0)  # 在所有卡片的正面和反面里找不属于坏数字的最小值；都不行时返回 0
