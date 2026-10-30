# 题目：632. 最小区间（Smallest Range Covering Elements from K Lists）
# 思路：把 k 个列表展平成 (值, 列表下标) 后排序，用滑动窗口维护「窗口内覆盖了哪些列表」；覆盖满 k 个列表时收缩左端点并更新最优区间。
# 时间复杂度：O(N log N)，N 为元素总数；空间复杂度：O(N)，展平数组与计数表。
class Solution:  # LeetCode 约定的题解类
    def smallestRange(self, nums: List[List[int]]) -> List[int]:  # nums 是 k 个升序列表，返回覆盖每个列表至少一个数的最小区间
        t = [(x, i) for i, v in enumerate(nums) for x in v]  # 双重推导式展平成 (值, 列表下标)，i 是列表下标，x 是元素值
        t.sort()  # 按值升序排序（值相同再按列表下标），使窗口最值具有单调性
        cnt = Counter()  # 窗口内各列表的元素计数，Counter 由判题环境提供
        ans = [-inf, inf]  # 答案初值取正负无穷，保证第一次命中一定被更新（inf 由判题环境提供）
        j = 0  # 滑动窗口左端点
        for i, (b, v) in enumerate(t):  # i 是右端点下标，b 是窗口最大值，v 是它所属列表
            cnt[v] += 1  # 把右端点元素计入所属列表的计数
            while len(cnt) == len(nums):  # 窗口覆盖了全部列表，可以尝试收缩左端点
                a = t[j][0]  # a 是当前窗口的最小值
                x = b - a - (ans[1] - ans[0])  # x 是与当前最优区间的长度差：小于 0 更短，等于 0 等长
                if x < 0 or (x == 0 and a < ans[0]):  # 更短，或等长但起点更小时才更新
                    ans = [a, b]  # 更新答案为 [a, b]
                w = t[j][1]  # w 是左端点元素所属的列表下标
                cnt[w] -= 1  # 左端点元素移出窗口
                if cnt[w] == 0:  # 该列表在窗口内已无元素
                    cnt.pop(w)  # 删除该列表的计数，使 len(cnt) 变小以跳出 while
                j += 1  # 左端点右移一格
        return ans  # 返回覆盖全部列表的最小区间
