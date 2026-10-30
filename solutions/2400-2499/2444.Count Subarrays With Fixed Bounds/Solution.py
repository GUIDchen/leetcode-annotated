# 题目：2444. 统计定界子数组的数目（Count Subarrays With Fixed Bounds）
# 思路：遍历右端点 i，维护 minK、maxK 最近出现的位置与越界元素最近的位置，累加合法左端点的个数。
# 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只存三个下标和一个累加器。
class Solution:  # LeetCode 约定的题解类
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:  # nums 是输入数组，minK/maxK 是子数组必须取到的最小值/最大值
        j1 = j2 = k = -1  # j1：minK 最近出现的下标；j2：maxK 最近出现的下标；k：越界元素最近出现的下标（-1 表示还没出现）
        ans = 0  # 累计合法子数组的个数
        for i, v in enumerate(nums):  # 同时取得右端点下标 i 与元素值 v
            if v < minK or v > maxK:  # 元素越界，任何包含它的子数组都不合法
                k = i  # 更新「墙」的位置，之后的左端点必须更靠右
            if v == minK:  # 遇到最小值
                j1 = i  # 刷新 minK 的位置
            if v == maxK:  # 遇到最大值
                j2 = i  # 刷新 maxK 的位置
            ans += max(0, min(j1, j2) - k)  # 左端点可取 (k, min(j1, j2)] 内共 min(j1, j2)-k 个位置，负值用 0 截断
        return ans  # 返回所有合法子数组的个数
