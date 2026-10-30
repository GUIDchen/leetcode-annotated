# 3414. 不重叠区间的最大得分 / Maximum Score of Non-overlapping Intervals
# 核心思路：按起点排序后二分求每个区间的后继，再从后往前 DP 选至多 4 个区间，同分时取下标序列字典序最小者。
# 复杂度：时间复杂度 O(n log n + 4n)，空间复杂度 O(4n)。
class Solution:  # 题解类定义
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:  # 选出至多 4 个不重叠区间，使总分最大且下标序列字典序最小
        n = len(intervals)  # 区间数量
        arr = [[e[0], e[1], e[2], i] for i, e in enumerate(intervals)]  # 把区间连同原始下标打包成四元组
        arr.sort()  # 按起点升序排序
        nxt = [0] * n  # nxt[i]：与区间 i 不重叠的下一个区间下标
        for i in range(n):  # 对每个区间二分查找
            l, r = i + 1, n  # 二分区间 [i+1, n)
            while l < r:  # 二分循环
                mid = (l + r) >> 1  # 取中点
                if arr[mid][0] > arr[i][1]:  # 中点起点严格大于区间 i 的终点
                    r = mid  # 答案落在左半部分
                else:  # 否则
                    l = mid + 1  # 答案落在右半部分
            nxt[i] = l  # 记录后继下标
        f = [[0] * 5 for _ in range(n + 1)]  # f[i][k]：从区间 i 起选 k 个区间的最大得分
        g = [[[] for _ in range(5)] for _ in range(n + 1)]  # g[i][k]：对应得分下字典序最小的下标序列
        for i in range(n - 1, -1, -1):  # 从后向前递推
            for k in range(1, 5):  # 枚举选取个数 1..4
                s1, a1 = f[i + 1][k], g[i + 1][k]  # 不选区间 i 的得分与序列
                a2 = g[nxt[i]][k - 1][:]  # 选区间 i 时对应下标序列的副本
                x = arr[i][3]  # 当前区间的原始下标
                j = 0  # 寻找插入位置
                while j < len(a2) and a2[j] < x:  # 跳过小于当前下标的元素
                    j += 1  # 位置后移
                a2.insert(j, x)  # 把下标插入有序序列
                s2 = f[nxt[i]][k - 1] + arr[i][2]  # 选区间 i 的得分（接上 nxt[i] 处选 k-1 个）
                if s2 > s1 or (s2 == s1 and a2 < a1):  # 得分更大或得分相同但序列字典序更小
                    f[i][k] = s2  # 采用选择区间 i 的方案得分
                    g[i][k] = a2  # 采用选择区间 i 的方案序列
                else:  # 否则
                    f[i][k] = s1  # 采用不选区间 i 的方案得分
                    g[i][k] = a1  # 采用不选区间 i 的方案序列
        return g[0][4]  # 答案为从头选 4 个区间的下标序列
