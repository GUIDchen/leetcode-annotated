# 题目：1630. 等差子数组（Arithmetic Subarrays）
# 思路：对每个查询区间取最小/最大值算出公差，再用集合验证等差数列的每一项是否都存在。
# 时间复杂度：O(q·k)，q 为查询个数、k 为区间长度；空间复杂度：O(k)，每个查询用集合存区间元素。
class Solution:  # LeetCode 约定的题解类
    def checkArithmeticSubarrays(  # nums 是原数组，l/r 分别是各查询区间的左右端点（闭区间）；方法分行书写是为了不被行宽截断
        self, nums: List[int], l: List[int], r: List[int]  # 参数列表续行：self 为实例，nums 为原数组，l/r 为查询端点数组
    ) -> List[bool]:  # 返回布尔列表，第 i 项表示第 i 个查询区间的判定结果
        def check(nums, l, r):  # 内部函数：判断 nums[l..r] 这一段能否重排成等差数列
            n = r - l + 1  # 区间元素个数
            s = set(nums[l : l + n])  # 用切片取出区间元素并转成集合，便于 O(1) 查询
            a1, an = min(nums[l : l + n]), max(nums[l : l + n])  # 区间最小值与最大值（切片各取一次，语义一致）
            d, mod = divmod(an - a1, n - 1)  # divmod 同时得到公差 d 与余数 mod（判断能否被 n-1 整除）
            return mod == 0 and all((a1 + (i - 1) * d) in s for i in range(1, n))  # 余数为 0 且等差数列的 n 个项全部落在集合中，才算等差子数组

        return [check(nums, left, right) for left, right in zip(l, r)]  # 用 zip 把左右端点配对，逐个区间调用 check，返回结果列表
