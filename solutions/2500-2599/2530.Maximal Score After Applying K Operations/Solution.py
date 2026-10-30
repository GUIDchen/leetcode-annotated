# 题目：2530. 执行 K 次操作后的最大分数（Maximal Score After Applying K Operations）
# 核心思路：贪心 + 小根堆存相反数模拟大根堆，每轮弹出最大值累加，再把 ceil(v/3) 压回堆中，重复 k 轮。
# 时间复杂度：O(n + k log n)，建堆 O(n)、每轮两次堆操作 O(log n)；空间复杂度：O(n)，堆中保存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def maxKelements(self, nums: List[int], k: int) -> int:  # nums 为初始数组，k 为操作次数，返回累计得到的最大分数
        h = [-v for v in nums]  # Python 只有小根堆，存相反数即可让堆顶对应原来的最大值
        heapify(h)  # 原地把列表调整为堆结构，时间复杂度 O(n)
        ans = 0  # 累计得分，Python 整数不会溢出所以无需额外处理
        for _ in range(k):  # 一共执行 k 次操作
            v = -heappop(h)  # 弹出堆顶并取回原来的值，它就是当前最大值
            ans += v  # 把最大值累加进得分
            heappush(h, -(ceil(v / 3)))  # 用 v/3 向上取整后的值替换它，仍以相反数入堆
        return ans  # 返回累计的最大分数
