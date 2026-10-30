# 题目：1679. K 和数对的最大数目（Max Number of K-Sum Pairs）
# 思路：先排序，再用左右双指针从两端逼近；和等于 k 就配对并同时内移，和偏大右指针左移，和偏小左指针右移。
# 时间复杂度：O(n log n)，排序主导，双指针扫描为 O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxOperations(self, nums: List[int], k: int) -> int:  # nums：整数数组；k：目标和；返回最多能凑出的数对数目
        nums.sort()  # 排序使数组递增，之后才能用双指针从两端向中间收缩
        l, r, ans = 0, len(nums) - 1, 0  # l、r 分别是左右指针，ans 记录已配成的数对数目
        while l < r:  # 两指针还没相遇，就继续尝试配对
            s = nums[l] + nums[r]  # 当前左右两端元素之和
            if s == k:  # 和恰好等于 k，可以配成一对
                ans += 1  # 数对数目加一
                l, r = l + 1, r - 1  # 两个数都已用掉，左右指针同时向中间移动
            elif s > k:  # 和太大，需要更小的数，右指针左移
                r -= 1  # 右指针左移，让下一轮的和变小
            else:  # 和太小，需要更大的数，左指针右移
                l += 1  # 左指针右移，让下一轮的和变大
        return ans  # 返回最多能凑出的数对数目
