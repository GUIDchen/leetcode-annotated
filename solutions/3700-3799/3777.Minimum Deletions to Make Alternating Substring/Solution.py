# 3777. 使子字符串变交替的最少删除次数 / Minimum Deletions to Make Alternating Substring
# 核心思路：把 s[i]==s[i-1] 的位置标记为 1，区间 [l,r] 的冲突数就是这些标记的区间和；用树状数组支持单点修改与前缀和，翻转一个字符只需改动它与后一位两个标记。
# 复杂度：时间复杂度 O((n+q) log n)，空间复杂度 O(n)，其中 n 为字符串长度，q 为操作次数。
class BinaryIndexedTree:  # 树状数组：支持单点修改与前缀和查询
    __slots__ = "n", "c"  # 限制实例属性以节省内存

    def __init__(self, n: int):  # 构造函数，n 为下标上界
        self.n = n  # 记录下标范围
        self.c = [0] * (n + 1)  # 数组开 n+1 个并全部置 0

    def update(self, x: int, delta: int) -> None:  # 在下标 x 处加上 delta
        while x <= self.n:  # 沿 lowbit 向上更新
            self.c[x] += delta  # 更新当前节点
            x += x & -x  # 跳到父节点

    def query(self, x: int) -> int:  # 查询前缀和 [1, x]
        s = 0  # 累计结果
        while x:  # 沿 lowbit 向下累加
            s += self.c[x]  # 累加当前节点
            x -= x & -x  # 跳到前一个覆盖块
        return s  # 返回前缀和


class Solution:  # 定义题解类
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:  # 返回每次查询区间子串变成交替所需的最少删除次数
        n = len(s)  # 字符串长度
        nums = [0] * n  # nums[i] 标记 s[i] 是否与 s[i-1] 相同
        bit = BinaryIndexedTree(n)  # 用树状数组维护 nums 的前缀和
        for i in range(1, n):  # 从第二个字符开始标记相邻相等的位置
            nums[i] = int(s[i] == s[i - 1])  # 相邻字符相同则标记为 1
            if nums[i]:  # 该位置构成一个需要删除的冲突
                bit.update(i + 1, 1)  # 在树状数组的 i+1 处加一
        ans = []  # 保存每次查询的答案
        for q in queries:  # 依次处理每个操作
            if q[0] == 1:  # 类型 1：翻转 s[q[1]] 处的字符
                j = q[1]  # 被翻转位置的下标
                delta = (nums[j] ^ 1) - nums[j]  # 计算 nums[j] 翻转后的变化量
                nums[j] ^= 1  # 翻转 nums[j]
                bit.update(j + 1, delta)  # 把变化量写回树状数组
                if j + 1 < n:  # 下一位置是否为冲突也会随之改变
                    delta = (nums[j + 1] ^ 1) - nums[j + 1]  # 计算 nums[j+1] 翻转后的变化量
                    nums[j + 1] ^= 1  # 翻转 nums[j+1]
                    bit.update(j + 2, delta)  # 把变化量写回树状数组
            else:  # 类型 2：查询区间 [l, r] 内的冲突数
                _, l, r = q  # 拆出区间左右端点
                ans.append(bit.query(r + 1) - bit.query(l + 1))  # 前缀和相减得到区间冲突数
        return ans  # 返回全部查询结果
