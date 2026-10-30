# 3763. 带阈值约束的最大总和 / Maximum Total Sum with Threshold Constraints
# 核心思路：按下标对应的 threshold 升序排序，用有序列表维护“已解锁”的分数，每一步取出其中的最大值累加。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # 定义解法类
    def maxSum(self, nums: List[int], threshold: List[int]) -> int:  # 求最大总和：nums 为可获得的分数，threshold 为元素最早可用的步数
        n = len(nums)  # 元素个数
        idx = sorted(range(n), key=lambda i: threshold[i])  # 按各下标对应的 threshold 升序排序下标
        sl = SortedList()  # 有序列表，保存当前可选的分数
        step = 1  # 从第 1 步开始推进
        ans = i = 0  # ans 为总和，i 为下一个待解锁元素的指针
        while True:  # 逐步推进，直到没有元素可用
            while i < n and threshold[idx[i]] <= step:  # 把 threshold 已到达当前步数的元素全部解锁
                sl.add(nums[idx[i]])  # 把该元素的分数加入有序列表
                i += 1  # 指针后移
            if not sl:  # 有序列表为空则无法继续
                break  # 提前结束循环
            ans += sl.pop()  # 取出并累加当前最大分数
            step += 1  # 步数加一
        return ans  # 返回最大总和
