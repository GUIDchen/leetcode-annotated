# 题目：3572. 选择不同 X 值三元组使 Y 值之和最大（Maximize Y‑Sum by Picking a Triplet of Distinct X‑Values）
# 思路：把 (x, y) 打包成元组并按 y 降序排序，从头贪心扫描：同一个 x 只取 y 最大的那一次，累计到 3 个不同的 x 就立刻返回当前和；不同 x 不足 3 个则返回 -1。
# 时间复杂度：O(n log n)，排序为主，扫描 O(n)；空间复杂度：O(n)，存放元组列表与去重集合。
class Solution:  # LeetCode 约定的题解类
    def maxSumDistinctTriplet(self, x: List[int], y: List[int]) -> int:  # x：每个元素的 X 值；y：每个元素的 Y 值；返回 3 个 X 互不相同时的最大 Y 之和，凑不齐则返回 -1
        arr = [(a, b) for a, b in zip(x, y)]  # 把 X、Y 逐项配对成元组列表
        arr.sort(key=lambda x: -x[1])  # 按 Y 降序排序（对 Y 取负即可让大的排在前面）
        vis = set()  # 记录已经用过的 X 值
        ans = 0  # 记录选中的 Y 之和
        for a, b in arr:  # 从 Y 最大的元素开始贪心扫描
            if a in vis:  # 这个 X 之前已经选过
                continue  # 跳过，同一个 X 只保留 Y 最大的那一次
            vis.add(a)  # 把该 X 标记为已使用
            ans += b  # 累加它的 Y
            if len(vis) == 3:  # 已经凑齐 3 个互不相同的 X
                return ans  # 当前和就是最大和，立即返回
        return -1  # 不同的 X 不足 3 个，无解
