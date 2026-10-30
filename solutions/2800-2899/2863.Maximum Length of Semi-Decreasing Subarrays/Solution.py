# 题目：2863. 最长半递减子数组的长度（Maximum Length of Semi-Decreasing Subarrays）
# 思路：先用字典把每种值的下标收集起来，再按值从大到小扫描；k 记录更大值里的最小下标，用当前值的最大下标与 k 配对求长度。
# 时间复杂度：O(n log n)，对不同的值排序；空间复杂度：O(n)，保存每个元素的下标。
class Solution:  # LeetCode 约定的题解类
    def maxSubarrayLength(self, nums: List[int]) -> int:  # nums 是输入数组，返回最长半递减子数组的长度
        d = defaultdict(list)  # 值 → 该值出现的下标列表，缺键时自动创建空列表
        for i, x in enumerate(nums):  # 从左到右扫描，同时拿到下标 i 和元素值 x
            d[x].append(i)  # 把下标追加到该值的列表末尾，列表因此保持升序
        ans, k = 0, inf  # ans 记录答案；k 是「更大值中出现过的最小下标」，先设为正无穷
        for x in sorted(d, reverse=True):  # 按键从大到小处理每一个不同的值
            ans = max(ans, d[x][-1] - k + 1)  # 用 k 处的大值做左端、本组最大下标做右端，更新长度
            k = min(k, d[x][0])  # 本组的值之后要当作「更大的值」，用它的最小下标收紧 k
        return ans  # 返回遍历过程中得到的最大长度
