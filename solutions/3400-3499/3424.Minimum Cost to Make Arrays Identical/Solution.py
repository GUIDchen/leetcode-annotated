# 3424. 将数组变相同的最小代价 / Minimum Cost to Make Arrays Identical
# 核心思路：方案一直接累加逐位绝对差；方案二先花 k 把 arr 任意重排，排序后与 brr 排序对齐即最优，再累加绝对差；两者取小
# 复杂度：时间 O(n·log n)（两次排序），空间 O(1) 额外空间（原地排序）
class Solution:  # 定义题解类
    def minCost(self, arr: List[int], brr: List[int], k: int) -> int:  # 求把 arr 变成 brr 所需的最小代价
        c1 = sum(abs(a - b) for a, b in zip(arr, brr))  # 方案一：不重排，直接按位求绝对差之和
        arr.sort()  # 方案二的第一步：花 k 的代价后可以把 arr 任意重排，排序即为最优顺序
        brr.sort()  # 对应地把 brr 也排序，使两数组按相同顺序对齐
        c2 = k + sum(abs(a - b) for a, b in zip(arr, brr))  # 排序对齐后的逐位绝对差之和，加上重排代价 k
        return min(c1, c2)  # 两种方案取较小值返回
