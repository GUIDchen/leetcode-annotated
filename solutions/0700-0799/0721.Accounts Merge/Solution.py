# 题目：721. 账户合并（Accounts Merge）
# 思路：以账户下标为元素建并查集，同一邮箱出现在多个账户时合并；再把每个合并组的邮箱去重排序，前面拼上账户名。
# 时间复杂度：O(total * log total)（并查集近线性 + 排序）；空间复杂度：O(total)，total 为邮箱总数。
class UnionFind:  # 并查集类：维护账户之间的合并关系
    def __init__(self, n):  # n：元素个数（账户个数）
        self.p = list(range(n))  # 每个元素初始指向自己
        self.size = [1] * n  # 每个集合初始大小为 1

    def find(self, x):  # 查找 x 所在集合的根
        if self.p[x] != x:  # 不是根，说明还有父节点
            self.p[x] = self.find(self.p[x])  # 路径压缩：递归找到根后把 x 直接挂到根上
        return self.p[x]  # 返回根

    def union(self, a, b):  # 合并 a、b 所在集合
        pa, pb = self.find(a), self.find(b)  # 先求出两个集合的根
        if pa == pb:  # 根相同，本来就在同一集合
            return False  # 无需合并
        if self.size[pa] > self.size[pb]:  # 按大小合并：把小集合挂到大集合上
            self.p[pb] = pa  # b 的根挂到 a 的根下面
            self.size[pa] += self.size[pb]  # 更新集合大小
        else:  # 否则反向挂接
            self.p[pa] = pb  # a 的根挂到 b 的根下面
            self.size[pb] += self.size[pa]  # 更新集合大小
        return True  # 本次确实合并成功


class Solution:  # LeetCode 约定的题解类
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:  # accounts：账户名 + 邮箱列表
        uf = UnionFind(len(accounts))  # 以账户下标为元素的并查集
        d = {}  # 邮箱 → 首次出现它的账户下标
        for i, (_, *emails) in enumerate(accounts):  # 解包出账户名（用 _ 丢弃）与邮箱列表
            for email in emails:  # 遍历该账户的邮箱
                if email in d:  # 邮箱之前出现过，说明两个账户是同一个人
                    uf.union(i, d[email])  # 合并这两个账户
                else:  # 该邮箱第一次出现
                    d[email] = i  # 记录它的归属账户
        g = defaultdict(set)  # 根账户下标 → 该组的邮箱集合（自动去重）
        for i, (_, *emails) in enumerate(accounts):  # 再遍历一次账户，把邮箱按根归组
            root = uf.find(i)  # 找到 i 所属合并组的代表
            g[root].update(emails)  # 把 i 的邮箱并入该组
        return [[accounts[root][0]] + sorted(emails) for root, emails in g.items()]  # 账户名放最前 + 按字典序排序的邮箱
