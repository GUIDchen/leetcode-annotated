# 题目：2317. 操作后的最大异或和（Maximum XOR After Operations）
# 核心思路：操作能把元素任意一位清零，于是答案某位只要有任一元素提供过 1 即可保留，因此答案为所有元素的按位或。
# 时间复杂度：O(n)，只做一遍按位或归约；空间复杂度：O(1)，无需额外容器。
class Solution:  # LeetCode 约定的题解类
    def maximumXOR(self, nums: List[int]) -> int:  # nums：输入数组；返回经过任意次操作后能达到的最大异或和
        return reduce(or_, nums)  # reduce 把 or_（按位或）依次作用到所有元素上，聚合结果就是最大异或和
