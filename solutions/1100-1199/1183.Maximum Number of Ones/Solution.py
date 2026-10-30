# 题目：1183. 矩阵中 1 的最大数量（Maximum Number of Ones）
# 思路：把格子按 (i % x, j % x) 分成 x*x 个等价类（x = sideLength），同一个边长 x 的方阵恰好含各类各一个；
#       所以每个方阵最多放 maxOnes 个 1，等价于选 maxOnes 个格子数最多的类。
class Solution:  # LeetCode 约定的题解类
    def maximumNumberOfOnes(  # width/height 为矩阵尺寸，sideLength 为方阵边长，maxOnes 为每个方阵内 1 的上限
        self, width: int, height: int, sideLength: int, maxOnes: int  # 签名换行只是排版，形参含义同上
    ) -> int:  # 返回最多能放下的 1 的个数
        x = sideLength  # 简写周期长度，后面要反复取模
        cnt = [0] * (x * x)  # 按 (i%x, j%x) 划分出 x*x 个等价类，记录每类格子数
        for i in range(width):  # 枚举行下标
            for j in range(height):  # 枚举列下标
                k = (i % x) * x + (j % x)  # 坐标模 x 后相同即在每个方阵中互相挤占，归为同一类
                cnt[k] += 1  # 该类格子数 +1
        cnt.sort(reverse=True)  # 降序排序：格子数多的等价类优先放 1
        return sum(cnt[:maxOnes])  # 每个方阵最多 maxOnes 个 1，累加最大的 maxOnes 个等价类
