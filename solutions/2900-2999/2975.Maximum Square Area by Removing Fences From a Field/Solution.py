# 题目：2975. 移除栅栏得到的正方形田地的最大面积（Maximum Square Area by Removing Fences From a Field）
# 思路：把边界 1 与 m（n）并入栅栏坐标，用组合枚举两两间距得到横向、纵向候选边长集合，取交集的最大值 d 并返回 d^2 % mod。
# 时间复杂度：O((H+V)log(H+V) + H^2 + V^2)，排序加两两组合；空间复杂度：O(H^2 + V^2)，两个集合。
class Solution:  # LeetCode 约定的题解类
    def maximizeSquareArea(  # 方法签名：m/n 为横向、纵向总长，hFences/vFences 为可移除的栅栏位置
        self, m: int, n: int, hFences: List[int], vFences: List[int]  # 形参跨行书写（保持原格式）
    ) -> int:  # 返回最大面积，无法构成长方形/正方形时返回 -1
        def f(nums: List[int], k: int) -> Set[int]:  # 内部函数：把边界 1 与 k 并入 nums，返回所有两两间距的集合
            nums.extend([1, k])  # extend 一次性追加两个边界值（注意会就地修改传入列表）
            nums.sort()  # 排序后组合出来的 (a, b) 必然满足 a < b，差值恒为正
            return {b - a for a, b in combinations(nums, 2)}  # combinations 枚举所有栅栏对，b - a 即可能的边长

        mod = 10**9 + 7  # 取模常数
        hs = f(hFences, m)  # 横向候选边长集合
        vs = f(vFences, n)  # 纵向候选边长集合
        ans = max(hs & vs, default=0)  # 交集即横纵都能取到的边长；default=0 处理交集为空的情况
        return ans**2 % mod if ans else -1  # 有公共边长则返回面积 d*d 取模，否则返回 -1
