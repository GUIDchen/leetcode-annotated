# 题目：3072. 将元素分配到两个数组中 II（Distribute Elements Into Two Arrays II）
# 核心思路：需要动态查询「某数组中有多少个数严格大于 x」，于是先把 nums 去重排序做离散化，再用两棵树状数组分别维护两个数组的值域计数，按规则比较两份计数结果决定元素去向。
# 时间复杂度：O(n·log n)，离散化排序 O(n·log n) 加每次 O(log n) 的树状数组操作；空间复杂度：O(n)，离散化列表、两棵树状数组与结果数组。
class BinaryIndexedTree:  # 手写树状数组（Binary Indexed Tree / Fenwick 树），支持单点加与前缀和查询
    __slots__ = "n", "c"  # 用 __slots__ 固定实例属性，省掉属性字典开销，同时禁止误加新属性

    def __init__(self, n: int):  # 构造函数：n 为离散化后的值域大小
        self.n = n  # 记录值域大小，树状数组维护 1..n 这些下标
        self.c = [0] * (n + 1)  # 内部数组开到 n+1，下标 0 空置不用，便于 1 基下标运算

    def update(self, x: int, delta: int) -> None:  # 在位置 x 上加 delta（本题 delta 恒为 1，即计数加一）
        while x <= self.n:  # 沿 lowbit 向上更新：x += x & -x 跳到下一个覆盖 x 的节点
            self.c[x] += delta  # 把增量累加到当前节点
            x += x & -x  # x += x & -x 已经推进到下一个节点，循环继续

    def query(self, x: int) -> int:  # 查询前缀和：返回下标 1..x 上的计数总和，即「值不大于 x 的元素个数」
        s = 0  # 累加器
        while x:  # x 大于 0 时继续回退
            s += self.c[x]  # 累加这一段的计数
            x -= x & -x  # x -= x & -x：跳过刚统计过的整段区间
        return s  # 返回前缀和


class Solution:  # 题解类：用两棵动态计数树模拟两数组的分配过程
    def resultArray(self, nums: List[int]) -> List[int]:  # nums：输入数组；返回按规则分配后拼接得到的数组
        st = sorted(set(nums))  # 去重并排序，得到升序的值域列表，用于离散化
        m = len(st)  # m 为不同取值的个数，也就是树状数组要维护的值域大小
        tree1 = BinaryIndexedTree(m + 1)  # arr1 对应的树状数组：维护 arr1 中各取值的出现次数
        tree2 = BinaryIndexedTree(m + 1)  # arr2 对应的树状数组
        tree1.update(bisect_left(st, nums[0]) + 1, 1)  # bisect_left 得到 0 基排名，加一变成 1 基下标，计数加一
        tree2.update(bisect_left(st, nums[1]) + 1, 1)  # 同理把 nums[1] 的排名在 tree2 中计数加一
        arr1 = [nums[0]]  # arr1 以第一个元素起步
        arr2 = [nums[1]]  # arr2 以第二个元素起步
        for x in nums[2:]:  # 从下标 2 开始依次分配剩余元素
            i = bisect_left(st, x) + 1  # 求出当前元素的离散化排名（1 基下标）
            a = len(arr1) - tree1.query(i)  # len(arr1) - query(i) 就是 arr1 中严格大于当前值的元素个数（query 统计的是不大于当前值的个数）
            b = len(arr2) - tree2.query(i)  # 同理得到 arr2 中严格大于当前值的元素个数
            if a > b:  # arr1 中更大元素更多，就放进 arr1
                arr1.append(x)  # 追加到 arr1 末尾
                tree1.update(i, 1)  # 同步更新 tree1 计数，保证后续查询正确
            elif a < b:  # arr2 中更大元素更多，则放进 arr2
                arr2.append(x)  # 追加到 arr2 末尾
                tree2.update(i, 1)  # 同步更新 tree2 计数
            elif len(arr1) <= len(arr2):  # 两者数量相等时，按规则优先放进元素更少的数组；长度也相等则放进 arr1
                arr1.append(x)  # 追加到 arr1 末尾
                tree1.update(i, 1)  # 同步更新 tree1 计数
            else:  # 否则 arr1 元素更多，放进 arr2
                arr2.append(x)  # 追加到 arr2 末尾
                tree2.update(i, 1)  # 同步更新 tree2 计数
        return arr1 + arr2  # 两个列表顺序拼接：arr1 在前、arr2 在后
