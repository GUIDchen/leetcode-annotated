# 题目：2791. 树中可以形成回文的路径数（Count Paths That Can Form a Palindrome in a Tree）
# 思路：把字母映射成二进制位，dfs 求根到每个节点的路径异或值；两段路径异或值相同或只差一位时可拼成回文，用计数器累计答案。
# 时间复杂度：O(n * 26)，每个节点查询 26 个状态（26 为常量，可视为 O(n)）；空间复杂度：O(n)，存邻接表与计数器。
class Solution:  # LeetCode 约定的题解类
    def countPalindromePaths(self, parent: List[int], s: str) -> int:  # parent：每个节点的父节点；s：节点到父节点这条边上的字母
        def dfs(i: int, xor: int):  # 深度优先搜索：i 是当前节点，xor 是根到 i 的路径异或值
            nonlocal ans  # 声明 ans 来自外层作用域，函数内需要修改它
            for j, v in g[i]:  # 遍历当前节点的全部子节点 j，v 是该边的字母掩码
                x = xor ^ v  # 根到 j 的路径异或值（变量名沿用题目写法）
                ans += cnt[x]  # 之前出现过相同异或值：两段路径异或为 0，所有字母都是偶数次，可构成回文
                for k in range(26):  # 枚举 26 个字母，允许其中一个出现奇数次
                    ans += cnt[x ^ (1 << k)]  # 异或值只差一位时，两段路径之间恰好一种字母为奇数个，同样可构成回文
                cnt[x] += 1  # 把当前异或值的出现次数加一，供子树查询
                dfs(j, x)  # 继续向子树深入

        # 图、答案与计数器在 dfs 定义之后才创建；闭包在调用时才解析这些自由变量，所以顺序没问题
        n = len(parent)  # 节点总数
        g = defaultdict(list)  # 邻接表：g[p] 存放 (子节点, 该边字母掩码)
        for i in range(1, n):  # 0 号节点是根，从 1 号节点开始建立父子边
            p = parent[i]  # 当前节点的父节点
            g[p].append((i, 1 << (ord(s[i]) - ord('a'))))  # 用 1 << (字母偏移) 作为边权，挂到父节点的邻接表上
        ans = 0  # ans：满足回文条件的路径对数
        cnt = Counter({0: 1})  # 计数器：空前缀的异或值为 0，初始出现一次
        dfs(0, 0)  # 从根节点开始搜索，根到根的路径异或值为 0
        return ans  # 返回可构成回文的路径总数
