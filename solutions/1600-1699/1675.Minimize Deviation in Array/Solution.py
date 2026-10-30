# 题目：1675. 数组的最小偏移量（Minimize Deviation in Array）
# 思路：奇数先乘 2 变成偶数，之后不断把最大值除以 2；Python 用最小堆存负数来模拟大根堆。
# 时间复杂度：O(n log n · log V)，每个数最多被除 log V 次 2；空间复杂度：O(n)，堆中保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def minimumDeviation(self, nums: List[int]) -> int:  # nums：输入数组，元素可以乘 2，偶数还可以除 2
        h = []  # 用列表当堆，存放元素的相反数，从而用最小堆模拟大根堆
        mi = inf  # 记录当前最小值，初值取正无穷
        for v in nums:  # 逐个处理每个元素
            if v & 1:  # 奇数只能乘 2，先统一成偶数
                v <<= 1  # 左移一位等价于乘 2，此后只能往小变
            h.append(-v)  # 存相反数，堆顶（最小值）对应原数组的最大值
            mi = min(mi, v)  # 同步维护最小值
        heapify(h)  # 把列表整理成堆结构
        ans = -h[0] - mi  # 初始偏移量 = 最大值 - 最小值（h[0] 是最大值的相反数）
        while h[0] % 2 == 0:  # 只要当前最大值是偶数，就还能把它缩小
            x = heappop(h) // 2  # 弹出最大值并除以 2（heappop 返回的是相反数，整除 2 后仍是相反数）
            heappush(h, x)  # 把缩小后的值放回堆中
            mi = min(mi, -x)  # 缩小后可能产生新的最小值，注意要取相反数还原
            ans = min(ans, -h[0] - mi)  # 用新的极差更新答案
        return ans  # 返回记录到的最小偏移量
