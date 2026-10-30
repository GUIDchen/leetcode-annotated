# 题目：1851. 包含每个查询的最小区间（Minimum Interval to Include Each Query）
# 思路：区间按左端点、查询按值分别排序后离线扫描；左端点 <= x 的区间按长度入堆，弹出右端点过期的，堆顶即答案。
# 时间复杂度：O((n+m)log n)，排序加每个区间至多进出堆一次；空间复杂度：O(n+m)，堆与排序后的数组。
class Solution:  # LeetCode 约定的题解类
    def minInterval(self, intervals: List[List[int]], queries: List[int]) -> List[int]:  # intervals：闭区间数组；queries：待查询的点
        n, m = len(intervals), len(queries)  # n 是区间个数，m 是查询个数
        intervals.sort()  # 区间按左端点升序，方便随查询值增大依次加入
        queries = sorted((x, i) for i, x in enumerate(queries))  # 把查询和原下标打包后按查询值排序，避免丢失输出顺序
        ans = [-1] * m  # 答案先全部置 -1，表示暂时没有被覆盖
        pq = []  # 小顶堆，元素是（区间长度，右端点）
        i = 0  # 区间数组游标，只会单调前进
        for x, j in queries:  # 按查询值从小到大处理（x 是查询值，j 是原下标）
            while i < n and intervals[i][0] <= x:  # 把所有左端点不超过 x 的区间加入候选
                a, b = intervals[i]  # 取出当前区间的左右端点
                heappush(pq, (b - a + 1, b))  # 入堆：键为长度，附带右端点用来判过期
                i += 1  # 游标后移，避免重复入堆
            while pq and pq[0][1] < x:  # 右端点小于 x 的区间覆盖不到当前查询，弹出
                heappop(pq)  # 丢弃堆顶的过期区间
            if pq:  # 堆非空说明仍有区间覆盖 x
                ans[j] = pq[0][0]  # 堆顶长度就是覆盖 x 的最小区间长度
        return ans  # 按原顺序返回答案
