# 题目：433. 最小基因变化（Minimum Genetic Mutation）
# 思路：把每种基因串视为图的一个顶点，相差恰好一个字符的两串之间有边；用 BFS 按变异次数分层搜索，首次到达 endGene 的层数即最短次数。
# 时间复杂度：O(n² * L)，n 为基因库大小、L 为串长（8）；空间复杂度：O(n)，队列与访问集合。
class Solution:  # LeetCode 约定的题解类
    def minMutation(self, startGene: str, endGene: str, bank: List[str]) -> int:  # 返回把 startGene 变成 endGene 的最少变异次数，无法到达时返回 -1
        q = deque([(startGene, 0)])  # BFS 队列，元素是 (当前基因串, 已经变异的次数)，起点层数为 0
        vis = {startGene}  # 访问集合，起点先标记，避免后续重复入队
        while q:  # 队列非空就继续按层向外扩展
            gene, depth = q.popleft()  # 从队首取出基因串和它所在的层数
            if gene == endGene:  # BFS 第一次到达终点，此时层数一定最小
                return depth  # 直接返回最小变异次数
            for nxt in bank:  # 枚举基因库中的每个串，看能否从当前串一步变异过去
                diff = sum(a != b for a, b in zip(gene, nxt))  # zip 逐位配对，统计字符不同的位置个数
                if diff == 1 and nxt not in vis:  # 恰好只有一处不同（合法变异）且该串尚未访问过
                    q.append((nxt, depth + 1))  # 把新串按层数 +1 入队
                    vis.add(nxt)  # 先标记已访问，避免同一串被重复入队
        return -1  # 队列耗尽仍未到达 endGene，说明不可达
