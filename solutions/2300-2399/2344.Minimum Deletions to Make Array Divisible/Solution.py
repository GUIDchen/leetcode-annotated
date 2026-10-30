# 题目：2344. 使数组可以被整除的最少删除次数（Minimum Deletions to Make Array Divisible）
# 思路：先求出 numsDivide 所有元素的最大公约数 x，再排序 nums，第一个能整除 x 的元素下标就是最少删除次数。
# 时间复杂度：O(m log C + n log n)；空间复杂度：O(1)（不计排序实现的额外开销）。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], numsDivide: List[int]) -> int:  # nums 是可删除元素的数组，numsDivide 要求每个元素都能被整除
        x = numsDivide[0]  # 用第一个元素作为 gcd 的初值
        for v in numsDivide[1:]:  # 从第二个元素开始逐个合并
            x = gcd(x, v)  # 两数最大公约数迭代，最终得到整个 numsDivide 的 gcd
        nums.sort()  # 原地升序排序，下标天然表示要删除的元素个数
        for i, v in enumerate(nums):  # 从小到大依次检查每个元素
            if x % v == 0:  # v 能整除 x，也就能整除 numsDivide 中每个元素
                return i  # 前面 i 个更小的元素都不能整除，必须删除，故答案为 i
        return -1  # 没有任何元素能整除 x，返回 -1 表示不可能
