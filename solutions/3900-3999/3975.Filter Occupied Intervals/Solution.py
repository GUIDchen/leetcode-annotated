# 3975. Filter Occupied Intervals | 筛选忙碌区间（中等）
# 核心思路：先按左端点排序，顺序扫描合并“相隔不超过 1”的区间得到合并后的忙碌区间；再逐个判断它与空闲区间 [freeStart, freeEnd] 的关系，完全不相交就整段保留，相交则只保留左右两侧露出来的部分。
# 复杂度：时间 O(n log n)，瓶颈在排序，合并与切割各是 O(n)；空间 O(n)，存放合并后的忙碌区间与答案。
class Solution:  # 定义题解类
    def filterOccupiedIntervals(  # 返回扣掉空闲区间后剩余的忙碌区间
        self, occupiedIntervals: List[List[int]], freeStart: int, freeEnd: int  # 参数：忙碌区间列表与空闲区间的左右端点
    ) -> List[List[int]]:  # 返回值为二维列表，即剩余忙碌区间
        occupiedIntervals.sort(key=lambda x: x[0])  # 只按左端点升序排序，便于顺序合并
        busy = [occupiedIntervals[0]]  # 合并后的忙碌区间集合，先用第一个区间初始化
        for interval in occupiedIntervals[1:]:  # 从第二个区间开始顺序扫描
            if busy[-1][1] + 1 < interval[0]:  # 与上一个合并区间之间存在真正的空隙（差超过 1）
                busy.append(interval)  # 当前区间作为一个新的忙碌区间
            else:  # 重叠或首尾相邻（busy[-1][1] + 1 == interval[0] 也算连成一片）
                busy[-1][1] = max(busy[-1][1], interval[1])  # 只把右端点扩展到两者的最大值
        ans = []  # 存放最终答案
        for interval in busy:  # 逐个处理合并后的忙碌区间
            if interval[1] < freeStart or freeEnd < interval[0]:  # 与空闲区间完全没有交集
                ans.append(interval)  # 整段保留
            else:  # 与空闲区间有交集，需要把空闲那段挖掉
                if interval[0] < freeStart:  # 左侧还有露出尾部的一部分
                    ans.append([interval[0], freeStart - 1])  # 保留从原左端点起到 freeStart - 1
                if interval[1] > freeEnd:  # 右侧还有露出头部的一部分
                    ans.append([freeEnd + 1, interval[1]])  # 保留从 freeEnd + 1 起到原右端点
        return ans  # 返回剔除空闲区间后的忙碌区间
