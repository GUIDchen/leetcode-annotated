# 3769. 二进制反射排序 / Sort Integers by Binary Reflection
# 核心思路：先算出每个数的二进制反射值，再以 (反射值, 原数值) 为双关键字升序排序。
# 复杂度：时间 O(n log n · log V)，空间 O(log n)（排序本身）。
class Solution:  # 定义解法类
    def sortByReflection(self, nums: List[int]) -> List[int]:  # 按二进制反射值排序并返回数组
        def f(x: int) -> int:  # 反射值计算函数
            y = 0  # 反射结果
            while x:  # 逐位取出最低位
                y = y << 1 | (x & 1)  # 把最低位接到结果的最低位上，实现位序反转
                x >>= 1  # 原数右移一位
            return y  # 返回反射值

        nums.sort(key=lambda x: (f(x), x))  # 以 (反射值, 原数值) 为双关键字升序排序
        return nums  # 返回排序后的数组
