# 题目：3751. 范围内总波动值 I（Total Waviness of Numbers in Range I）
# 核心思路：上界只有 1e5，直接枚举区间内每个数并按位判断峰谷即可。把数位从低位到高位拆进列表（相邻关系不变），不足 3 位波动值为 0，否则统计中间严格大于或严格小于两侧的位数并累加。
# 复杂度：时间 O((num2 - num1 + 1) * log num2)，每个数都要拆位检查；空间 O(log num2)，数位列表大小与位数成正比。
class Solution:  # LeetCode 约定的题解类
    def totalWaviness(self, num1: int, num2: int) -> int:  # 返回闭区间 [num1, num2] 内所有数字的波动值之和
        def f(x: int) -> int:  # 辅助函数：返回整数 x 的波动值，即其中峰与谷的个数
            nums = []  # nums 存放 x 的各个数位（低位在前）
            while x:  # 反复取最低位，把 x 的每一位拆出来
                nums.append(x % 10)  # 取最低位追加到 nums
                x //= 10  # x 去掉最低位
            m = len(nums)  # m 是 x 的位数
            if m < 3:  # 不足 3 位的数字没有峰谷
                return 0  # 波动值为 0
            s = 0  # s 统计峰和谷的总数
            for i in range(1, m - 1):  # 首尾数位不可能是峰谷，只遍历中间的数位
                if nums[i] > nums[i - 1] and nums[i] > nums[i + 1]:  # 中间位严格大于两侧相邻位，说明它是一个峰
                    s += 1  # 峰的数量加一
                elif nums[i] < nums[i - 1] and nums[i] < nums[i + 1]:  # 中间位严格小于两侧相邻位，说明它是一个谷
                    s += 1  # 谷的数量加一
            return s  # 返回 x 的波动值

        return sum(f(x) for x in range(num1, num2 + 1))  # 对区间内每个数求波动值并求和
