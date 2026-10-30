# 题目：2940. 找到 Alice 和 Bob 可以相遇的建筑（Find Building Where Alice and Bob Can Meet）
# 思路：把询问按右端点 r 从大到小离线处理，用树状数组维护右侧建筑里「离散化高度 → 最左下标」的前缀最小值。
# 时间复杂度：O((n+m)log n)，排序与树状数组操作各 O(log n)；空间复杂度：O(n+m)，树状数组与答案数组。
class BinaryIndexedTree:  # 树状数组（维护前缀最小值）：记录每个高度桶里出现的最小下标
    __slots__ = ["n", "c"]  # 限定实例属性，省内存并防止手误新增字段

    def __init__(self, n: int):  # n：树状数组容量，合法下标范围是 1..n
        self.n = n  # 保存容量，供 update / query 使用
        self.c = [inf] * (n + 1)  # 下标从 1 开始，用 inf 表示该桶还没有元素

    def update(self, x: int, v: int):  # 单点更新：在位置 x 放入值 v，节点上取较小值
        while x <= self.n:  # 沿 x += lowbit(x) 向上更新所有覆盖该位置的节点
            self.c[x] = min(self.c[x], v)  # 节点保存其覆盖区间内的最小值
            x += x & -x  # lowbit 跳跃到父节点

    def query(self, x: int) -> int:  # 查询前缀 [1, x] 上的最小值
        mi = inf  # 用哨兵初始化，保证 min 从「无元素」开始
        while x:  # 沿 x -= lowbit(x) 向前缀方向跳跃，x 为 0 时结束
            mi = min(mi, self.c[x])  # 合并当前节点覆盖的区间
            x -= x & -x  # 跳到左前方节点
        return -1 if mi == inf else mi  # 没查到返回 -1（没有可行建筑），否则返回最左下标


class Solution:  # LeetCode 约定的题解类
    def leftmostBuildingQueries(  # 处理所有询问，返回最靠左的相遇建筑下标
        self, heights: List[int], queries: List[List[int]]  # heights：每栋建筑的高度；queries：每条询问形如 [alice, bob] 两个下标
    ) -> List[int]:  # 返回值为每个询问的答案
        n, m = len(heights), len(queries)  # n：建筑数量；m：询问数量
        for i in range(m):  # 遍历每个询问，把两个下标统一成「左端点 <= 右端点」
            queries[i] = [min(queries[i]), max(queries[i])]  # 用 min/max 重排两个下标
        j = n - 1  # j：从右往左的扫描指针，指向还没加入树状数组的建筑
        s = sorted(set(heights))  # 所有出现过的不同高度值，用于离散化
        ans = [-1] * m  # 答案数组，先全部填 -1，随后逐个覆盖
        tree = BinaryIndexedTree(n)  # 树状数组容量取 n，足以容纳离散化后的所有编号
        for i in sorted(range(m), key=lambda i: -queries[i][1]):  # 按右端点从大到小依次回答询问
            l, r = queries[i]  # l、r：当前询问的两个建筑下标，满足 l <= r
            while j > r:  # 把下标大于 r 的建筑全部加入树状数组
                k = n - bisect_left(s, heights[j]) + 1  # 用 n 作常数偏移，等价于从 s 末尾往前数；+1 让编号从 1 开始
                tree.update(k, j)  # 把建筑 j 的下标记到对应高度桶（同桶取最小下标）
                j -= 1  # 指针左移，保证每栋建筑只加入一次
            if l == r or heights[l] < heights[r]:  # 两人同楼，或 Bob 所在楼已经更高
                ans[i] = r  # 答案就是 r
            else:  # 否则要在 r 右侧找严格高于 heights[l] 的建筑
                k = n - bisect_left(s, heights[l])  # 上面 +1 的偏移让这个上界恰好排除等高建筑
                ans[i] = tree.query(k)  # 前缀最小值即最靠左的可行建筑下标（没有则为 -1）
        return ans  # 返回所有询问的答案
