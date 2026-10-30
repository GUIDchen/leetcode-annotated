# 题目：2115. 从给定原材料中找到所有可以做出的菜（Find All Possible Recipes from Given Supplies）
# 思路：建「原料 → 依赖它的菜」的图并记录每道菜的入度；从初始原料出发不断把入度减到 0 的菜加入答案（拓扑排序）。
# 时间复杂度：O(N + E)，N 为原料/菜总数、E 为依赖边数；空间复杂度：O(N + E)，存图与入度表。
class Solution:# LeetCode 约定的题解类
    def findAllRecipes(# recipes：菜名；ingredients：所需原料；supplies：初始原料；返回能做出的菜
        self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]# 参数说明续行：与上一行共同构成完整签名
    ) -> List[str]:# 返回能做出的菜名列表
        g = defaultdict(list)# 邻接表：原料 -> 依赖它的菜（依赖图的反向边）
        indeg = defaultdict(int)# 每道菜的入度 = 还缺的原料种数
        for a, b in zip(recipes, ingredients):# 同时遍历菜名与它的原料清单
            for v in b:# 遍历这道菜需要的每一种原料
                g[v].append(a)# 建立反向边：原料 v 指向菜 a
            indeg[a] += len(b)# 菜 a 的初始入度就是所需原料总数
        q = supplies# 直接复用 supplies 当 BFS 队列，它同时充当「已得材料」集合
        ans = []# 记录能做出的菜
        for i in q:# 边遍历边追加：Python 的 for 会继续看到列表后面新增的元素
            for j in g[i]:# 遍历依赖材料 i 的菜
                indeg[j] -= 1# 材料 i 已可得，菜 j 少缺一种原料
                if indeg[j] == 0:# 入度归零说明原料已全部凑齐
                    ans.append(j)# 这道菜可以做了，记入答案
                    q.append(j)# 它又成为新可得材料，追加到队列继续扩散
        return ans# 返回所有能做出的菜
