# 题目：356. 直线镜像（Line Reflection）
# 思路：先求所有点 x 的最小值与最大值，对称轴只能是 x = (min_x + max_x) / 2；再用集合检查每个点的镜像点是否存在。
# 时间复杂度：O(n)，两遍遍历加集合查询；空间复杂度：O(n)，存放去重后的点。
class Solution:  # LeetCode 约定的题解类
    def isReflected(self, points: List[List[int]]) -> bool:  # points 为点集，判断是否存在一条竖直直线使点集关于它镜像对称
        min_x, max_x = inf, -inf  # 用正无穷/负无穷作为 x 最值的初值
        point_set = set()  # 集合既去重又支持平均 O(1) 的成员查询
        for x, y in points:  # 第一遍：求 x 的最值并收集所有点
            min_x = min(min_x, x)  # 更新最小 x
            max_x = max(max_x, x)  # 更新最大 x
            point_set.add((x, y))  # 记录点，重复点自动去重
        s = min_x + max_x  # 对称轴只能是 x = s / 2；镜像点满足 x + x' = s
        return all((s - x, y) in point_set for x, y in points)  # 每个点的镜像都在集合中则对称（镜像是对合运算，逐点检查即充分）
