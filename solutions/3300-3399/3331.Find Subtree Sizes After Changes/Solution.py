# 题目：3331. 修改后子树的大小（Find Subtree Sizes After Changes）
# 思路：建树后 DFS，用 d[字符] 栈保存路径上的同字母节点；回溯时把子树大小累加到最近的同字母祖先（没有就累加到原父亲），从而模拟父子关系的改变。
# 时间复杂度：O(n)，每个节点进出栈各一次；空间复杂度：O(n)，邻接表、栈与答案数组。
class Solution:  # LeetCode 约定的题解类
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:  # parent 是父节点数组，s 是每个节点的字符；返回修改后的子树大小
        def dfs(i: int, fa: int):  # 递归函数：i 是当前节点，fa 是它在原树中的父亲
            ans[i] = 1  # 子树至少包含自己
            d[s[i]].append(i)  # 当前节点入栈，字符相同的后代能把它当作最近的祖先
            for j in g[i]:  # 依次处理所有孩子
                dfs(j, i)  # 递归统计孩子的子树大小
            k = fa  # 先假设新父亲就是原父亲 fa
            if len(d[s[i]]) > 1:  # 栈里还有更早的同字母节点，说明存在最近的同字母祖先
                k = d[s[i]][-2]  # 取次栈顶（-2）作为新父亲，栈顶是当前节点自己
            if k != -1:  # -1 表示根节点没有父亲，无处累加
                ans[k] += ans[i]  # 把当前子树大小累加到新父亲，等价于完成改接
            d[s[i]].pop()  # 回溯：当前节点离开 DFS 路径，出栈

        n = len(s)  # 节点总数
        g = [[] for _ in range(n)]  # 邻接表：g[u] 存放 u 的所有孩子
        for i in range(1, n):  # 0 是根节点，从 1 开始挂接孩子
            g[parent[i]].append(i)  # 把 i 挂到父亲 parent[i] 下面
        d = defaultdict(list)  # 每个字符对应一个栈，记录 DFS 路径上该字符的节点
        ans = [0] * n  # 答案数组，初始全 0
        dfs(0, -1)  # 从根节点 0 开始 DFS，父亲的哨兵为 -1
        return ans  # 返回每个节点的子树大小
