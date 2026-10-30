# 题目：3027. 人员站位的方案数 II（Find the Number of Ways to Place People II）
# 核心思路：与 I 同一套做法——按 (x 升序, y 降序) 排序，枚举左上角 i 后向右扫描 j 并维护已遇到的最大纵坐标 max_y；只有 max_y < y2 ≤ y1 时才说明矩形内没有第三人，方案数 +1，从而避免 O(n^3) 检查矩形内部。
# 时间复杂度：O(n^2)，n ≤ 1000 时可接受；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfPairs(self, points: List[List[int]]) -> int:  # points：所有点坐标 [x, y]；返回合法的站位方案数
        points.sort(key=lambda x: (x[0], -x[1]))  # 自定义排序：x 升序，x 相同时 y 降序
        ans = 0  # ans：累计的合法方案数
        for i, (_, y1) in enumerate(points):  # 枚举矩形左上角 i，取出它的纵坐标 y1
            max_y = -inf  # max_y：i 之后已扫描点的最大纵坐标，用来排除矩形内部的点
            for _, y2 in points[i + 1 :]:  # 枚举右下角 j，只需考虑排在 i 之后的点
                if max_y < y2 <= y1:  # y2 落在 (max_y, y1] 内，说明这个矩形内部没有其它点
                    max_y = y2  # 更新已遇到的最大纵坐标，以后更低的点都会被它挡住
                    ans += 1  # 找到一种合法站位方案
        return ans  # 返回方案总数
