# 题目：16. 最接近的三数之和（3Sum Closest）
# 思路：排序后固定第一个数，左右双指针夹逼；按 |t - target| 更新最优解，和偏大就右指针左移，偏小就左指针右移。
# 时间复杂度：O(n^2)，外层枚举 + 内层双指针；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def threeSumClosest(self, nums: List[int], target: int) -> int:  # target 是目标值
        nums.sort()  # 排序后才能用双指针单调收缩
        n = len(nums)  # 数组长度
        ans = inf  # 用正无穷初始化“目前最优和”，保证第一次比较一定成立
        for i, v in enumerate(nums):  # 枚举第一个数 v 及其下标 i
            j, k = i + 1, n - 1  # 左右指针指向 i 右侧区间的最小值与最大值
            while j < k:  # 两指针未相遇就继续
                t = v + nums[j] + nums[k]  # 当前三数之和
                if t == target:  # 正好等于目标
                    return t  # 已是最优，直接返回
                if abs(t - target) < abs(ans - target):  # 当前和比已知最优更接近目标
                    ans = t  # 更新最优解
                if t > target:  # 和偏大，需要更小的数
                    k -= 1  # 右指针左移
                else:  # 和偏小，需要更大的数
                    j += 1  # 左指针右移
        return ans  # 返回最接近 target 的和
