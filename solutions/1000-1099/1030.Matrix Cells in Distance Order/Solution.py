# 题目：1030. 距离顺序排列矩阵单元格（Matrix Cells in Distance Order）
# 思路：从中心点做 BFS，第 k 层恰好是所有曼哈顿距离为 k 的格子，出队顺序天然满足距离升序。
# 时间复杂度：O(rows*cols)，每格只入队出队一次；空间复杂度：O(rows*cols)，队列与访问标记。
class Solution:  # LeetCode 约定的题解类
    def allCellsDistOrder(  # 返回所有单元格按到 (rCenter, cCenter) 曼哈顿距离升序排列的结果
        self, rows: int, cols: int, rCenter: int, cCenter: int  # 参数续行：rows 行数、cols 列数、rCenter/cCenter 中心坐标
    ) -> List[List[int]]:  # 参数续行结束，返回二维坐标列表
        q = deque([[rCenter, cCenter]])  # 双端队列初始化为中心点，作为 BFS 的第 0 层
        vis = [[False] * cols for _ in range(rows)]  # 访问标记表，先全部建成 False
        vis[rCenter][cCenter] = True  # 起点立即标记为已访问，避免重复入队
        ans = []  # 收集出队顺序，即答案要求的距离升序
        while q:  # 队列非空就继续按层扩展
            for _ in range(len(q)):  # 固定当前层长度，只处理这一层，保证同层距离相等
                p = q.popleft()  # 从队首取出一个单元格
                ans.append(p)  # 出队顺序就是距离升序，直接加入答案
                for a, b in pairwise((-1, 0, 1, 0, -1)):  # pairwise 把方向元组两两配对，得到 (行偏移, 列偏移)
                    x, y = p[0] + a, p[1] + b  # 计算相邻格子的坐标
                    if 0 <= x < rows and 0 <= y < cols and not vis[x][y]:  # 行列不越界且该格未访问过
                        vis[x][y] = True  # 先标记已访问，防止被多个邻居重复入队
                        q.append([x, y])  # 合法邻居入队，成为下一层
        return ans  # 队列空表示所有可达格子都处理完，返回答案
