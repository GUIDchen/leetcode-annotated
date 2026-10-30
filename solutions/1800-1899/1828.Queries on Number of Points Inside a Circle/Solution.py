# 题目：1828. 统计一个圆中点的数目（Queries on Number of Points Inside a Circle）
# 思路：对每个查询枚举所有点，比较平方距离与半径平方，小于等于即计入。
# 时间复杂度：O(q * p)；空间复杂度：O(q)，答案列表。
class Solution:  # LeetCode 约定的题解类
    def countPoints(  # 方法定义：points 为点集，queries 为查询列表
        self, points: List[List[int]], queries: List[List[int]]  # 参数续行：self 是实例本身，类型注解说明参数是二维整数列表
    ) -> List[int]:  # 返回每个查询命中的点数列表
        ans = []  # 结果列表
        for x, y, r in queries:  # 逐个查询：x、y 是圆心，r 是半径
            cnt = 0  # 当前查询命中点数
            for i, j in points:  # 枚举所有点
                dx, dy = i - x, j - y  # 点与圆心的坐标差
                cnt += dx * dx + dy * dy <= r * r  # 平方距离比较，布尔值可直接当 0/1 累加
            ans.append(cnt)  # 记录该查询的答案
        return ans  # 返回所有答案
