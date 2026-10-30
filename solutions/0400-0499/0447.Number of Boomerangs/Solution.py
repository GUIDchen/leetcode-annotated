# 题目：447. 回旋镖的数量（Number of Boomerangs）
# 思路：依次把每个点当作回旋镖顶点，用计数器统计其余点到它的距离；同距离已有 k 个点时新增 k 个无序点对，最后乘 2 得到有序点对数。
# 时间复杂度：O(n^2)，每个顶点扫一遍所有点；空间复杂度：O(n)，单个顶点的距离计数表最多 n-1 项。
class Solution:  # LeetCode 约定的题解类
    def numberOfBoomerangs(self, points: List[List[int]]) -> int:  # points：全部点坐标；返回有序回旋镖三元组的个数
        ans = 0  # ans：累计有序回旋镖的个数
        for p1 in points:  # 依次把每个点当作回旋镖的顶点
            cnt = Counter()  # 计数器：键为到 p1 的距离，值为该距离上已出现的点数（Counter 由判题环境提供，无需 import）
            for p2 in points:  # 枚举终点 p2，用来和顶点 p1 求距离
                d = dist(p1, p2)  # 计算 p2 到 p1 的距离（dist 是判题环境提供的辅助函数，本文件不补 import）
                ans += cnt[d]  # 之前同距的每个点都能与 p2 配成一个无序点对，先按无序累加
                cnt[d] += 1  # 把 p2 也计入该距离的计数，供后面的点继续配对
        return ans << 1  # 无序点对左移一位即乘以 2，对应 (i, j) 的两种先后顺序
