# 题目：327. 区间和的个数（Count of Range Sum）
# 思路：前缀和 + 离散化 + 树状数组；对每个右端点统计前面有多少个前缀和 s[j] 满足 lower <= s[i]-s[j] <= upper，即 s[j] ∈ [s[i]-upper, s[i]-lower]。
# 时间复杂度：O(n log n)，排序一次、每次二分与树状数组操作都是 O(log n)；空间复杂度：O(n)，前缀和、离散化数组与树状数组。
class BinaryIndexedTree:    # 树状数组模板：按离散化后的值域统计元素个数
    def __init__(self, n):    # n 是离散化后的值域大小
        self.n = n    # 记录下标上界
        self.c = [0] * (n + 1)    # 树状数组用 1 起下标，所以多开一个位置，c[0] 不用

    def update(self, x, v):    # 在下标 x 处增加 v（这里加 1 表示某个值出现一次）
        while x <= self.n:    # 沿 lowbit 方向向上更新所有覆盖到 x 的位置
            self.c[x] += v    # 该位置计数累加
            x += x & -x    # x & -x 是最低位的 1，加上它跳到下一个覆盖位置

    def query(self, x):    # 求前缀和：统计下标 <= x 的元素个数
        s = 0    # 累加器
        while x > 0:    # 沿 lowbit 方向向下把覆盖区间加起来
            s += self.c[x]    # 累加当前覆盖区间
            x -= x & -x    # 减去 lowbit，跳到前一个区间
        return s    # 返回前缀和


class Solution:    # LeetCode 约定的题解类
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:    # nums：输入数组；lower/upper：区间和的下界与上界，返回满足条件的子数组个数
        s = list(accumulate(nums, initial=0))    # 前缀和：s[i] 是前 i 个元素之和，initial=0 保证 s[0]=0
        arr = sorted(set(v for x in s for v in (x, x - lower, x - upper)))    # 把所有可能用到的取值（s[i]、s[i]-lower、s[i]-upper）去重后排序，做离散化
        tree = BinaryIndexedTree(len(arr))    # 按离散化后的值域建立树状数组
        ans = 0    # 答案：满足条件的子数组个数
        for x in s:    # 依次把每个前缀和当作区间右端点 x
            l = bisect_left(arr, x - upper) + 1    # 历史前缀和需满足 s[j] >= x-upper，二分出它的 1 起下标
            r = bisect_left(arr, x - lower) + 1    # 历史前缀和还需满足 s[j] <= x-lower，二分出右端的 1 起下标
            ans += tree.query(r) - tree.query(l - 1)    # 两次前缀和相减，得到值落在 [l, r] 内的历史前缀和个数
            tree.update(bisect_left(arr, x) + 1, 1)    # 把当前前缀和 x 插入树状数组，供后面的右端点查询
        return ans    # 返回统计结果
