# 3453. 分割正方形 I / Separate Squares I
# 核心思路：二分水平分割线高度 y，用每个正方形落在 y 以下的面积之和判断是否已达到总面积一半，取最小的可行高度。
# 复杂度：时间复杂度 O(n·log(maxY/eps))，空间复杂度 O(1)。
class Solution:  # 题解类
    def separateSquares(self, squares: List[List[int]]) -> float:  # 求使上下两部分面积相等的最小高度
        def check(y1: float) -> bool:  # 判断水平线 y=y1 以下的面积是否已达到总面积的一半
            t = 0  # 累加 y1 以下的面积
            for _, y, l in squares:  # 遍历每个正方形，只用到左下角纵坐标 y 与边长 l
                if y < y1:  # 正方形底边在分割线之下才会产生贡献
                    t += l * min(y1 - y, l)  # 截取高度 min(y1-y, l)，再乘宽 l 得到面积
            return t >= s / 2  # 下方面积已够一半则分割线可行

        s = sum(a[2] * a[2] for a in squares)  # 所有正方形的面积总和
        l, r = 0, max(a[1] + a[2] for a in squares)  # 二分区间：[0, 所有正方形上边界最大值]
        eps = 1e-5  # 二分精度
        while r - l > eps:  # 区间尚未收敛
            mid = (l + r) / 2  # 取中点作为候选分割线
            if check(mid):  # 中点处下方面积已满足一半
                r = mid  # 收缩右界，继续找更小的可行高度
            else:  # 中点处下方面积不足
                l = mid  # 抬高左界
        return r  # 返回满足条件的最小高度
