# 题目：2601. 质数减法运算（Prime Subtraction Operation）
# 思路：用试除法筛出小于 max(nums) 的质数表，再从右往左扫描；遇到 nums[i] >= nums[i+1] 就二分找第一个大于差值的质数减掉。
# 时间复杂度：O(P·k + n·log k)，P 为最大值、k 为质数个数；空间复杂度：O(k) 存放质数表。
class Solution:  # LeetCode 约定的题解类
    def primeSubOperation(self, nums: List[int]) -> bool:  # nums：待调整的数组，返回能否通过若干次质数减法使其严格递增
        p = []  # 质数表 p，从左到右递增，供后面 bisect_right 使用
        for i in range(2, max(nums)):  # 只需筛到 max(nums) 以下：要减的质数必须严格小于当前元素
            for j in p:  # 用已筛出的小质数试除
                if i % j == 0:  # 能整除说明 i 是合数
                    break  # 直接跳出内层循环，i 不进质数表
            else:  # for-else：内层循环没有被 break 打断，说明 i 是质数
                p.append(i)  # 把质数 i 加入质数表

        n = len(nums)  # 数组长度
        for i in range(n - 2, -1, -1):  # 从右往左：右侧元素确定后，才能确定左侧允许的上界
            if nums[i] < nums[i + 1]:  # 已经满足严格递增
                continue  # 跳过，无需做减法
            j = bisect_right(p, nums[i] - nums[i + 1])  # 二分找第一个大于差值的质数下标
            if j == len(p) or p[j] >= nums[i]:  # 下标越界表示没有更大的质数；p[j] >= nums[i] 表示减完会小于等于 0
                return False  # 该位置无解，直接判负
            nums[i] -= p[j]  # 减去这个质数，使 nums[i] < nums[i + 1]
        return True  # 所有位置都处理完，返回成功
