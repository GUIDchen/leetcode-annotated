# 题目：2535. 数组元素和与数字和的绝对差（Difference Between Element Sum and Digit Sum of an Array）
# 思路：一次遍历，同时维护元素和 x 与数位和 y；每个元素用 while 循环不断取余、整除来拆位。
# 时间复杂度：O(n log M)，M 为元素最大值；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def differenceOfSum(self, nums: List[int]) -> int:  # nums 为输入数组，返回元素和与数字和之差
        x = y = 0  # 链式赋值：x 是元素和，y 是数位和，同时初始化为 0
        for v in nums:  # 遍历数组中的每个元素
            x += v  # 累加元素和
            while v:  # v 非 0 就继续拆位（这里 v 是循环变量副本，改写它不影响原数组）
                y += v % 10  # 把最低位数字累加到数位和
                v //= 10  # 整除 10 去掉最低位
        return x - y  # 返回元素和减数位和的结果
