# 题目：303. 区域和检索 - 数组不可变（Range Sum Query - Immutable）
# 思路：用 accumulate 一次性生成前缀和，s[i] 表示前 i 个元素之和，区间和由两个前缀和相减得到。
# 时间复杂度：构造 O(n)、每次查询 O(1)；空间复杂度：O(n)，保存 n+1 个前缀和。
class NumArray:  # LeetCode 约定的题解类
    def __init__(self, nums: List[int]):  # 构造函数：nums 是输入数组
        self.s = list(accumulate(nums, initial=0))  # accumulate 生成累加值，initial=0 让首项为 0、长度变成 n+1

    def sumRange(self, left: int, right: int) -> int:  # 查询闭区间 [left, right] 的元素和
        return self.s[right + 1] - self.s[left]  # 减去前 left 项，剩下的就是区间和，O(1)


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# param_1 = obj.sumRange(left,right)
