# 题目：212. 单词搜索 II（Word Search II）
# 思路：把所有单词建成前缀树，再从矩阵每个格子出发做 DFS；沿途沿前缀树下走，走到单词结尾就收集，并用 # 标记回溯。
# 时间复杂度：O(m * n * 4^L)，L 为单词最大长度（前缀树剪枝后远小于此）；空间复杂度：O(总字符数 + L)。
class Trie:  # 前缀树节点：26 个儿子 + 单词下标
    def __init__(self):  # 构造一个空节点
        self.children: List[Trie | None] = [None] * 26  # 26 个槽位对应 a~z
        self.ref: int = -1  # 是单词结尾时存它在 words 中的下标，否则为 -1

    def insert(self, w: str, ref: int):  # 把单词 w 插入前缀树，并记下下标 ref
        node = self  # 从根节点出发
        for c in w:  # 逐字符建路径
            idx = ord(c) - ord('a')  # 字符映射成 0~25 的下标
            if node.children[idx] is None:  # 该字母分支不存在
                node.children[idx] = Trie()  # 新建子节点
            node = node.children[idx]  # 向下走一层
        node.ref = ref  # 末尾节点记住单词下标


class Solution:  # LeetCode 约定的题解类
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:  # board 是字母矩阵，words 是待查找的单词表
        def dfs(node: Trie, i: int, j: int):  # DFS：从格子 (i, j) 出发，在树的 node 位置继续往下匹配
            idx = ord(board[i][j]) - ord('a')  # 当前格子字符对应的分支下标
            if node.children[idx] is None:  # 前缀树里没有这条分支
                return  # 剪枝：走不出任何单词
            node = node.children[idx]  # 沿该字符向下走一层
            if node.ref >= 0:  # 当前节点是某个单词的结尾
                ans.append(words[node.ref])  # 把该单词加入答案
                node.ref = -1  # 置 -1，避免同一个单词重复加入
            c = board[i][j]  # 记下原字符，回溯时还原
            board[i][j] = '#'  # 标记已访问，防止同一次路径里重复踩格
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # pairwise 把序列两两配对，配出上、右、下、左四组方向（依赖判题器已导入 pairwise）
                x, y = i + a, j + b  # 相邻格子的坐标
                if 0 <= x < m and 0 <= y < n and board[x][y] != '#':  # 坐标合法且该格未被访问
                    dfs(node, x, y)  # 递归搜索该相邻格子
            board[i][j] = c  # 回溯：还原字符

        tree = Trie()  # 建一棵空前缀树
        for i, w in enumerate(words):  # 逐个单词插入
            tree.insert(w, i)  # 同时记下它在 words 中的下标
        m, n = len(board), len(board[0])  # 矩阵的行数与列数
        ans = []  # 存放找到的单词
        for i in range(m):  # 枚举每个起点行
            for j in range(n):  # 枚举每个起点列
                dfs(tree, i, j)  # 以 (i, j) 为起点开始匹配
        return ans  # 返回所有找到的单词
