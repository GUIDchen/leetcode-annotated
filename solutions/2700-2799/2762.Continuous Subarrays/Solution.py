# 题目：2762. 不间断子数组（Continuous Subarrays）
# 思路：滑动窗口配合有序容器 SortedList，窗口内最大值与最小值之差不超过 2 才合法；右移右端点后从左边不断吐出元素，再用窗口长度累加以当前元素结尾的合法子数组个数。
# 时间复杂度：O(n log n)，每个元素进出 SortedList 各一次；空间复杂度：O(n)，SortedList 最多保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def continuousSubarrays(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有最大值与最小值之差不超过 2 的连续子数组个数
        ans = i = 0  # i 是滑动窗口左边界，ans 累加答案（一行同时给两个变量赋初值）
        sl = SortedList()  # SortedList 是有序容器，能在 O(log n) 内取最小/最大值并删除元素
        for x in nums:  # 逐个把元素加入窗口右端
            sl.add(x)  # 新元素入窗
            while sl[-1] - sl[0] > 2:  # sl[-1] 是窗口最大值，sl[0] 是最小值，极差超过 2 说明窗口不合法
                sl.remove(nums[i])  # 从窗口左侧吐出一个元素（nums[i] 一定还在窗口里）
                i += 1  # 左边界右移一位
            ans += len(sl)  # 以当前元素结尾的合法子数组个数就是窗口长度，累加进答案
        return ans  # 返回不间断子数组的总个数
