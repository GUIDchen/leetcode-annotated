# 题目：2091. 从数组中移除最大值和最小值（Removing Minimum and Maximum From Array）
# 思路：先一次遍历定位最小值与最大值下标（设小者在左、大者在右），再比较三种删法：都从左边删、都从右边删、小的从左边删且大的从右边删，取次数最少者。
# 时间复杂度：O(n)，只需一次遍历加常数次比较；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumDeletions(self, nums: List[int]) -> int:  # nums：原数组；返回删掉最大值和最小值所需的最少操作次数
        mi = mx = 0  # mi/mx 分别记录最小值、最大值的下标，初值都指向 0 号元素
        for i, num in enumerate(nums):  # 一次遍历同时找最大值与最小值的位置
            if num < nums[mi]:  # 发现比当前最小值更小的元素
                mi = i  # 更新最小值下标
            if num > nums[mx]:  # 发现比当前最大值更大的元素（与上一个 if 互相独立，不能用 elif）
                mx = i  # 更新最大值下标
        if mi > mx:  # 保证 mi 是较左的下标、mx 是较右的下标
            mi, mx = mx, mi  # 用元组解包交换两个下标，方便后面统一表述
        return min(mx + 1, len(nums) - mi, mi + 1 + len(nums) - mx)  # 三种删法取最小：①都从左边删需 mx+1 次；②都从右边删需 len-mi 次；③小的从左边删、大的从右边删需 mi+1+len-mx 次
