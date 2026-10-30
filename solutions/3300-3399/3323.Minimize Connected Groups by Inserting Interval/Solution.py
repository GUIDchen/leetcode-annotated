# 题目：3323. 通过插入区间最小化连通组（Minimize Connected Groups by Inserting Interval）
# 思路：先排序并合并所有重叠区间；再枚举每个合并组 i，用 bisect_left 找到插入长度 k 的区间后仍够不到的第一个组 j，
# 用 总组数 - 被吞并的中间组数 更新答案。时间复杂度：O(n log n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def minConnectedGroups(self, intervals: List[List[int]], k: int) -> int:  # intervals：原始区间集合；k：可以额外插入的区间长度
        intervals.sort()  # 按左端点升序排序（Python 列表比较即字典序）
        merged = [intervals[0]]  # 把第一个区间直接作为第一个合并组，省去空列表判断
        for s, e in intervals[1:]:  # 从第二个区间开始顺序扫描
            if merged[-1][1] < s:  # 与上一个合并组的右端点不相交
                merged.append([s, e])  # 开启一个新的连通组
            else:  # 有重叠，延长右端点
                merged[-1][1] = max(merged[-1][1], e)  # 有重叠就延长右端点，取两者较大值
        ans = len(merged)  # 不插入任何区间时的组数，作为答案初值
        for i, (_, e) in enumerate(merged):  # 枚举每个合并组，只关心它的右端点 e
            j = bisect_left(merged, [e + k + 1, 0])  # 二分找到第一个左端点 >= e + k + 1 的组下标，即插入后仍然够不到的分界
            ans = min(ans, len(merged) - (j - i - 1))  # 插入后吞并了 j-i-1 个中间组：组数 = 总组数 - 吞并数
        return ans  # 返回最小的连通组数
