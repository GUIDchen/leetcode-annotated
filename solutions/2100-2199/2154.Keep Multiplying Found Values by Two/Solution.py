# 题目：2154. 将找到的值乘以 2（Keep Multiplying Found Values by Two）
# 思路：把数组放进集合，只要 original 还在集合里就不断乘 2，直到集合中查不到为止。
# 时间复杂度：O(n + log M)，建集合 O(n)、倍增 O(log M)（M 为最终值）；空间复杂度：O(n)，集合存放去重后的元素。
class Solution:  # LeetCode 约定的题解类
    def findFinalValue(self, nums: List[int], original: int) -> int:  # nums：输入数组；original：初始值；返回最终值
        s = set(nums)  # 用集合保存数组元素，便于 O(1) 判断某个值是否存在
        while original in s:  # 只要原值还在集合中，就继续倍增
            original <<= 1  # 左移一位等价于乘 2
        return original  # 集合里查不到该值了，返回最终结果
