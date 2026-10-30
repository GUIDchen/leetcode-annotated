# 3688. 偶数的按位或运算 / Bitwise OR of Even Numbers in an Array
# 核心思路：用 reduce 把所有偶数依次按位或起来，初始值为按位或的单位元 0
# 时间复杂度 O(n)，空间复杂度 O(1)
class Solution:  # 题解类
    def evenNumberBitwiseORs(self, nums: List[int]) -> int:  # 返回所有偶数的按位或结果
        return reduce(or_, (x for x in nums if x % 2 == 0), 0)  # 过滤出偶数后从 0 开始依次按位或
