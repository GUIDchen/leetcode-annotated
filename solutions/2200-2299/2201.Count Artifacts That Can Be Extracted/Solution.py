# 题目：2201. 统计可以提取的工件（Count Artifacts That Can Be Extracted）
# 思路：把已挖开的格子存成 (行, 列) 集合，再对每个工件用 all 检查它的每一格是否都在集合中。
# 时间复杂度：O(d + 工件总面积)，每个格子只检查一次；空间复杂度：O(d)，集合保存 d 个格子。
class Solution:  # LeetCode 约定的题解类
    def digArtifacts(  # n：网格边长；artifacts：工件坐标列表；dig：已挖开的格子列表
        self, n: int, artifacts: List[List[int]], dig: List[List[int]]  # 参数列表续行：n 为边长，artifacts 与 dig 都是若干 [行, 列] 形式的坐标
    ) -> int:  # 返回可以提取的工件数量
        def check(a: List[int]) -> bool:  # 内部函数：判断工件 a 是否每一格都已被挖开（s 在下方定义，调用时已经存在）
            x1, y1, x2, y2 = a  # 解包工件的左上角 (x1, y1) 与右下角 (x2, y2)
            return all(  # all 遇到 False 立即短路：全部格子都在 s 中才返回 True
                (x, y) in s for x in range(x1, x2 + 1) for y in range(y1, y2 + 1)  # 用生成器表达式双重循环枚举工件覆盖的每个格子，检查是否被挖开
            )  # 结束 all(...) 的生成器

        s = {(i, j) for i, j in dig}  # 已挖开格子的集合：以 (行, 列) 元组为键，查询是 O(1)
        return sum(check(a) for a in artifacts)  # 逐个工件调用 check，True 计 1、False 计 0，求和即答案
