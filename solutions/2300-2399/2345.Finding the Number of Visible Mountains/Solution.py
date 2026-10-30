# 题目：2345. 寻找可见山的数量（Finding the Number of Visible Mountains）
# 思路：山底覆盖区间 [x-y, x+y]，按 (左端点升序, 右端点降序) 排序后扫描，右端点严格变大的山才可能可见，且顶点唯一时才会计数。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，区间列表与计数哈希表。
class Solution:  # LeetCode 约定的题解类
    def visibleMountains(self, peaks: List[List[int]]) -> int:  # peaks 中每组是山峰顶点 [x, y]
        arr = [(x - y, x + y) for x, y in peaks]  # 把每座山转换成山底区间 (左端点, 右端点)
        cnt = Counter(arr)  # 统计每个区间出现的次数，用来识别同顶点的重复山
        arr.sort(key=lambda x: (x[0], -x[1]))  # 左端点升序、右端点降序，保证区间不会互相吞噬
        ans, cur = 0, -inf  # ans 统计可见山数，cur 记录已经能看到的最远右端点
        for l, r in arr:  # 按排好的顺序扫描区间
            if r <= cur:  # 右端点不超出 cur，整座山被前面更高的山遮住
                continue  # 跳过，且不更新 cur
            cur = r  # 这山的右边界成为新的最远可见右端点
            if cnt[(l, r)] == 1:  # 只有顶点唯一的山才算可见，重复的山彼此遮挡都不计入
                ans += 1  # 可见山数量加一
        return ans  # 返回可见山的数量
