# 题目：2460. 对数组执行操作（Apply Operations to an Array）
# 思路：第一遍从左到右合并相邻相等的元素（前一个乘 2、后一个置 0），第二遍把所有非零元素按原顺序紧凑填到数组前面。
# 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，额外开一个等长结果数组。
class Solution:  # LeetCode 约定的题解类
    def applyOperations(self, nums: List[int]) -> List[int]:  # nums：待处理的数组，原地修改
        n = len(nums)  # 数组长度
        for i in range(n - 1):  # 从左到右扫描，只到倒数第二个，保证 i+1 不越界
            if nums[i] == nums[i + 1]:  # 只有相邻元素相等时才需要合并
                nums[i] <<= 1  # 左移一位等价于乘 2，把修改后的值放回前一个位置
                nums[i + 1] = 0  # 后一个位置被消耗，置为 0
        ans = [0] * n  # 结果数组，长度与原数组相同，先全部填 0
        i = 0  # 结果数组的写指针，指向下一个待写入的空位
        for x in nums:  # 第二遍：把所有非零元素按原顺序搬到前面
            if x:  # x 非 0 才需要保留
                ans[i] = x  # 写入当前空位
                i += 1  # 写指针后移，指向下一个空位
        return ans  # 其余位置保持 0，返回处理后的数组
