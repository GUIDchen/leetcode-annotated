# 题目：3074. 重新分装苹果（Apple Redistribution into Boxes）
# 思路：贪心。苹果总数固定，优先用容量最大的箱子，按容量降序累减，剩余苹果数首次不超过 0 时的箱子数就是答案。
# 时间复杂度：O(m log m + n)，排序加求苹果总和；空间复杂度：O(1)，排序在原数组上进行。
class Solution:  # LeetCode 约定的题解类
    def minimumBoxes(self, apple: List[int], capacity: List[int]) -> int:  # apple：每个包裹的苹果数；capacity：每个箱子的容量；返回最少需要选用的箱子数
        capacity.sort(reverse=True)  # 容量从大到小排序，保证贪心时总是先拿最大的箱子
        s = sum(apple)  # 苹果总数，即需要装箱的苹果总量
        for i, c in enumerate(capacity, 1):  # 下标从 1 开始枚举，i 就是当前已经选用的箱子数，c 是它的容量
            s -= c  # 用掉这个箱子
            if s <= 0:  # 剩余苹果不超过 0，说明这 i 个箱子已经能装下全部苹果
                return i  # 箱子数最少，直接返回 i
