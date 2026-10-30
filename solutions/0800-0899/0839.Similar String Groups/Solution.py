# 题目：839. 相似字符串组（Similar String Groups）
# 思路：两个变位词若能通过至多一次交换（等价于恰好 0 或 2 个位置不同）互相转换就相似，相似关系可传递，于是用并查集把所有相似串合并，最终集合数就是组数。
# 时间复杂度：O(n^2·m·α(n))，两两比较字符串并做并查集合并；空间复杂度：O(n)，并查集的父指针与大小数组。
class UnionFind:  # 并查集模板：维护连通分量，用来把相似的字符串合并成一组
    def __init__(self, n):  # 构造函数：n 个元素一开始各自独立
        self.p = list(range(n))  # 每个元素的父结点初始为自己
        self.size = [1] * n  # 每棵树的大小初始都为 1，用于按大小合并

    def find(self, x):  # 查找 x 所在集合的根，同时做路径压缩
        if self.p[x] != x:  # x 不是根，说明还有父结点
            self.p[x] = self.find(self.p[x])  # 递归查根，并把 x 直接挂到根上，压缩后续查询路径
        return self.p[x]  # 返回 x 所在集合的根

    def union(self, a, b):  # 合并 a、b 所在集合，返回本次是否真的发生了合并
        pa, pb = self.find(a), self.find(b)  # 先找到两个元素所在集合的根
        if pa == pb:  # 根相同说明本来就在同一集合
            return False  # 无需合并，返回 False
        if self.size[pa] > self.size[pb]:  # 按大小合并：把小的树挂到大的树上，保证树高为对数级
            self.p[pb] = pa  # 小树根 pb 的父改为大树根 pa
            self.size[pa] += self.size[pb]  # 大树的大小累加小树的大小
        else:  # 对称情况：pa 所在树更小或相等
            self.p[pa] = pb  # 小树根 pa 的父改为大树根 pb
            self.size[pb] += self.size[pa]  # 大树的大小累加小树的大小
        return True  # 合并成功，返回 True


class Solution:  # LeetCode 约定的题解类
    def numSimilarGroups(self, strs: List[str]) -> int:  # strs 是一组互为变位词的字符串，返回相似字符串的组数
        n, m = len(strs), len(strs[0])  # 字符串个数与每个字符串的长度
        uf = UnionFind(n)  # 为每个字符串建立一个并查集元素
        for i, s in enumerate(strs):  # 枚举第一个字符串及其下标
            for j, t in enumerate(strs[:i]):  # 只与它前面的字符串比较，避免同一对被检查两次
                if sum(s[k] != t[k] for k in range(m)) <= 2 and uf.union(i, j):  # 变位词的差异个数只能是 0 或 ≥2，故 ≤2 即相似；合并成功才说明组数减少
                    n -= 1  # 两个集合合并成功，组数减一
        return n  # 返回最终组数
