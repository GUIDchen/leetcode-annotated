# 题目：1361. 验证二叉树（Validate Binary Tree Nodes）
# 思路：并查集 + 入度标记。每个孩子最多一个父亲（vis 判重），连边不能成环（find 相同即为环），最终连通分量必须恰好为 1。
# 时间复杂度：O(n α(n))，并查集近似常数；空间复杂度：O(n)，父数组与 vis 数组。
class Solution:  # LeetCode 约定的题解类
    def validateBinaryTreeNodes(  # 定义题解方法；n 为节点数，leftChild/rightChild 为每个节点的左右孩子下标
        self, n: int, leftChild: List[int], rightChild: List[int]  # self 是实例本身，其余是带类型注解的参数
    ) -> bool:  # 返回值类型：是否为合法二叉树
        def find(x: int) -> int:  # 并查集查找函数：返回 x 所在集合的根
            if p[x] != x:  # p[x] != x 说明 x 还不是根，需要继续向上找
                p[x] = find(p[x])  # 递归查找并做路径压缩，把 x 直接挂到根上
            return p[x]  # 返回最终找到的根

        p = list(range(n))  # 并查集父数组初始化：每个节点各自成集合
        vis = [False] * n  # vis 标记某个节点是否已经有父亲（入度是否已达 1）
        for i, (a, b) in enumerate(zip(leftChild, rightChild)):  # 按下标 i 同时取出左右孩子 a、b
            for j in (a, b):  # 依次处理左右孩子
                if j != -1:  # -1 表示该孩子不存在，跳过
                    if vis[j] or find(i) == find(j):  # 孩子已有父亲（入度≥2）或 i、j 已连通（再连边会成环）
                        return False  # 违反二叉树定义，立即返回 False
                    p[find(i)] = find(j)  # 合并集合：把 i 的根挂到 j 的根下
                    vis[j] = True  # 记录 j 已经有父亲
                    n -= 1  # 每成功连一条边，连通分量数减一
        return n == 1  # 最终只剩一个连通分量才是合法二叉树
