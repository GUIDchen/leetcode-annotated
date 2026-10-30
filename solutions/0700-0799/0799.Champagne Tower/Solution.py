# 题目：799. 香槟塔（Champagne Tower）
# 思路：按行递推，f[i][j] 表示流经第 i 行第 j 个杯子的香槟量；杯子最多留住 1 杯，超出的部分平分成两半流给下一行的两个杯子，推到查询所在行即可。
# 时间复杂度：O(query_row²)，逐行逐杯递推；空间复杂度：O(1)，固定 101x101 的表格。
class Solution:  # LeetCode 约定的题解类
    def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:  # poured：总杯数；query_row、query_glass：要查询的杯子坐标
        f = [[0] * 101 for _ in range(101)]  # f[i][j]：流经第 i 行第 j 个杯子的香槟量
        f[0][0] = poured  # 顶端杯子先倒入全部香槟
        for i in range(query_row + 1):  # 只需递推到查询所在行
            for j in range(i + 1):  # 第 i 行共有 i+1 个杯子
                if f[i][j] > 1:  # 只有满溢的杯子才会往下流
                    half = (f[i][j] - 1) / 2  # 溢出量平分给下面两个杯子
                    f[i][j] = 1  # 自己最多留下 1 杯
                    f[i + 1][j] += half  # 左下方杯子分到一半
                    f[i + 1][j + 1] += half  # 右下方杯子分到另一半
        return f[query_row][query_glass]  # 返回目标杯中的香槟量（未装满时就是流入量）
