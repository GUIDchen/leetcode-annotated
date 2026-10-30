# 题目：939. 最小面积矩形（Minimum Area Rectangle）
# 思路：按 x 分组得到每列的 y 列表，枚举同列内的 y 对，用字典记住该 y 对上次出现的 x，不同 x 上出现同一 y 对即构成矩形。
# 时间复杂度：O(n²)，每列内枚举 y 对；空间复杂度：O(n)，存分组与边对字典。
class Solution:  # LeetCode 约定的题解类
    def minAreaRect(self, points: List[List[int]]) -> int:  # points 是点集，返回最小矩形面积，找不到时返回 0
        d = defaultdict(list)  # 按 x 分组：键是横坐标，值是该列所有 y 坐标组成的列表
        for x, y in points:  # 解包每个点的横纵坐标
            d[x].append(y)  # 把 y 追加进对应的列分组
        pos = {}  # 字典：(y1, y2) 边对 → 最近一次出现该边对的 x
        ans = inf  # 答案初值取正无穷，方便后面用 min 更新
        for x in sorted(d):  # 按 x 升序遍历各列，保证后处理的列更靠右
            ys = d[x]  # 当前列上所有 y 坐标
            ys.sort()  # 排序后枚举可保证 y1 < y2
            n = len(ys)  # 当前列的点数
            for i, y1 in enumerate(ys):  # 枚举边对的下端点 y1 及其下标
                for y2 in ys[i + 1 :]:  # 只遍历 i 之后的部分，避免重复枚举与 y1 == y2
                    if (y1, y2) in pos:  # 之前某列也有同样的 (y1, y2)，可以围成矩形
                        ans = min(ans, (x - pos[(y1, y2)]) * (y2 - y1))  # 面积 = 宽 × 高，更新最小值
                    pos[(y1, y2)] = x  # 记录/刷新该边对最近出现的 x
        return 0 if ans == inf else ans  # 始终没围成矩形则返回 0
