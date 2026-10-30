# 题目：1383. 最大的团队表现值（Maximum Performance of a Team）
# 思路：按效率降序枚举效率下限，用小根堆保留速度最大的至多 k 人，速度之和乘当前效率即为候选表现值。
# 时间复杂度：O(n log n)，排序加堆操作；空间复杂度：O(n)，存放排序结果与堆。
class Solution:  # LeetCode 约定的题解类
    def maxPerformance(  # 返回团队表现值的最大值（对 1e9+7 取模）
        self, n: int, speed: List[int], efficiency: List[int], k: int  # self：实例；n：人数；speed/efficiency：速度与效率；k：团队人数上限
    ) -> int:  # 返回值为整数
        t = sorted(zip(speed, efficiency), key=lambda x: -x[1])  # 打捆后按效率降序排序
        ans = tot = 0  # ans 记录最优表现值，tot 是当前团队的速度之和
        mod = 10**9 + 7  # 取模常量
        h = []  # 小根堆（Python 的 heapq 就是小根堆）
        for s, e in t:  # 依次把当前工程师的效率当作团队效率下限
            tot += s  # 先把当前工程师的速度计入团队
            ans = max(ans, tot * e)  # 表现值 = 速度和 × 当前效率下限
            heappush(h, s)  # 速度入堆，便于之后淘汰最慢的人
            if len(h) == k:  # 堆已凑满 k 人，再继续加就会超员
                tot -= heappop(h)  # 弹出速度最小者，并把它从速度和中扣除
        return ans % mod  # 取模后返回答案
