# 题目：982. 按位与为零的三元组（Triples with Bitwise AND Equal To Zero）
# 思路：用 Counter 统计所有 (x, y) 组合的与值出现次数，再枚举与值与 z，把满足与为 0 的组合数累加。
# 时间复杂度：O(n^2 + V*n)，V 为与值种类数；空间复杂度：O(V)，存储计数表。
class Solution:  # LeetCode 约定的题解类
    def countTriplets(self, nums: List[int]) -> int:  # nums 是输入数组
        cnt = Counter(x & y for x in nums for y in nums)  # 双层生成式枚举所有 (x, y)，统计按位与结果的频次
        return sum(v for xy, v in cnt.items() for z in nums if xy & z == 0)  # 遍历计数表，凡与值再与 z 相与为 0 的，整组频次都计入答案
