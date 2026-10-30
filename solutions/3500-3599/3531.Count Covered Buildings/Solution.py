# 题目：3531. 统计被覆盖的建筑（Count Covered Buildings）
# 思路：按列、按行分别收集坐标并排序。若某建筑在同一列中存在 x 更小和更大的建筑、同一行中存在 y 更小和更大的建筑，则它上下左右都有建筑，被覆盖。
# 时间复杂度：O(m log m)，m 为建筑数量（排序开销）；空间复杂度：O(m)，两个哈希表存坐标。
class Solution:  # LeetCode 约定的题解类
    def countCoveredBuildings(self, n: int, buildings: List[List[int]]) -> int:  # n 为城市边长，buildings[i] = [x, y] 是互不相同的建筑坐标
        g1 = defaultdict(list)  # g1[x] 存同一列（x 相同）所有建筑的 y 坐标
        g2 = defaultdict(list)  # g2[y] 存同一行（y 相同）所有建筑的 x 坐标
        for x, y in buildings:  # 一次遍历收集行列信息
            g1[x].append(y)  # 按列归入
            g2[y].append(x)  # 按行归入
        for x in g1:  # 逐列处理
            g1[x].sort()  # 该列的 y 坐标升序排序，便于取最小/最大值
        for y in g2:  # 逐行处理
            g2[y].sort()  # 该行的 x 坐标升序排序
        ans = 0  # 被覆盖的建筑数量
        for x, y in buildings:  # 逐个建筑判断是否被覆盖
            l1 = g1[x]  # 同一列中所有建筑的 y 列表
            l2 = g2[y]  # 同一行中所有建筑的 x 列表
            if l2[0] < x < l2[-1] and l1[0] < y < l1[-1]:  # 同一列里有更小和更大的 y，同一行里有更小和更大的 x，即上下左右都有建筑
                ans += 1  # 满足被覆盖条件，计数加一
        return ans  # 返回被覆盖的建筑数量
