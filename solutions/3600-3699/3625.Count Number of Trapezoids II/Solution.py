# 3625. Count Number of Trapezoids II（3625. 统计梯形的数目 II）
# 核心思路：枚举所有点对得直线 (k, b) 与中点，cnt1 统计同斜率下不同截距的线段数，cnt2 统计同斜率同中点的线段数；按前缀和两两组合，前者累加、后者扣除共线退化情形。
# 复杂度：时间 O(n^2) 建表 + O(n^2) 统计，空间 O(n^2) 存储线段信息。
class Solution:  # 定义题解类
    def countTrapezoids(self, points: List[List[int]]) -> int:  # 统计所有点对构成的梯形数目
        n = len(points)  # 点的个数

        # cnt1: k -> (b -> count)，k 为斜率、b 为截距
        cnt1: dict[float, dict[float, int]] = defaultdict(lambda: defaultdict(int))  # 斜率 -> (截距 -> 线段数)
        # cnt2: p -> (k -> count)，p 为中点编码、k 为斜率
        cnt2: dict[int, dict[float, int]] = defaultdict(lambda: defaultdict(int))  # 中点编码 -> (斜率 -> 线段数)

        for i in range(n):  # 枚举点对 (i, j)，j < i
            x1, y1 = points[i]  # 第一个点的坐标
            for j in range(i):  # 只需枚举 j < i，避免重复
                x2, y2 = points[j]  # 第二个点的坐标
                dx, dy = x2 - x1, y2 - y1  # 两点坐标差

                if dx == 0:  # 竖直线，斜率不存在
                    k = 1e9  # 用一个极大值代替斜率
                    b = x1  # 用横坐标代替截距
                else:  # 一般情况
                    k = dy / dx  # 计算斜率
                    b = (y1 * dx - x1 * dy) / dx  # 计算截距

                cnt1[k][b] += 1  # 累计该直线上的线段数

                p = (x1 + x2 + 2000) * 4001 + (y1 + y2 + 2000)  # 把中点坐标编码成一个整数
                cnt2[p][k] += 1  # 累计该中点、该斜率的线段数

        ans = 0  # 答案：梯形数目

        for e in cnt1.values():  # 遍历每个斜率分组
            s = 0  # 之前各截距上线段数的前缀和
            for t in e.values():  # 遍历该斜率下每条直线的线段数
                ans += s * t  # 不同直线上的线段两两配对，形成平行底边
                s += t  # 累加前缀和

        for e in cnt2.values():  # 遍历每个中点分组
            s = 0  # 之前各斜率上线段数的前缀和
            for t in e.values():  # 遍历该中点下的线段数
                ans -= s * t  # 同中点同斜率说明线段共线重叠，属于退化情况要扣除
                s += t  # 累加前缀和

        return ans  # 返回统计结果
