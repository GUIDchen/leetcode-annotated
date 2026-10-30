# 题目：2709. 最大公约数遍历（Greatest Common Divisor Traversal）
# 思路：把每个下标与它的各个质因子当作图上的节点，共享质因数的下标相互连通；并查集合并后看所有下标是否属于同一个连通块。
# 时间复杂度：O(MX·log MX + n·ω·α)，预处理质因子加并查集；空间复杂度：O(MX·ω + n + m)，质因子表与并查集数组。
class UnionFind:  # 并查集：用于把下标节点与质因子节点连成连通块
    def __init__(self, n):  # 构造 n 个元素，初始各自成一个集合
        self.p = list(range(n))  # 父指针数组，初始 p[i] = i
        self.size = [1] * n  # 每个集合的大小，初始都是 1

    def find(self, x):  # 查找 x 所在集合的根，并做路径压缩
        if self.p[x] != x:  # x 还不是根，需要继续往上找
            self.p[x] = self.find(self.p[x])  # 递归找根，同时让 x 直接指向根
        return self.p[x]  # 返回根节点

    def union(self, a, b):  # 合并两个元素所在集合，返回是否真的发生了合并
        pa, pb = self.find(a), self.find(b)  # 分别取两个元素所在集合的根
        if pa == pb:  # 已经在同一集合，无需合并
            return False  # 返回 False 表示没有合并
        if self.size[pa] > self.size[pb]:  # 按大小合并：把较小的集合挂到较大的集合下
            self.p[pb] = pa  # pb 的父节点改为 pa
            self.size[pa] += self.size[pb]  # 更新大集合的大小
        else:  # 否则把 pa 挂到 pb 下面
            self.p[pa] = pb  # pa 的父节点改为 pb
            self.size[pb] += self.size[pa]  # 更新 pb 所在集合的大小
        return True  # 两个集合成功合并


mx = 100010  # 预处理上限：题目中 nums[i] 最大可达 10^5
p = defaultdict(list)  # p[x] 保存 x 的所有不同质因子
for x in range(1, mx + 1):  # 依次预处理 1..mx 的每个数
    v = x  # v 是试除过程中的剩余部分
    i = 2  # 从最小的质数 2 开始试除
    while i <= v // i:  # 只需试到 sqrt(v)，用整除避免浮点误差
        if v % i == 0:  # i 能整除 v，说明 i 是 v 的一个质因子
            p[x].append(i)  # 记录质因子 i
            while v % i == 0:  # 把 v 中的因子 i 全部除尽
                v //= i  # 除以 i
        i += 1  # 试除下一个候选因子
    if v > 1:  # 除完后剩余的 v 大于 1，它本身也是质因子
        p[x].append(v)  # 记录这个剩余的质因子


class Solution:  # LeetCode 约定的题解类
    def canTraverseAllPairs(self, nums: List[int]) -> bool:  # nums 是待判断的数组
        n = len(nums)  # 数组长度
        m = max(nums)  # 数组最大值，决定质因子节点编号的上界
        uf = UnionFind(n + m + 1)  # 并查集：n 个下标节点 + m 个质因子节点 + 1 个安全余量
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            for j in p[x]:  # 遍历 x 的所有不同质因子 j
                uf.union(i, j + n)  # 把下标 i 与质因子节点 j+n 合并，共享质因数即可互相到达
        return len(set(uf.find(i) for i in range(n))) == 1  # 统计所有下标所在集合的根，只有一个根说明全部连通
