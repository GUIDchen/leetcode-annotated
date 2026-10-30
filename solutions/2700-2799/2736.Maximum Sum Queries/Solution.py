# 题目：2736. 最大和查询（Maximum Sum Queries）
# 思路：询问按 x 降序离线处理，把 nums1 >= x 的元素按 nums2 秩插入树状数组维护前缀最大 value，再查询 nums2 >= y 那一侧的前缀最大值。
# 时间复杂度：O((n+m)log n)，排序加每元素 log n 次更新/查询；空间复杂度：O(n+m)，树状数组 O(n) 加索引与答案数组 O(m)。
class BinaryIndexedTree:  # 树状数组（下标从 1 开始），维护前缀最大值
    __slots__ = ["n", "c"]  # 用 __slots__ 限定实例属性，减少内存开销并加快属性访问

    def __init__(self, n: int):  # 构造函数：共 n 个可更新的位置
        self.n = n  # 保存长度，update/query 都要用到
        self.c = [-1] * (n + 1)  # 多开一位让下标从 1 开始，全部初始化为 -1 表示该位置还没有元素

    def update(self, x: int, v: int):  # 单点更新：把位置 x 的值变为 max(原值, v)，并向上更新覆盖它的节点
        while x <= self.n:  # 沿 lowbit 链向上跳，覆盖所有包含位置 x 的区间
            self.c[x] = max(self.c[x], v)  # 只求最大值且插入顺序无要求，直接取 max 即可
            x += x & -x  # lowbit 技巧：x & -x 是 x 最低位的 1，加上它跳到上层负责节点

    def query(self, x: int) -> int:  # 查询前缀 [1, x] 的最大值
        mx = -1  # 前缀最大值初值取 -1，表示该前缀范围内没有元素
        while x:  # 等价于 x > 0：沿 lowbit 链向下拆出前缀区间块
            mx = max(mx, self.c[x])  # 合并当前块的最大值
            x -= x & -x  # 减去 lowbit，跳到下一个更小的前缀块
        return mx  # 返回前缀 [1, x] 的最大值


class Solution:  # LeetCode 约定的题解类
    def maximumSumQueries(  # nums1/nums2 是等长数组，queries 里的 (x, y) 要求 nums1[i]>=x 且 nums2[i]>=y 时 nums1[i]+nums2[i] 的最大值
        self, nums1: List[int], nums2: List[int], queries: List[List[int]]  # 多行参数列表：依次是两个输入数组与询问列表
    ) -> List[int]:  # 返回每个询问对应的最大和，无解处为 -1
        nums = sorted(zip(nums1, nums2), key=lambda x: -x[0])  # 按 nums1 降序打包成 (nums1, nums2) 对，方便边扫描边插入
        nums2.sort()  # 把 nums2 升序排序，用于把它的取值离散化成树状数组下标
        n, m = len(nums1), len(queries)  # n：元素个数；m：询问个数
        ans = [-1] * m  # 答案数组先全部置 -1，表示暂时无解
        j = 0  # 扫描指针：指向下一个待插入树状数组的元素
        tree = BinaryIndexedTree(n)  # 建一棵以离散化 nums2 秩为下标的树状数组
        for i in sorted(range(m), key=lambda i: -queries[i][0]):  # 询问按 x 从大到小离线处理，已插入的元素集合只增不减
            x, y = queries[i]  # 取出当前询问的两个阈值
            while j < n and nums[j][0] >= x:  # 把所有 nums1 >= x 的元素依次插入树状数组
                k = n - bisect_left(nums2, nums[j][1])  # 把 nums2 由小到大的名次翻转成由大到小，使 nums2 >= y 对应前缀 [1, k]
                tree.update(k, nums[j][0] + nums[j][1])  # 插入这对元素的 value = nums1 + nums2
                j += 1  # 指针后移，处理下一个元素
            k = n - bisect_left(nums2, y)  # 求阈值 y 对应的秩，nums2 >= y 的元素恰好落在前缀 [1, k] 内
            ans[i] = tree.query(k)  # 查询前缀最大值回填到原询问下标，查不到时得到 -1
        return ans  # 按原顺序返回全部答案
