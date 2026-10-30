# 题目：2445. 值为 1 的节点数（Number of Nodes With Value One，🔒 会员题）
# 思路：同一节点被翻转偶数次相互抵消，只对出现奇数次的查询节点做 DFS 翻转整棵子树，最后求和得到 1 的个数。
# 时间复杂度：O(q + 各奇数查询节点的子树大小之和)，最坏 O(n·q)；空间复杂度：O(n)，tree 数组加递归栈。
class Solution:  # LeetCode 约定的题解类
    def numberOfNodes(self, n: int, queries: List[int]) -> int:  # n 是节点总数，queries 是每次翻转子树的根节点编号
        def dfs(i):  # 内层函数：以 i 为根，把整棵子树的值翻转一次
            if i > n:  # 编号超过 n 说明该子树为空
                return  # 直接回溯，什么都不做
            tree[i] ^= 1  # 与 1 异或实现 0/1 翻转
            dfs(i << 1)  # 递归翻转左儿子 2*i
            dfs(i << 1 | 1)  # 递归翻转右儿子 2*i+1；移位优先级高于按位或

        tree = [0] * (n + 1)  # tree[i] 是节点 i 的值，下标 0 弃用，初始全为 0（dfs 调用时它已存在）
        cnt = Counter(queries)  # 统计每个节点作为查询根出现的次数
        for i, v in cnt.items():  # 只遍历出现过的查询节点
            if v & 1:  # 只有奇数次查询才真正生效，偶数次互相抵消
                dfs(i)  # 翻转以 i 为根的整棵子树
        return sum(tree)  # 求和即值为 1 的节点数（下标 0 恒为 0）
