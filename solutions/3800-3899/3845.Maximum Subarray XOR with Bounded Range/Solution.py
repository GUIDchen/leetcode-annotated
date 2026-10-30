# 3845. 最大子数组异或值 / Maximum Subarray XOR with Bounded Range（困难）
# 核心思路：单调队列维护窗口内极差不超过 k 的左端点区间，再用 0-1 字典树配合异或前缀和查询最大异或。
# 复杂度：时间 O(n log U)（U 为值域 2^15），空间 O(n)。
class TrieNode:  # 0-1 字典树节点，用 __slots__ 减少内存开销
    __slots__ = ("children", "count")  # 仅允许这两个实例属性

    def __init__(self):  # 初始化节点
        self.children = [None, None]  # 两个子节点分别代表当前位为 0 / 1
        self.count = 0  # 经过该节点的元素个数，用于删除后判断是否存在


class Solution:  # 题解类（LeetCode 约定类名）
    def maxXor(self, nums: List[int], k: int) -> int:  # 返回元素极差不超过 k 的连续子数组的最大异或值
        root = TrieNode()  # 为本次调用新建字典树根节点

        def update(value: int, delta: int) -> None:  # 把 value 插入（delta=1）或删除（delta=-1）字典树
            cur = root  # 从根节点开始逐位下行
            for bit in range(14, -1, -1):  # 从高位第 14 位到第 0 位遍历
                b = (value >> bit) & 1  # 取出当前位的比特值
                if cur.children[b] is None:  # 该分支还未创建
                    cur.children[b] = TrieNode()  # 新建节点挂到该分支
                cur = cur.children[b]  # 下移到对应子节点
                cur.count += delta  # 途经节点计数同步增减

        def get_max_xor(value: int) -> int:  # 查询字典树中与 value 异或结果最大的值
            cur = root  # 从根节点开始贪心下行
            ans = 0  # 记录能得到的最大异或值
            for bit in range(14, -1, -1):  # 从高位到低位逐位决策
                b = (value >> bit) & 1  # 取出 value 当前位的比特值
                opp = 1 - b  # 反向位，优先走能让异或结果为 1 的分支
                if cur.children[opp] is not None and cur.children[opp].count > 0:  # 反向分支存在且有元素时贪心选取
                    ans |= 1 << bit  # 该位异或结果为 1，置位
                    cur = cur.children[opp]  # 下移到反向子节点
                else:  # 否则只能走同向分支
                    cur = cur.children[b]  # 下移到同向子节点，该位贡献 0
            return ans  # 返回最大异或值

        n = len(nums)  # n 为数组长度
        prefix = [0] * (n + 1)  # prefix[i] 表示 nums 前 i 个元素的异或前缀和
        for i, x in enumerate(nums):  # 预处理异或前缀和
            prefix[i + 1] = prefix[i] ^ x  # 递推得到下一个前缀异或值

        maxq, minq = deque(), deque()  # 单调队列：分别维护窗口内最大值、最小值的下标
        left = 0  # 滑动窗口左端点
        ans = 0  # 答案：满足极差限制的最大异或值
        update(prefix[0], 1)  # 先把 prefix[0] 插入字典树
        for right, x in enumerate(nums):  # right 为滑动窗口右端点
            while maxq and nums[maxq[-1]] <= x:  # 维护递减的最大值队列
                maxq.pop()  # 弹出队尾所有不大于当前值的下标
            while minq and nums[minq[-1]] >= x:  # 维护递增的最小值队列
                minq.pop()  # 弹出队尾所有不小于当前值的下标
            maxq.append(right)  # 当前下标入最大值队列队尾
            minq.append(right)  # 当前下标入最小值队列队尾
            while nums[maxq[0]] - nums[minq[0]] > k:  # 窗口极差超限，收缩左端点直到满足条件
                if maxq[0] == left:  # 队首正是要移出的左端点时同步出队
                    maxq.popleft()  # 最大值队首出队
                if minq[0] == left:  # 最小值队首同样处理
                    minq.popleft()  # 最小值队首出队
                update(prefix[left], -1)  # 左端点移出窗口，从字典树删除对应前缀值
                left += 1  # 窗口左端右移一位
            ans = max(ans, get_max_xor(prefix[right + 1]))  # 用当前前缀值查询最大异或并更新答案
            update(prefix[right + 1], 1)  # 把当前前缀值插入字典树供后续查询
        return ans  # 返回满足极差限制的最大异或值
