# 题目：1620. 网络信号最好的坐标（Coordinate With Maximum Network Quality）
# 思路：坐标范围很小（0~50），暴力枚举所有整数点，累加半径内每个信号塔的 floor(q/(1+d))，取质量最大的点（并列时取字典序最小）。
# 时间复杂度：O(51^2 * n)，n 为信号塔数量；空间复杂度：O(1)，只保存当前最优坐标与最大质量。
class Solution:  # LeetCode 约定的题解类
    def bestCoordinate(self, towers: List[List[int]], radius: int) -> List[int]:  # towers：每项是 [x, y, q]；radius：信号半径
        mx = 0  # 当前扫到的最大网络质量（初始 0，保证任何点都会被比较一次）
        ans = [0, 0]  # 记录取得最大质量的坐标，默认原点
        for i in range(51):  # 枚举横坐标 0~50
            for j in range(51):  # 枚举纵坐标 0~50
                t = 0  # 当前这个候选点的网络质量总和
                for x, y, q in towers:  # 遍历所有信号塔
                    d = ((x - i) ** 2 + (y - j) ** 2) ** 0.5  # 欧氏距离：平方和再开 0.5 次方
                    if d <= radius:  # 落在信号覆盖范围内才贡献质量
                        t += floor(q / (1 + d))  # 质量按 q/(1+d) 向下取整后累加
                if t > mx:  # 严格大于才更新，并列时保留先枚举到的更小坐标
                    mx = t  # 记录新的最大质量
                    ans = [i, j]  # 记录取得该质量的坐标
        return ans  # 返回网络信号最好的整数坐标
