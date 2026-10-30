# 题目：3102. 最小化曼哈顿距离（Minimize Manhattan Distances）
# 思路：做切比雪夫变换 u = x + y、v = x - y，则最大曼哈顿距离等于 max(max u - min u, max v - min v)；枚举删掉的点，用有序列表随时取两族值的最小/最大值。
# 时间复杂度：O(n log n)，SortedList 的插入与删除都是对数级；空间复杂度：O(n)，两个有序列表各存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def minimumDistance(self, points: List[List[int]]) -> int:  # points：所有点坐标，返回删掉一个点后其余点之间最大曼哈顿距离的最小可能值
        sl1 = SortedList()  # 有序列表一：维护所有已存在点的 x + y
        sl2 = SortedList()  # 有序列表二：维护所有已存在点的 x - y
        for x, y in points:  # 先遍历全部点建立两个有序列表
            sl1.add(x + y)  # 把 x + y 加入第一个列表
            sl2.add(x - y)  # 把 x - y 加入第二个列表
        ans = inf  # 答案先设为无穷大，等待取 min
        for x, y in points:  # 依次枚举“被删掉的那个点”
            sl1.remove(x + y)  # 从列表一中删掉一个该值
            sl2.remove(x - y)  # 从列表二中删掉一个该值
            ans = min(ans, max(sl1[-1] - sl1[0], sl2[-1] - sl2[0]))  # 删点后剩余点的最大曼哈顿距离等于两族极差中的较大者（sl[0] 最小、sl[-1] 最大），用它更新答案
            sl1.add(x + y)  # 把该点还原到列表一，供下一轮枚举使用
            sl2.add(x - y)  # 把该点还原到列表二
        return ans  # 返回最小的“剩余点最大曼哈顿距离”
