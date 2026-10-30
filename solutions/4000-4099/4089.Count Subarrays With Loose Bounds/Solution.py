# 题目：4089. 统计宽界子数组的数目（Count Subarrays With Loose Bounds）
# 思路：右端点 r 从 0 扫描到 n-1，l 记录「最近一个越界元素的下一个位置」；nums[r] 落在 [minK, maxK] 内时，以 r 结尾的合法子数组恰好有 r - l + 1 个，直接累加；一旦越界就把 l 跳到 r + 1。
# 时间复杂度：O(n)，每个元素最多被右移一次；空间复杂度：O(1)，只用了 ans、l、r 几个整数变量。
class Solution:  # LeetCode 约定的题解类
    def countSubarrays(self, nums: list[int], minK: int, maxK: int) -> int:  # nums：输入数组；minK / maxK：子数组元素允许的取值下界与上界；返回合法子数组个数
        ans = l = 0  # ans 累计答案；l 是当前合法段的左边界，即最近一个越界元素的下一个位置
        for r, x in enumerate(nums):  # 同时取得右端点下标 r 与元素值 x
            if x < minK or x > maxK:  # 该元素越界，任何包含它的子数组都不可能合法
                l = r + 1  # 合法段被迫从 r 的下一位重新开始
            else:  # 该元素落在区间内，可以继续扩展合法子数组
                ans += r - l + 1  # 以 r 结尾的合法子数组共有 r-l+1 个（左端点在 [l, r] 中任取）
        return ans  # 返回所有元素都落在 [minK, maxK] 内的子数组数目
