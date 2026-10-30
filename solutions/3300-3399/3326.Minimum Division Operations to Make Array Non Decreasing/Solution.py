# 题目：3326. 使数组非递减的最少除法操作次数（Minimum Division Operations to Make Array Non Decreasing）
# 思路：预处理每个数的最小质因子；从右往左贪心，遇到逆序就把 nums[i] 除成最小质因子，若仍逆序则无解返回 -1。
# 时间复杂度：O(MX log log MX + n)，MX = 10^6；空间复杂度：O(MX)，存放最小质因子表。
mx = 10**6 + 1  # 元素上界 10^6，多留一位方便下面直接按下标访问
lpf = [0] * (mx + 1)  # lpf[x] 存 x 的最小质因子，初始全 0 表示还没被筛到
for i in range(2, mx + 1):  # 从小到大枚举可能的质因子
    if lpf[i] == 0:  # 仍为 0 说明 i 没被更小的数标记过，即 i 是质数
        for j in range(i, mx + 1, i):  # 用质数 i 扫它的所有倍数
            if lpf[j] == 0:  # 只填还没赋值的位置，先到先得保证是最小质因子
                lpf[j] = i  # 记录 j 的最小质因子


class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums 允许把元素换成它的真因子
        ans = 0  # 累计除法操作次数
        for i in range(len(nums) - 2, -1, -1):  # 从右往左处理，右侧元素已定，只需保证左侧不超过它
            if nums[i] > nums[i + 1]:  # 逆序，必须把 nums[i] 变小
                nums[i] = lpf[nums[i]]  # 一次操作能取到的最小值就是它的最小质因子
                if nums[i] > nums[i + 1]:  # 取到最小仍大于右边，说明无法补救
                    return -1  # 返回无解
                ans += 1  # 记一次操作
        return ans  # 返回最少操作次数
