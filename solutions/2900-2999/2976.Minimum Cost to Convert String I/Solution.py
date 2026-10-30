# 题目：2976. 转换字符串的最小成本 I（Minimum Cost to Convert String I）
# 思路：26 个字母当结点、转换规则当带权有向边，Floyd 求任意两字母的最小转换成本，再逐位累加 source→target 的代价，不可达返回 -1。
# 时间复杂度：O(26^3 + n)，n 为字符串长度；空间复杂度：O(26^2)，一个 26x26 的矩阵。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # minimumCost：求把 source 变成 target 的最小总成本
        self,  # self 为实例本身
        source: str,  # 原串
        target: str,  # 目标串
        original: List[str],  # 每条转换规则的起点字母
        changed: List[str],  # 每条转换规则的终点字母
        cost: List[int],  # 与规则一一对应的成本
    ) -> int:  # 参数列表结束，返回 int
        g = [[inf] * 26 for _ in range(26)]  # 26x26 邻接矩阵，初值 inf 表示不可达
        for i in range(26):  # 逐个字母初始化对角线
            g[i][i] = 0  # 自身转到自身成本为 0，避免被 inf 覆盖
        for x, y, z in zip(original, changed, cost):  # 逐条读取转换规则
            x = ord(x) - ord('a')  # 起点字母映射到 0..25
            y = ord(y) - ord('a')  # 终点字母映射到 0..25
            g[x][y] = min(g[x][y], z)  # 同一对字母可能有多条规则，保留最便宜的一条
        for k in range(26):  # Floyd 的中间点 k
            for i in range(26):  # 起点 i
                for j in range(26):  # 终点 j
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j])  # 松弛：允许借助 k 间接转换
        ans = 0  # 累计总成本
        for a, b in zip(source, target):  # 逐位比较两个串
            if a != b:  # 该位字母不同才需要转换
                x, y = ord(a) - ord('a'), ord(b) - ord('a')  # 把两个字母都映射到 0..25
                if g[x][y] >= inf:  # 该转换不可达
                    return -1  # 无法完成转换，返回 -1
                ans += g[x][y]  # 累加该位的最小转换成本
        return ans  # 返回总成本
