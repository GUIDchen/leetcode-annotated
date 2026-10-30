# 题目：3066. 超过阈值的最少操作数 II（Minimum Operations to Exceed Threshold Value II）
# 思路：贪心 + 最小堆；每次弹出最小的两个数 x<=y 合并成 x*2+y 放回堆，直到堆顶不小于 k。
# 时间复杂度：O(n log n)，每次操作两次 heappop 一次 heappush；空间复杂度：O(n)，堆存全部元素。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是阈值，返回最少操作次数
        heapify(nums)  # 原地把 nums 整理成最小堆，堆顶 nums[0] 即当前最小值
        ans = 0  # ans 记录已经执行的操作次数
        while len(nums) > 1 and nums[0] < k:  # 堆顶仍小于 k 且至少有两个元素时继续合并
            x, y = heappop(nums), heappop(nums)  # 依次弹出最小的两个数：先弹 x 再弹 y，保证 x <= y
            heappush(nums, x * 2 + y)  # 按规则合并 x、y 得到新值并压回堆
            ans += 1  # 操作次数加一
        return ans  # 返回总操作次数；堆不足两个元素时循环自然结束
