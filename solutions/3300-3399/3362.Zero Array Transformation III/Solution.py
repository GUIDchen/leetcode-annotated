# 题目：3362. 零数组变换 III（Zero Array Transformation III）
# 思路：区间按左端点排序后从左到右扫描，用小根堆（存右端点相反数）维护可用区间；当前位置减量不足时贪心选右端点最远的区间，扫描结束后堆中剩余区间数即可删除的最大个数。
# 时间复杂度：O((n+m) log m)；空间复杂度：O(n+m)，差分数组与堆。
class Solution:  # LeetCode 约定的题解类
    def maxRemoval(self, nums: List[int], queries: List[List[int]]) -> int:  # nums：目标数组；queries：可选的区间操作
        queries.sort()  # 按左端点排序，便于扫描时依次入堆
        pq = []  # 小根堆（存右端点的相反数），堆顶即覆盖最远的右端点
        d = [0] * (len(nums) + 1)  # 差分数组，记录已选区间造成的减量变化
        s = j = 0  # s：当前位置累计减量；j：下一个待入堆区间的下标
        for i, x in enumerate(nums):  # 从左到右处理每个位置
            s += d[i]  # 差分前缀还原出当前位置的减量
            while j < len(queries) and queries[j][0] <= i:  # 左端点不大于 i 的区间都可以覆盖位置 i，全部入堆
                heappush(pq, -queries[j][1])  # 存相反数，用小根堆模拟大根堆
                j += 1  # 区间指针后移
            while s < x and pq and -pq[0] >= i:  # 减量不足且堆顶区间仍覆盖当前位置时，贪心再用一个区间
                s += 1  # 当前位置减量加一
                d[-heappop(pq) + 1] -= 1  # 弹出最远右端点，并在其下一位做差分收口
            if s < x:  # 仍然减不够，说明无解
                return -1  # 返回 -1
        return len(pq)  # 剩下没用的区间都可以删掉，返回其个数
