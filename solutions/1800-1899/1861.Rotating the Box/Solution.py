# 题目：1861. 旋转盒子（Rotating the Box）
# 思路：先按顺时针 90° 把 m×n 矩阵搬到 n×m 的 ans（原 (i, j) → 新 (j, m-1-i)），再逐列自下而上用双端队列记录空位，模拟石头下落，遇到障碍 '*' 就清空队列。
# 时间复杂度：O(mn)，旋转与下落各扫描一遍；空间复杂度：O(mn)，保存旋转后的答案矩阵。
class Solution:  # LeetCode 约定的题解类
    def rotateTheBox(self, boxGrid: List[List[str]]) -> List[List[str]]:  # boxGrid：m 行 n 列的原始盒子
        m, n = len(boxGrid), len(boxGrid[0])  # m 为行数，n 为列数
        ans = [[None] * m for _ in range(n)]  # 旋转后变成 n 行 m 列，先全部填 None 占位
        for i in range(m):  # 遍历原矩阵的每一行
            for j in range(n):  # 遍历这一行的每一列
                ans[j][m - i - 1] = boxGrid[i][j]  # 顺时针旋转公式：原 (i, j) 落到新 (j, m-1-i)
        for j in range(m):  # 逐列模拟重力，ans 共 m 列、每列 n 个格子
            q = deque()  # 双端队列保存当前列可落空的空位行号，队首是最靠下的空位
            for i in range(n - 1, -1, -1):  # 从列底往上扫描
                if ans[i][j] == "*":  # 遇到固定障碍：它上面的石头无法再穿过这里
                    q.clear()  # 清空队列，障碍上方的空位对下方石头不再可用
                elif ans[i][j] == ".":  # 空格子：记录为一个可以落石的位置
                    q.append(i)  # 自下而上入队，队首始终是最底部的空位
                elif q:  # 剩下只能是石头 '#'：若下方还有空位就让石头下落
                    ans[q.popleft()][j] = "#"  # 石头落到最靠下的空位
                    ans[i][j] = "."  # 石头原位置变成空位
                    q.append(i)  # 新空出的位置可以继续承接上方石头
        return ans  # 返回旋转并重排后的盒子
