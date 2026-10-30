# 题目：436. 寻找右区间（Find Right Interval）
# 思路：把（左端点, 原下标）排序后用 bisect_left 二分，为每个区间的右端点找到第一个左端点 ≥ 它的区间，其原下标就是答案。
# 时间复杂度：O(n log n)，一次排序加 n 次二分；空间复杂度：O(n)，辅助数组 arr 与答案数组。
class Solution:  # LeetCode 约定的题解类
    def findRightInterval(self, intervals: List[List[int]]) -> List[int]:  # 为每个区间找出右区间的下标；不存在右区间时该位置填 -1
        n = len(intervals)  # 区间总数
        ans = [-1] * n  # 答案数组，先全部初始化为 -1（表示找不到右区间）
        arr = sorted((st, i) for i, (st, _) in enumerate(intervals))  # 生成 (左端点, 原下标) 并按左端点升序排序，供二分使用
        for i, (_, ed) in enumerate(intervals):  # 按原始顺序遍历，用下划线忽略用不到的左端点
            j = bisect_left(arr, (ed, -inf))  # 二分找第一个左端点 ≥ ed 的位置；第二元取 -inf 保证落在相同左端点的最前面
            if j < n:  # j 没有越界，说明存在合法的右区间
                ans[i] = arr[j][1]  # 把该区间的原始下标写回答案
        return ans  # 返回与输入一一对应的答案数组
