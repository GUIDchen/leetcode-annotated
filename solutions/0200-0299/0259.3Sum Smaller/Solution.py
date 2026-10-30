# 题目：259. 较小的三数之和（3Sum Smaller）
# 思路：排序 + 双指针。固定 i，j、k 指向剩余区间两端；和小于 target 时 k-j 个组合都合法，累加后右移 j，否则左移 k。
# 时间复杂度：O(n^2)，每个 i 的双指针只扫一遍；空间复杂度：O(1)，只用常数个变量（不计排序开销）。

class Solution:  # LeetCode 约定的题解类
    def threeSumSmaller(self, nums: List[int], target: int) -> int:  # nums：输入数组；target：目标和
        nums.sort()  # 原地升序排序，双指针法依赖有序性
        ans, n = 0, len(nums)  # ans 统计合法三元组个数，n 是数组长度
        for i in range(n - 2):  # 固定第一个下标 i，保证后面至少还剩两个元素
            j, k = i + 1, n - 1  # 双指针：j 从 i 后一位开始，k 从末尾开始
            while j < k:  # 两指针未相遇时继续
                x = nums[i] + nums[j] + nums[k]  # 当前三数之和
                if x < target:  # 和偏小：固定 i、j 时 k 取 (j+1..k) 中任一位置都合法
                    ans += k - j  # 一次累加 k-j 个合法组合
                    j += 1  # 左指针右移，让和变大
                else:  # 和已不小于 target，需要变小
                    k -= 1  # 右指针左移
        return ans  # 返回合法三元组数量
