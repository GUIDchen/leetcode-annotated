# 题目：3030. 找出网格的区域平均强度（Find the Grid of Region Average）
# 思路：枚举每个 3×3 子网格，用按位与累积「所有相邻格子差值都不超过阈值」这一条件；合法区域先整数除法求平均，累加到 9 个格子并记录覆盖次数，最后除以覆盖次数。
# 时间复杂度：O(n * m)，每个区域是常数次操作；空间复杂度：O(n * m)，需要 ans 与 ct 两个矩阵。
class Solution:  # LeetCode 约定的题解类
    def resultGrid(self, image: List[List[int]], threshold: int) -> List[List[int]]:  # image：原始网格；threshold：相邻格子允许的最大差值
        n, m = len(image), len(image[0])  # n：行数；m：列数
        ans = [[0] * m for _ in range(n)]  # ans：每个格子所属区域平均强度之和
        ct = [[0] * m for _ in range(n)]  # ct：每个格子被多少个合法区域覆盖
        for i in range(n - 2):  # 枚举区域左上角行号，保证 3 行都在网格内
            for j in range(m - 2):  # 枚举区域左上角列号，保证 3 列都在网格内
                region = True  # 先假设该 3×3 区域合法
                for k in range(3):  # 逐行检查水平方向的相邻对
                    for l in range(2):  # 每行有 2 对水平相邻格子
                        region &= (  # 用按位与累积合法性，任意一对不满足就变 False
                            abs(image[i + k][j + l] - image[i + k][j + l + 1])  # 水平相邻两格差值的绝对值
                            <= threshold  # 差值不超过阈值才合法
                        )
                for k in range(2):  # 逐行检查竖直方向的相邻对，只需前 2 行
                    for l in range(3):  # 每列各有一个竖直相邻对
                        region &= (  # 同样用按位与累积合法性
                            abs(image[i + k][j + l] - image[i + k + 1][j + l])  # 竖直相邻两格差值的绝对值
                            <= threshold  # 差值不超过阈值才合法
                        )

                if region:  # 区域合法才参与统计
                    tot = 0  # tot：区域元素总和
                    for k in range(3):  # 遍历区域内的行
                        for l in range(3):  # 遍历区域内的列
                            tot += image[i + k][j + l]  # 累加元素值
                    for k in range(3):  # 再把平均值写到区域内的每个格子
                        for l in range(3):  # 遍历区域内的列
                            ct[i + k][j + l] += 1  # 该格子的覆盖次数加一
                            ans[i + k][j + l] += tot // 9  # 先用整数除法求区域平均，再累加

        for i in range(n):  # 整理结果：逐行
            for j in range(m):  # 逐列
                if ct[i][j] == 0:  # 没有被任何合法区域覆盖
                    ans[i][j] = image[i][j]  # 保持原始强度
                else:  # 至少被一个合法区域覆盖
                    ans[i][j] //= ct[i][j]  # 平均强度之和除以覆盖次数得到最终值

        return ans  # 返回处理后的新网格
