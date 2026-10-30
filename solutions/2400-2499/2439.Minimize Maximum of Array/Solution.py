# 题目：2439. 最小化数组中的最大值（Minimize Maximum of Array）
# 思路：二分答案 mx，从右往左贪心把超过 mx 的部分 d 传给左侧元素，最后检查 nums[0] + d 是否不超过 mx。
# 时间复杂度：O(n log max(nums))，二分 O(log max) 轮、每轮 O(n)；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimizeArrayValue(self, nums: List[int]) -> int:  # nums：非负整数数组，元素的值只能向左挪动
        def check(mx):  # 判定函数：能否把数组调整成所有元素都不超过 mx
            d = 0  # d 记录从右侧溢出、需要继续向左传递的数值总量
            for x in nums[:0:-1]:  # 切片 nums[:0:-1] 生成从末尾到下标 1 的倒序序列（不含 nums[0]）
                d = max(0, d + x - mx)  # 当前元素加上此前的溢出量，超出 mx 的部分左传，不足则清零
            return nums[0] + d <= mx  # 首位接住全部溢出量后仍不超过 mx，说明 mx 可行

        left, right = 0, max(nums)  # 二分区间：答案至少为 0，至多为数组当前最大值
        while left < right:  # 二分查找最小的可行 mx
            mid = (left + right) >> 1  # 取中点（右移一位等价于整除 2）
            if check(mid):  # 若 mid 可行
                right = mid  # 保留 mid 作为上界，继续找更小的答案
            else:  # 若 mid 不可行
                left = mid + 1  # 答案必然大于 mid
        return left  # 二分收敛时 left == right，就是最小化的最大值
