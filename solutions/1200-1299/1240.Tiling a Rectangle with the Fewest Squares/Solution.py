# 题目：1240. 铺瓷砖（Tiling a Rectangle with the Fewest Squares）
# 思路：按从左到右、从上到下的顺序回溯每个空格子，尝试用所有可行边长的正方形覆盖，用位表记录占用并借助当前最优解剪枝。
# 时间复杂度：最坏指数级（用最优解 ans 剪枝），空间复杂度：O(n·m) 递归深度 + O(n) 位表。
class Solution:  # LeetCode 约定的题解类
    def tilingRectangle(self, n: int, m: int) -> int:  # n 行 m 列，返回铺满矩形所需的最少正方形个数
        def dfs(i: int, j: int, t: int):  # 处理格子 (i,j)，此时已放置 t 个正方形
            nonlocal ans  # 声明让内部函数可以修改外层的最优解 ans
            if j == m:  # 本行已处理完
                i += 1  # 换到下一行
                j = 0  # 列号归零
            if i == n:  # 所有行都处理完，说明矩形已经铺满
                ans = t  # 有剪枝保证这是当前最优，直接更新答案
                return  # 结束这条分支
            if filled[i] >> j & 1:  # 当前格子已被之前的正方形覆盖
                dfs(i, j + 1, t)  # 跳过该格，接着处理右边一格
            elif t + 1 < ans:  # 只有还能比现有最优解更少时才继续试探
                r = c = 0  # r：从 (i,j) 往下连续的空格数；c：往右连续的空格数
                for k in range(i, n):  # 向下探测最大可用高度
                    if filled[k] >> j & 1:  # 第 k 行的第 j 列已被占用
                        break  # 高度探测到此为止
                    r += 1  # 可用高度加一
                for k in range(j, m):  # 向右探测最大可用宽度
                    if filled[i] >> k & 1:  # 第 i 行的第 k 列已被占用
                        break  # 宽度探测到此为止
                    c += 1  # 可用宽度加一
                mx = r if r < c else c  # 取较小值：以 (i,j) 为左上角的正方形边长上限
                for w in range(1, mx + 1):  # 依次尝试边长 1..mx 的正方形
                    for k in range(w):  # 只标记底边与右边，这些位足够判断占用
                        filled[i + w - 1] |= 1 << (j + k)  # 标记正方形底边所在的这一行
                        filled[i + k] |= 1 << (j + w - 1)  # 标记正方形右边所在的这一列
                    dfs(i, j + w, t + 1)  # 放下该正方形后，从它右侧的格子继续搜索
                for x in range(i, i + mx):  # 回溯：撤销这一轮试探留下的大量标记
                    for y in range(j, j + mx):  # 遍历 mx×mx 的整块区域
                        filled[x] ^= 1 << y  # 异或把区域内被翻转的位恢复成未占用

        ans = n * m  # 上界：每格放一个 1×1 正方形，共 n*m 块
        filled = [0] * n  # 每行一个整数位表，记录该行被占用的列
        dfs(0, 0, 0)  # 从左上角、已用 0 块开始搜索
        return ans  # 返回找到的最小块数
