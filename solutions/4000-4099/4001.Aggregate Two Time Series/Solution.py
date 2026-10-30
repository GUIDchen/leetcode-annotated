# 4001. 聚合两个时间序列 / Aggregate Two Time Series（中等）
# 核心思路：两个序列的时间戳都严格递增，用双指针归并；某序列缺失的时间戳要取「下一个更晚时间戳」的值，恰好就是该指针当前指向的值（指针越界后视为 0），所以每个出现过的时刻把两个当前值相加即可。
# 复杂度：时间 O(m + n)，空间 O(m + n) 用于存放结果。
class Solution:  # 题解类
    def aggregateTimeSeries(  # 返回按时间戳严格递增排列的聚合序列（参数分多行书写）
        self, series1: list[list[int]], series2: list[list[int]]  # 两个输入序列，元素均为 [时间戳, 值]
    ) -> list[list[int]]:  # 返回值：聚合后的 [时间戳, 求和值] 列表
        m, n = len(series1), len(series2)  # 两个序列的长度
        i = j = 0  # 双指针分别指向两个序列的当前元素
        ans = []  # 聚合结果
        while i < m and j < n:  # 两个序列都还有元素时归并
            t1, v1 = series1[i]  # 序列 1 当前时刻与值
            t2, v2 = series2[j]  # 序列 2 当前时刻与值
            if t1 == t2:  # 两个序列都有该时刻
                ans.append([t1, v1 + v2])  # 该时刻的值等于两者相加
                i += 1  # 序列 1 指针前进
                j += 1  # 序列 2 指针前进
            elif t1 < t2:  # 序列 1 的时刻更早
                ans.append([t1, v1 + v2])  # 序列 2 在该时刻缺失，取它下一个时间戳的值 v2
                i += 1  # 序列 1 指针前进
            else:  # 序列 2 的时刻更早
                ans.append([t2, v1 + v2])  # 序列 1 在该时刻缺失，取它下一个时间戳的值 v1
                j += 1  # 序列 2 指针前进
        while i < m:  # 序列 2 已耗尽，它在这些时刻的值为 0
            ans.append(series1[i])  # 序列 1 的剩余元素原样加入
            i += 1  # 指针前进
        while j < n:  # 序列 1 已耗尽，它在这些时刻的值为 0
            ans.append(series2[j])  # 序列 2 的剩余元素原样加入
            j += 1  # 指针前进
        return ans  # 返回聚合结果
