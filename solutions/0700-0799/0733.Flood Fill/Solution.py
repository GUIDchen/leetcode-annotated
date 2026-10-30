# 题目：733. 图像渲染（Flood Fill）
# 思路：从 (sr, sc) 出发做深度优先搜索，把与起始像素同色且四连通的格子全部改成 color；起始色与目标色相同则不做任何改动，避免无限递归。
# 时间复杂度：O(m·n)，每个格子最多访问一次；空间复杂度：O(m·n)，递归栈最坏深度。
class Solution:  # LeetCode 约定的题解类
    def floodFill(  # 函数签名换行书写，参数在下一行继续
        self, image: List[List[int]], sr: int, sc: int, color: int  # image 是像素矩阵，sr、sc 是起点行列，color 是目标颜色
    ) -> List[List[int]]:  # 返回染色后的矩阵
        def dfs(i: int, j: int):  # 内部 DFS：把 (i, j) 所在连通块染成 color
            image[i][j] = color  # 进入格子先染色，天然兼作已访问标记
            for a, b in pairwise(dirs):  # pairwise 把方向数组两两配对成四个方向（LeetCode 环境已预置该函数）
                x, y = i + a, j + b  # 按方向得到邻居坐标
                if 0 <= x < len(image) and 0 <= y < len(image[0]) and image[x][y] == oc:  # 邻居在边界内且仍是原来的颜色，才继续扩散
                    dfs(x, y)  # 递归处理邻居

        oc = image[sr][sc]  # 记下起点原来的颜色，用于判断是否属于同一连通块
        if oc != color:  # 起始颜色与目标颜色不同时才需要染色，否则会无限递归
            dirs = (-1, 0, 1, 0, -1)  # 方向数组：连续两两组成四个方向
            dfs(sr, sc)  # 从起点开始搜索染色
        return image  # 返回染色后的矩阵（未染色时原样返回）
