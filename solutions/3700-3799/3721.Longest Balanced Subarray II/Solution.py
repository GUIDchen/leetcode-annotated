# 3721. Longest Balanced Subarray II（最长平衡子数组 II）
# 核心思路：把每个不同数值按奇偶性折算成 +1/-1，用支持区间加与区间最值的线段树维护“按不同数值计数”的前缀和，对每个右端点找出最早出现相同前缀和的位置，即得最长平衡子数组。
# 复杂度：时间 O(n log n)（每次区间加/查询 O(log n)），空间 O(n)（4(n+1) 个结点）。

class Solution:  # 题解类
    def longestBalanced(self, nums: List[int]) -> int:  # 求最长平衡子数组的长度
        n = len(nums)  # 取数组长度 n

        class Node:  # 线段树结点类（只存 l、r、mn、mx、lazy 五个字段）
            __slots__ = ("l", "r", "mn", "mx", "lazy")  # 用 __slots__ 固定属性名，省内存、加速属性访问

            def __init__(self):  # 构造函数：所有字段初始化为 0
                self.l = self.r = 0  # 结点管辖的区间端点初始为 0
                self.mn = self.mx = 0  # 区间前缀和的最小值、最大值初始为 0
                self.lazy = 0  # 区间加的懒标记初始为 0

        tr = [Node() for _ in range((n + 1) * 4)]  # 开 4(n+1) 个结点，下标范围是 [0, n]

        def build(u: int, l: int, r: int):  # 递归建树：结点 u 管辖区间 [l, r]
            tr[u].l, tr[u].r = l, r  # 记录结点管辖的左、右端点
            tr[u].mn = tr[u].mx = tr[u].lazy = 0  # 初始前缀和全为 0，最值与懒标记都置 0
            if l == r:  # 到达叶子结点
                return  # 叶子无需继续分裂，直接返回
            mid = (l + r) >> 1  # 取区间中点
            build(u << 1, l, mid)  # 递归建左子树 [l, mid]
            build(u << 1 | 1, mid + 1, r)  # 递归建右子树 [mid+1, r]

        def apply(u: int, v: int):  # 对结点 u 整段加上 v，并同步懒标记
            tr[u].mn += v  # 区间最小值整体加 v
            tr[u].mx += v  # 区间最大值整体加 v
            tr[u].lazy += v  # 懒标记累加 v

        def pushdown(u: int):  # 把结点 u 的懒标记下传给左右子结点
            if tr[u].lazy:  # 只有存在待下传的懒标记时才处理
                apply(u << 1, tr[u].lazy)  # 左子结点继承懒标记
                apply(u << 1 | 1, tr[u].lazy)  # 右子结点继承懒标记
                tr[u].lazy = 0  # 父结点懒标记清零，避免重复下传

        def pushup(u: int):  # 用左右子结点的最值更新父结点
            tr[u].mn = min(tr[u << 1].mn, tr[u << 1 | 1].mn)  # 父结点最小值取两子结点最小值
            tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx)  # 父结点最大值取两子结点最大值

        def modify(u: int, l: int, r: int, v: int):  # 把区间 [l, r] 内的所有前缀和都加上 v
            if tr[u].l >= l and tr[u].r <= r:  # 当前结点区间被目标区间完全覆盖
                apply(u, v)  # 整段打上懒标记并更新最值
                return  # 完全覆盖，无需继续递归，直接返回
            pushdown(u)  # 否则先下传懒标记，保证子结点数据正确
            mid = (tr[u].l + tr[u].r) >> 1  # 取区间中点
            if l <= mid:  # 左子区间与目标区间有交集
                modify(u << 1, l, r, v)  # 递归更新左子树
            if r > mid:  # 右子区间与目标区间有交集
                modify(u << 1 | 1, l, r, v)  # 递归更新右子树
            pushup(u)  # 左右子树更新后回溯合并最值

        def query(u: int, target: int) -> int:  # 在线段树上二分，找最小下标 pos 使前缀和等于 target
            if tr[u].l == tr[u].r:  # 递归到叶子结点，该下标即答案
                return tr[u].l  # 返回叶子对应的下标
            pushdown(u)  # 向下递归前先下传懒标记
            if tr[u << 1].mn <= target <= tr[u << 1].mx:  # 目标值落在左子区间的 [mn, mx] 内，说明左子树中一定存在该值
                return query(u << 1, target)  # 优先往左子树找，保证取到最小下标
            return query(u << 1 | 1, target)  # 左子树不含目标值时只能去右子树

        build(1, 0, n)  # 在 [0, n] 上建树

        last = {}  # 记录每个数值最近一次出现的位置（1 基下标）
        now = ans = 0  # now 为当前前缀和，ans 为最长平衡子数组长度

        for i, x in enumerate(nums, start=1):  # 枚举子数组右端点（1 基下标，与线段树下标对齐）
            det = 1 if (x & 1) else -1  # 该数值的贡献：奇数 +1，偶数 -1
            if x in last:  # 该数值之前出现过，先撤销它在旧位置之后的贡献
                modify(1, last[x], n, -det)  # 区间 [last[x], n] 减去旧贡献，使旧位置之后不再统计该数值
                now -= det  # 当前前缀和同步减去该贡献
            last[x] = i  # 更新该数值最近一次出现的位置
            modify(1, i, n, det)  # 从当前位置 i 开始加上新贡献
            now += det  # 当前前缀和同步加上该贡献
            pos = query(1, now)  # 找到前缀和等于 now 的最早下标 pos
            ans = max(ans, i - pos)  # 用 i-pos 更新答案（子数组 nums[pos..i-1] 平衡）

        return ans  # 返回最长平衡子数组长度
