# 题目：2003. 每棵子树内缺失的最小基因值（Smallest Missing Genetic Value in Each Subtree）
# 思路：只有「根到基因值 1 的节点」这条链上的祖先，其子树才可能包含 1、答案才可能大于 1；其余子树答案恒为 1。从基因值 1 出发沿父指针自底向上，用 DFS 把子树里出现过的基因值累加进集合，指针 i 单调递增地找最小缺失值。
# 时间复杂度：O(n)，每个节点最多被 DFS 访问一次，指针 i 也只增不减；空间复杂度：O(n)，邻接表与两个标记数组。
class Solution:  # LeetCode 约定的题解类
    def smallestMissingValueSubtree(  # parents 给出每个节点的父节点，nums 给出每个节点上的基因值；返回每棵子树缺失的最小基因值
        self, parents: List[int], nums: List[int]  # 参数行：parents 是父节点数组，nums 是基因值数组
    ) -> List[int]:  # 返回值的类型标注：与 nums 等长的答案数组
        def dfs(i: int):  # 递归函数 dfs(i)：把以 i 为根的子树里出现过的基因值全部登记到 has 中
            if vis[i]:  # 该节点已经访问过，说明整棵子树都登记过了
                return  # 直接返回，避免重复计算
            vis[i] = True  # 标记为已访问，防止后续重复进入
            if nums[i] < len(has):  # 只登记落在 has 数组范围内的基因值，防止越界写
                has[nums[i]] = True  # 记录这个基因值已经出现
            for j in g[i]:  # 继续递归处理所有子节点
                dfs(j)  # 递归登记子节点的子树

        n = len(nums)  # n 是节点总数，编号 0 ~ n-1，0 号是根
        ans = [1] * n  # 答案默认全为 1：不含基因值 1 的子树，缺失的最小基因值一定是 1
        g = [[] for _ in range(n)]  # g[i] 存节点 i 的所有子节点，用它把树存成邻接表
        idx = -1  # idx 记录基因值等于 1 的节点编号，没找到则为 -1
        for i, p in enumerate(parents):  # 一次遍历同时建树并定位基因值 1
            if i:  # 根节点 0 没有父节点，跳过
                g[p].append(i)  # 把节点 i 挂到父节点 p 的子节点列表里
            if nums[i] == 1:  # 基因值等于 1 的节点是自底向上遍历的起点
                idx = i  # 记下该节点编号，后面沿父指针往上走
        if idx == -1:  # 整棵树都没有基因值 1
            return ans  # 直接返回全 1 的答案
        vis = [False] * n  # vis[i] 标记节点 i 是否已经被 DFS 访问过
        has = [False] * (n + 2)  # has[v] 标记基因值 v 是否已经出现在当前累积的子树集合里；多开两格防止越界
        i = 2  # 最小缺失值指针，从 2 开始且只会增大
        while idx != -1:  # 从基因值 1 的节点出发，沿父指针一路上移，-1 表示走到根之上
            dfs(idx)  # 先把当前节点整棵子树里出现的基因值都登记进来
            while has[i]:  # 单调递增地跳过所有已经出现过的基因值
                i += 1  # 该值已在子树中出现，继续往后找
            ans[idx] = i  # 当前子树的答案就是第一个没有出现过的最小基因值 i
            idx = parents[idx]  # 沿父指针继续向上处理祖先节点
        return ans  # 返回所有子树的答案
