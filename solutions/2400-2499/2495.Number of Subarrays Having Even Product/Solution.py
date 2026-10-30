# 题目：2495. 乘积为偶数的子数组数（Number of Subarrays Having Even Product）
# 思路：乘积为偶数 等价于 子数组内至少有一个偶数；枚举右端点 i，左端点只要不超过最近偶数下标 last 就都合法。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def evenProduct(self, nums: List[int]) -> int:  # nums 是输入数组，返回乘积为偶数的子数组个数
        ans, last = 0, -1  # ans 累计答案；last 是最近出现的偶数下标，-1 表示还没遇到偶数
        for i, v in enumerate(nums):  # 枚举子数组右端点 i，同时取出元素值 v
            if v % 2 == 0:  # 当前元素是偶数
                last = i  # 更新最近偶数的位置
            ans += last + 1  # 左端点取 0..last 共 last+1 个，区间必含偶数，乘积为偶数
        return ans  # 返回统计出的子数组个数
