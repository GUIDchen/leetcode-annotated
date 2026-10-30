# 题目：1779. 找到最近的有相同 X 或 Y 坐标的点（Find Nearest Point That Has the Same X or Y Coordinate）
# 思路：一次遍历所有点，只保留与给定点同 x 或同 y 的点，用曼哈顿距离维护最小值，并记录最早出现的下标。
# 时间复杂度：O(n)，n 为点的个数；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def nearestValidPoint(self, x: int, y: int, points: List[List[int]]) -> int:  # x、y 是给定坐标，points 是点集
        ans, mi = -1, inf  # ans 记录答案下标（-1 表示暂无有效点），mi 记录当前最小曼哈顿距离，inf 表示无穷大
        for i, (a, b) in enumerate(points):  # 按下标从小到大遍历，同时解包出点的两个坐标
            if a == x or b == y:  # 只要有一个坐标相同，就是有效点
                d = abs(a - x) + abs(b - y)  # 计算该有效点的曼哈顿距离
                if mi > d:  # 只有严格更小才更新，距离相同时保留更小的下标
                    ans, mi = i, d  # 同时更新答案下标与最小距离
        return ans  # 返回最近有效点的下标；没有有效点时就是 -1
