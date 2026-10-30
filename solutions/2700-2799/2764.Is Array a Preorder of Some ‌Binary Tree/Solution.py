# 题目：2764. 数组是否表示某二叉树的前序遍历（Is Array a Preorder of Some Binary Tree）
# 思路：先用 nodes 建出「父 → 子」邻接表，再用指针 k 做前序 DFS：每访问一个节点必须等于 nodes[k]，匹配就消费它并递归所有孩子，最后要求所有节点都被消费完。
# 时间复杂度：O(n)，每个节点和每条边各访问一次；空间复杂度：O(n)，邻接表与递归栈的开销。
class Solution:  # LeetCode 约定的题解类
    def isPreorder(self, nodes: List[List[int]]) -> bool:  # nodes 每行是 [节点值, 父节点值]，已按前序顺序给出；返回它能否对应某棵二叉树的前序遍历
        def dfs(i: int) -> int:  # 内层递归函数 dfs(i)：判断以 i 为根的子树能否匹配 nodes[k...]（注解写的是 int，实际返回布尔值，保留原样）
            nonlocal k  # 声明 k 来自外层函数，递归中要修改它并让外层可见
            if i != nodes[k][0]:  # 前序遍历要求当前访问的节点恰好是 i，否则顺序不符
                return False  # 顺序不符，判失败
            k += 1  # 匹配成功，消费掉当前节点并把指针后移
            return all(dfs(j) for j in g[i])  # 所有子节点都按输入顺序匹配成功，本子树才算成功

        g = defaultdict(list)  # 邻接表：父节点 → 子节点列表（访问不存在的键时自动创建空列表）
        for i, p in nodes:  # 每行是 [子节点 i, 父节点 p]
            g[p].append(i)  # 把子节点按输入顺序挂到父节点下面
        k = 0  # k 是消费指针，从第一个节点开始匹配
        return dfs(nodes[0][0]) and k == len(nodes)  # 从根节点开始匹配，并确认所有节点都被消费完
