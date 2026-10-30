# 3488. 距离最小相等元素查询 / Closest Equal Element Queries
# 核心思路：把数组首尾相接复制成两倍长度，分别从左、从右扫描求出每个位置到最近相等元素的距离，再合并后半段结果，查询时距离达到 n 即表示不存在其它相等元素。
# 复杂度：时间 O(n + q)，空间 O(n)。
class Solution:  # 定义题解类
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:  # 主函数：对每个查询返回该位置到最近相等元素的距离
        n = len(nums)  # 原数组长度
        m = n << 1  # 数组复制一遍，长度变为两倍以处理环形
        d = [m] * m  # d[i] 记录到最近相等元素的距离，先设为 m（表示无穷大）
        left = {}  # 记录每个值上一次（左侧最近）出现的下标
        for i in range(m):  # 从左往右扫描两倍数组
            x = nums[i % n]  # 取环形意义下的元素
            if x in left:  # 左侧出现过相同元素
                d[i] = min(d[i], i - left[x])  # 用左侧最近距离更新
            left[x] = i  # 更新该值最近出现的下标
        right = {}  # 记录每个值下一次（右侧最近）出现的下标
        for i in range(m - 1, -1, -1):  # 从右往左扫描两倍数组
            x = nums[i % n]  # 取环形意义下的元素
            if x in right:  # 右侧出现过相同元素
                d[i] = min(d[i], right[x] - i)  # 用右侧最近距离更新
            right[x] = i  # 更新该值最近出现的下标
        for i in range(n):  # 把后半段的答案合并回前半段
            d[i] = min(d[i], d[i + n])  # 跨越首尾边界的距离也可能更小
        return [-1 if d[i] >= n else d[i] for i in queries]  # 距离达到 n 说明没有其它相等元素，返回 -1
