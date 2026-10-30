# 题目：3264. K 次乘运算后的最终数组 I（Final Array State After K Multiplication Operations I）
# 思路：用小根堆维护「(数值, 下标)」对，数值相同时下标小者优先；每次弹出堆顶（当前最小值）乘以 multiplier 后重新入堆，重复 k 次即得最终数组。
# 时间复杂度：O(n + k log n)，建堆 O(n)、每次操作 O(log n)；空间复杂度：O(n)，堆中始终保存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def getFinalState(self, nums: List[int], k: int, multiplier: int) -> List[int]:  # nums 为初始数组，k 为操作次数，multiplier 为每次所乘的数；返回操作后的数组
        pq = [(x, i) for i, x in enumerate(nums)]  # 把每个元素与它的下标打包成 (值, 下标)，使并列时按下标比较
        heapify(pq)  # 调整成小根堆，堆顶始终是当前最小元素
        for _ in range(k):  # 重复 k 次乘法操作
            _, i = heappop(pq)  # 弹出堆顶，丢掉数值只留下标 i（最小元素所在位置）
            nums[i] *= multiplier  # 把该位置上的元素乘以 multiplier
            heappush(pq, (nums[i], i))  # 修改后的 (新值, 下标) 重新入堆，供下一轮使用
        return nums  # 返回 k 次操作后的最终数组
