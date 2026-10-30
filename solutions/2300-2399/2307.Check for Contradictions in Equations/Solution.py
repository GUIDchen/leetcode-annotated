# 题目：2307. 检查方程中的矛盾之处（Check for Contradictions in Equations）
# 思路：带权并查集，每条方程 a/b = v 表示 a 是 b 的 v 倍；合并时由比例推出新根的权值，同集合内比例对不上即为矛盾。
# 时间复杂度：O(n·α(m))，n 为方程数、m 为变量数；空间复杂度：O(m)，父指针与权值列表各一。
class Solution:  # LeetCode 约定的题解类
    def checkContradictions(  # equations 是形如 [a, b] 的方程列表，values 是每条方程 a / b 的比值
        self, equations: List[List[str]], values: List[float]  # 参数续行：题目给定的两个输入
    ) -> bool:  # 返回值为布尔值，表示是否存在矛盾
        def find(x: int) -> int:  # 带权路径压缩的 find：返回 x 的根，并把 w[x] 更新为「x 相对根」的倍数（p、w 在调用时已就绪）
            if p[x] != x:  # 自己不是根，说明还有父节点
                root = find(p[x])  # 先递归找到根，此时 w[p[x]] 已被更新为相对根的倍数
                w[x] *= w[p[x]]  # x 相对根的倍数 = x 相对旧父的倍数 × 旧父相对根的倍数
                p[x] = root  # 路径压缩：让 x 直接挂到根上
            return p[x]  # 返回 x 所在集合的根

        d = defaultdict(int)  # 变量名到编号的映射；defaultdict 保证读取未出现过的键也不报错
        n = 0  # 已分配的变量编号个数
        for e in equations:  # 遍历每条方程
            for s in e:  # 遍历方程里的两个变量名
                if s not in d:  # 变量首次出现时才分配新编号
                    d[s] = n  # 写入编号
                    n += 1  # 编号自增，供下一个新变量使用
        p = list(range(n))  # 并查集父指针：初始 p[i] = i，每个变量各自成集合
        w = [1.0] * n  # 权值数组：w[x] = x / parent[x]，初始各自为根所以都是 1
        eps = 1e-5  # 浮点比较的容差
        for (a, b), v in zip(equations, values):  # 同时取出方程两端以及该方程的比值 v
            a, b = d[a], d[b]  # 把变量名换成编号
            pa, pb = find(a), find(b)  # 求出两个变量所在集合的根
            if pa != pb:  # 两个集合尚未连通，按比例合并
                p[pb] = pa  # 让 b 的根指向 a 的根
                w[pb] = v * w[a] / w[b]  # 由 a/b=v、w[a]=a/pa、w[b]=b/pb 推出 pb/pa = v·w[a]/w[b]
            elif abs(v * w[a] - w[b]) >= eps:  # 已连通时校验现有比例是否与方程一致
                return True  # 比例不符，说明存在矛盾
        return False  # 所有方程都不矛盾
