# 题目：697. 数组的度（Degree of an Array）
# 思路：用 Counter 求数组的度，同时记录每个元素首次与末次出现的下标；在达到度的元素里取「末次减首次加一」最小的那段长度。
# 时间复杂度：O(n)，统计与两次遍历都是线性的；空间复杂度：O(n)，计数表与两张下标表各存 O(n) 个条目。
class Solution:  # LeetCode 约定的题解类
    def findShortestSubArray(self, nums: List[int]) -> int:  # nums 是输入数组，返回与整体度相同的最短连续子数组长度
        cnt = Counter(nums)  # 统计每个元素的出现次数
        degree = cnt.most_common()[0][1]  # most_common 按次数降序排列，取第一个的计数即为数组的度
        left, right = {}, {}  # left 记首次出现下标，right 记末次出现下标
        for i, v in enumerate(nums):  # 从左到右扫一遍数组，同时拿到下标 i 和值 v
            if v not in left:  # 判断是不是第一次遇到这个值
                left[v] = i  # 只在首次出现时记录左端点
            right[v] = i  # 每次遇到都刷新右端点，循环结束后即最后一次的位置
        ans = inf  # 用一个正无穷大的数初始化最短长度
        for v in nums:  # 再扫一遍数组，挑出达到度的元素
            if cnt[v] == degree:  # 只考虑出现次数等于数组度的值
                t = right[v] - left[v] + 1  # 把该值全部出现位置包住所需的区间长度
                if ans > t:  # 若这个区间更短
                    ans = t  # 更新最短长度
        return ans  # 返回满足条件的最短子数组长度
