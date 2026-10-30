# 题目：2817. 限制条件下元素之间的最小绝对差（Minimum Absolute Difference Between Elements With Constraint）
# 思路：滑动窗口 + 有序列表。扫到 i 时把 nums[i-x] 加入 SortedList，集合内元素与 i 的下标差都 >= x；用二分找到 nums[i] 的位置，比较右侧元素与左侧前驱，即可得到以 i 为右端点的最优配对。
# 时间复杂度：O(n·log n)，每轮的 add 与 bisect_left 都是 O(log n)；空间复杂度：O(n)，有序列表最多保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def minAbsoluteDifference(self, nums: List[int], x: int) -> int:  # nums：输入数组；x：下标至少相差 x；返回满足约束的最小绝对差
        sl = SortedList()  # 有序列表：自动维护升序，支持二分查找
        ans = inf  # 答案初值取正无穷，后面不断取 min
        for i in range(x, len(nums)):  # i 从 x 开始，保证至少有一个合法的 j = i - x 已经进入窗口
            sl.add(nums[i - x])  # 把下标 i-x 的值加入窗口，窗口内元素与 i 的下标差都 >= x
            j = bisect_left(sl, nums[i])  # 二分找插入位置，即第一个 >= nums[i] 的下标
            if j < len(sl):  # 右侧还有元素，说明存在不小于 nums[i] 的候选
                ans = min(ans, sl[j] - nums[i])  # 用右侧最近元素更新答案
            if j:  # j 不为 0，说明左侧还有更小的候选
                ans = min(ans, nums[i] - sl[j - 1])  # 用左侧前驱 sl[j-1] 更新答案
        return ans  # 返回最小绝对差
