# 题目：947. 移除最多的同行或同列石头（Most Stones Removed with Same Row or Column）
# 思路：把石头看成点，同行或同列即同属一个连通块；用并查集合并，成功合并的次数就是最多能移除的石头数。
# 时间复杂度：O(n^2·α(n))，两两枚举石头；空间复杂度：O(n)，父指针与集合大小数组。
class UnionFind:  # 并查集：判断两块石头是否已经连通
    def __init__(self, n):  # n：元素个数，即石头数量
        self.p = list(range(n))  # 父指针数组，初始每个元素指向自己
        self.size = [1] * n  # 每个集合的大小，初始各为 1

    def find(self, x):  # 查找 x 的根，并做路径压缩
        if self.p[x] != x:  # 还没直接指向根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把路径上的节点直接挂到根上
        return self.p[x]  # 返回根节点

    def union(self, a, b):  # 合并 a、b 所在集合，返回是否真的发生了合并
        pa, pb = self.find(a), self.find(b)  # 先分别求出两个元素的根
        if pa == pb:  # 根相同说明本来就连通，无需合并
            return False  # 没有合并，不计入可移除的石头数
        if self.size[pa] > self.size[pb]:  # 按集合大小合并，小集合挂到大集合下，保持树高接近对数
            self.p[pb] = pa  # 小集合的根指向大集合的根
            self.size[pa] += self.size[pb]  # 更新大集合的元素个数
        else:  # 另一种情况：把 pa 挂到 pb 下面
            self.p[pa] = pb  # pa 成为 pb 的子节点
            self.size[pb] += self.size[pa]  # 更新 pb 集合的元素个数
        return True  # 本次合并成功


class Solution:  # 题解主类
    def removeStones(self, stones: List[List[int]]) -> int:  # stones 里每个元素是 (行, 列) 坐标
        uf = UnionFind(len(stones))  # 每块石头先各自成一个连通块
        ans = 0  # 统计成功合并的次数，即最多可移除的石头数
        for i, (x1, y1) in enumerate(stones):  # 枚举每块石头作为「新加入者」，同时取出它的坐标
            for j, (x2, y2) in enumerate(stones[:i]):  # 只与之前出现过的石头配对，避免重复比较
                if x1 == x2 or y1 == y2:  # 同行或同列才可能互相消去
                    ans += uf.union(i, j)  # 合并成功就多出一条冗余边，可多移除一块石头
        return ans  # 每个连通块最终必剩一块石头，其余都能移除
