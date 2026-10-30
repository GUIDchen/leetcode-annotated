# 题目：220. 存在重复元素 III（Contains Duplicate III）
# 核心思路：用有序集合维护长度为 indexDiff+1 的滑动窗口，每次二分查找不小于 v-valueDiff 的最小值，再检查是否不超过 v+valueDiff。
# 时间复杂度：O(n log n)，每个元素一次二分查找与一次增删；空间复杂度：O(k)，窗口内最多 indexDiff+1 个元素。
class Solution:  # LeetCode 约定的题解类
    def containsNearbyAlmostDuplicate(  # 判断是否存在下标差 <= indexDiff 且值差 <= valueDiff 的一对元素
        self, nums: List[int], indexDiff: int, valueDiff: int  # 方法签名换行：self、数组、下标差上限、值差上限
    ) -> bool:  # 返回布尔结果
        s = SortedSet()  # 有序集合 SortedSet（sortedcontainers 提供），维护窗口内最近若干个元素的值
        for i, v in enumerate(nums):  # 同时取得下标 i 与元素值 v，右端点从左往右滑动
            j = s.bisect_left(v - valueDiff)  # 二分找第一个 >= v-valueDiff 的位置，它是最接近的下界候选
            if j < len(s) and s[j] <= v + valueDiff:  # 若该元素同时 <= v+valueDiff，则窗口内存在值差满足要求的元素
                return True  # 找到满足条件的元素对
            s.add(v)  # 把当前值加入窗口
            if i >= indexDiff:  # 窗口只保留最近 indexDiff 个元素
                s.remove(nums[i - indexDiff])  # 移除已经超出下标差限制的左端旧值
        return False  # 没有找到满足条件的元素对
