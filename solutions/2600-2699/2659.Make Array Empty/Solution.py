# 题目：2659. 将数组清空（Make Array Empty）
# 核心思路：按值从小到大的顺序删除元素，用有序容器（SortedList）维护已删除的下标，逐段累加「沿环前进」的真实步数，绕回开头时多走一整圈。
# 时间复杂度：O(n log n)，排序加有序容器插入/二分；空间复杂度：O(n)，pos 字典与有序容器。
class Solution:  # 题解类
    def countOperationsToEmptyArray(self, nums: List[int]) -> int:  # 返回把数组清空所需的最少操作次数
        pos = {x: i for i, x in enumerate(nums)}  # 记录「值 → 原始下标」，题目保证元素互不相同
        nums.sort()  # 排序后按「被删除的先后顺序」遍历
        sl = SortedList()  # 有序容器，保存已被删除元素的下标，便于二分统计区间内的删除个数
        ans = pos[nums[0]] + 1  # 先转圈走到最小值处并删除它：pos+1 次操作
        n = len(nums)  # 数组长度
        for k, (a, b) in enumerate(pairwise(nums)):  # 依次处理排序后相邻的两个值
            i, j = pos[a], pos[b]  # 两者在原始数组中的下标
            d = j - i - sl.bisect(j) + sl.bisect(i)  # 减去中间已删除的元素个数，得到实际需要前进的步数
            ans += d + (n - k) * int(i > j)  # 若 i > j 说明要绕回开头，多走一整圈（此时还剩 n-k 个元素）
            sl.add(i)  # 把 i 记为已删除
        return ans  # 返回总操作次数
