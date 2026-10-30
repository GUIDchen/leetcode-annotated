# 题目：774. 最小化去加油站的最大距离（Minimize Max Distance to Gas Station）
# 核心思路：二分答案 x（允许的最大间距）；判定时每个相邻区间需要新增 int(间距/x) 个加油站，总数不超过 k 则 x 可行。
# 时间复杂度 O(n·log(1e8/1e-6))，每次判定 O(n)；空间复杂度 O(1)（只用到常数个变量）。
class Solution:  # LeetCode 约定的题解类
    def minmaxGasDist(self, stations: List[int], k: int) -> float:  # stations：已排序坐标；k：还能新建的加油站个数；返回最小化的最大间距
        def check(x):  # 判定函数：把最大间距压到不超过 x 是否只需不超过 k 个新站
            return sum(int((b - a) / x) for a, b in pairwise(stations)) <= k  # pairwise 给出相邻两点，int(间距/x) 为向下取整，sum 汇总所需新站数

        left, right = 0, 1e8  # 二分区间：答案一定在 0 到 1e8 之间
        while right - left > 1e-6:  # 浮点二分：区间宽度缩小到 1e-6 以内即收敛
            mid = (left + right) / 2  # 取区间中点作为候选答案
            if check(mid):  # mid 可行，说明答案可以更小
                right = mid  # 收缩右边界
            else:  # mid 不可行
                left = mid  # 抬高左边界，间距必须更大
        return left  # left 停在可行解一侧，即最小化的最大间距
