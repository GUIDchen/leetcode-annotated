# 题目：801. 使序列递增的最小交换次数（Minimum Swaps To Make Sequences Increasing）
# 思路：动态规划，a 记录「本位不交换」的最少次数，b 记录「本位交换」的最少次数，根据相邻两列是否已严格递增分情况转移。
# 时间复杂度：O(n)，只遍历一遍数组；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minSwap(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个等长数组；返回最少交换次数
        a, b = 0, 1  # a：第 0 位不交换的次数；b：第 0 位交换的次数（代价 1）
        for i in range(1, len(nums1)):  # 从左到右逐位推进
            x, y = a, b  # 暂存上一列的状态，避免被本列的更新覆盖
            if nums1[i - 1] >= nums1[i] or nums2[i - 1] >= nums2[i]:  # 不交换时相邻两列已不递增，只能靠交换
                a, b = y, x + 1  # 当前不换 ⇐ 上一列换；当前换 ⇐ 上一列不换再换一次
            else:  # 不交换本身合法，还需要考虑第二种选择
                b = y + 1  # 当前换：在上一列已换的基础上再换一次
                if nums1[i - 1] < nums2[i] and nums2[i - 1] < nums1[i]:  # 交叉比较也成立，两种选择可以互换
                    a, b = min(a, y), min(b, x + 1)  # 分别取两种来源中的较小值
        return min(a, b)  # 最后一位换或不交换，取更优的那个
