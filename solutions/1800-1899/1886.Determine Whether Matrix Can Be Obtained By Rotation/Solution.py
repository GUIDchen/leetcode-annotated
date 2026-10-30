# 题目：1886. 判断矩阵经轮转后是否一致（Determine Whether Matrix Can Be Obtained By Rotation）
# 思路：一次遍历同时校验 4 种旋转角度，用 4 个二进制位记录每种旋转是否仍与 target 一致，全都失败就提前返回。
# 时间复杂度：O(n^2)，每个格子只访问一次；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def findRotation(self, mat: List[List[int]], target: List[List[int]]) -> bool:  # mat 是原矩阵，target 是目标矩阵
        n = len(mat)  # 矩阵边长（题目保证 n × n）
        ok = 0b1111  # 四个二进制位分别表示旋转 0°、90°、180°、270° 后是否仍然匹配
        for i in range(n):  # 枚举行下标
            for j in range(n):  # 枚举列下标
                if mat[i][j] != target[i][j]:  # 旋转 0°：元素位置不变
                    ok &= ~0b0001  # 清掉「0° 可行」这一位
                if mat[j][n - 1 - i] != target[i][j]:  # 旋转 90°：原 (j, n-1-i) 会落到 (i, j)
                    ok &= ~0b0010  # 清掉「90° 可行」这一位
                if mat[n - 1 - i][n - 1 - j] != target[i][j]:  # 旋转 180°：原 (n-1-i, n-1-j) 会落到 (i, j)
                    ok &= ~0b0100  # 清掉「180° 可行」这一位
                if mat[n - 1 - j][i] != target[i][j]:  # 旋转 270°：原 (n-1-j, i) 会落到 (i, j)
                    ok &= ~0b1000  # 清掉「270° 可行」这一位
                if ok == 0:  # 四种旋转都被否定，继续扫描也没有意义
                    return False  # 提前结束，直接返回不可能
        return ok != 0  # 还剩至少一位为 1，说明存在一种旋转能还原成 target
