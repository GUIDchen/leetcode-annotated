# 题目：1722. 执行交换操作后的最小汉明距离（Minimize Hamming Distance After Swap Operations）难度：中等
# 思路：把 allowedSwaps 看成无向边，同一下标连通分量内的元素可以任意换位，因此各分量的多重集合固定。
# 对每个分量先统计 source 中各值的出现次数，再用 target 逐个“消耗”同分量的计数：消耗不到就说明该位置必然失配，答案加一。
# 时间复杂度：O(n·α(n) + m)，并查集近似常数（α 为反阿克曼函数），m 为允许交换对数；空间复杂度：O(n)，并查集与计数表。
class Solution:  # LeetCode 约定的题解类
    def minimumHammingDistance(  # source/target：两个等长数组；allowedSwaps：可交换的下标对
        self, source: List[int], target: List[int], allowedSwaps: List[List[int]]
    ) -> int:  # 返回最小汉明距离（必须失配的位置数）
        def find(x: int) -> int:  # 带路径压缩的并查集查找
            if p[x] != x:  # 当前节点不是根
                p[x] = find(p[x])  # 递归查找并把父指针直接指向根
            return p[x]  # 返回根节点

        n = len(source)  # 数组长度
        p = list(range(n))  # 并查集父节点数组，初始时每个下标自成一个集合
        for a, b in allowedSwaps:  # 遍历每一对允许交换的下标
            p[find(a)] = find(b)  # 合并两个下标所在集合：它们可以自由换位
        cnt = defaultdict(Counter)  # cnt[分量根][数值] = source 中该值的出现次数
        for i, x in enumerate(source):  # 按分量统计 source 的数值频次
            j = find(i)  # i 所属分量的根
            cnt[j][x] += 1  # 把数值 x 计入该分量的计数表
        ans = 0  # 最少汉明距离（必须失配的位置数）
        for i, x in enumerate(target):  # 再按 target 逐个位置核对
            j = find(i)  # i 所属分量的根
            cnt[j][x] -= 1  # 用掉一个与该位置同分量、同值的 source 元素
            ans += cnt[j][x] < 0  # 计数被减成负数则为 True（即 1），说明该位置必然失配
        return ans  # 返回最少失配位置个数
