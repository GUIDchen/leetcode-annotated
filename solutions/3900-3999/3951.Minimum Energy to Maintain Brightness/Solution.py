# 题目：3951. 维持亮度的最小总能量（Minimum Energy to Maintain Brightness）
# 思路：按左端点排序后合并所有区间，对合并后的每段长度 m，每点需要 ceil(brightness/3) 点能量，累加 (brightness+2)//3*m。
# 复杂度：时间 O(n log n)（排序），空间 O(n)（存合并结果）。
class Solution:  # LeetCode 约定的题解类
    def minEnergy(self, n: int, brightness: int, intervals: list[list[int]]) -> int:  # intervals 是若干区间，brightness 是每个位置要维持的亮度
        intervals.sort()  # 按左端点排序，便于线性合并
        merged = [intervals[0]]  # merged 存放合并后的互不相交区间，先放入第一个区间
        for x in intervals[1:]:  # 从第二个区间开始逐个合并
            if merged[-1][1] < x[0]:  # 最后一个合并区间的右端点与当前区间左端点之间有间隙
                merged.append(x)  # 没有重叠，直接作为新区间加入
            else:  # 否则两者重叠或相邻，合并进最后一个区间
                merged[-1][1] = max(merged[-1][1], x[1])  # 右端点取两者中较大的那个
        ans = 0  # ans 累计总能量
        for start, end in merged:  # 遍历合并后的每个区间
            m = end - start + 1  # m 是区间长度（包含两端）
            ans += (brightness + 2) // 3 * m  # 每个位置需要 ceil(brightness/3) 点能量，乘以整段长度后累加
        return ans  # 返回维持亮度所需的最小总能量
