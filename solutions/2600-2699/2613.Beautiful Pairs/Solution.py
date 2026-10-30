# 题目：2613. 美数对（Beautiful Pairs）
# 思路：先把每个点压成元组查重（重合点距离为 0 直接返回），再按 x 排序做分治「最近点对」：合并时用 |x - 中线x| <= 当前最优截出带状区域，按 y 排序后只比较 y 差不超过当前最优的对，并用下标字典序做平局裁决。
# 时间复杂度：O(n log^2 n)，每层递归都要对带状区域排序；空间复杂度：O(n)，用于哈希表、点集与递归栈。
class Solution:  # LeetCode 约定的题解类
    def beautifulPair(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1/nums2 分别给出点的横纵坐标；返回距离最小的两个下标
        def dist(x1: int, y1: int, x2: int, y2: int) -> int:  # 曼哈顿距离
            return abs(x1 - x2) + abs(y1 - y2)  # 横纵坐标差的绝对值之和

        def dfs(l: int, r: int):  # 分治：返回 points[l..r] 的 (最小距离, 较小下标, 较大下标)
            if l >= r:  # 区间内不足两个点，最近距离视为无穷大
                return inf, -1, -1  # inf 充当无穷大，下标 -1 表示无效
            m = (l + r) >> 1  # 取中点切分；右移一位等价于除以 2
            x = points[m][0]  # 中线的横坐标，合并时用来截取带状区域
            d1, pi1, pj1 = dfs(l, m)  # 左半区间的最优解
            d2, pi2, pj2 = dfs(m + 1, r)  # 右半区间的最优解
            if d1 > d2 or (d1 == d2 and (pi1 > pi2 or (pi1 == pi2 and pj1 > pj2))):  # 按 (距离, 较小下标, 较大下标) 的字典序挑出更优的一侧
                d1, pi1, pj1 = d2, pi2, pj2  # 用右半区间结果覆盖当前最优
            t = [p for p in points[l : r + 1] if abs(p[0] - x) <= d1]  # 带状区域：与中线水平距离不超过当前最优的点
            t.sort(key=lambda x: x[1])  # 按 y 升序排序；lambda 的形参 x 只是遮蔽了外层的 x，无副作用
            for i in range(len(t)):  # 枚举带状区域中每个点作为配对的一端
                for j in range(i + 1, len(t)):  # 只向 y 更大的方向找另一端，避免重复
                    if t[j][1] - t[i][1] > d1:  # y 差已超过当前最优，序号更大的点只会更远
                        break  # 直接跳出内层循环
                    pi, pj = sorted([t[i][2], t[j][2]])  # 排序后解包，得到 pi < pj，便于按下标字典序比较
                    d = dist(t[i][0], t[i][1], t[j][0], t[j][1])  # 两点的曼哈顿距离
                    if d < d1 or (d == d1 and (pi < pi1 or (pi == pi1 and pj < pj1))):  # 距离更小，或距离相同但下标对字典序更小，则更新最优
                        d1, pi1, pj1 = d, pi, pj  # 写入新的最优三元组
            return d1, pi1, pj1  # 返回本区间的最优解

        pl = defaultdict(list)  # 坐标 -> 下标列表，用来发现重合的点
        for i, (x, y) in enumerate(zip(nums1, nums2)):  # 同时遍历横纵坐标并取得下标
            pl[(x, y)].append(i)  # 记录该坐标出现的下标
        points = []  # 待分治的点集，元素为 (x, y, 原始下标)
        for i, (x, y) in enumerate(zip(nums1, nums2)):  # 按原顺序扫描，保证返回的下标对也符合偏好顺序
            if len(pl[(x, y)]) > 1:  # 该坐标重复出现，最近距离 0 已经可以确定
                return [i, pl[(x, y)][1]]  # 当前下标与同坐标的第二个下标组成答案
            points.append((x, y, i))  # 没有重合点，加入点集
        points.sort()  # 先按 x、再按 y、最后按下标排序，满足分治要求
        _, pi, pj = dfs(0, len(points) - 1)  # dfs 内部引用的 points 此时已经赋值；忽略距离本身，只取答案下标对
        return [pi, pj]  # 按下标先后返回答案
