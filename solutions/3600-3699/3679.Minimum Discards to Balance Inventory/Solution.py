# 3679. 使库存平衡的最少丢弃次数 / Minimum Discards to Balance Inventory
# 核心思路：维护长度 w 的滑动窗口，用 Counter 统计窗口内每种商品被保留的次数，超上限 m 就丢弃，否则标记保留并计数
# 时间复杂度 O(n)，空间复杂度 O(n)
class Solution:  # 题解类
    def minArrivalsToDiscard(self, arrivals: List[int], w: int, m: int) -> int:  # 返回最少需要丢弃的商品数量
        cnt = Counter()  # cnt[x] 记录当前窗口内商品 x 被保留的次数
        n = len(arrivals)  # 到达序列长度
        marked = [0] * n  # marked[i] 表示第 i 件商品是否被保留（1 保留，0 丢弃）
        ans = 0  # 记录被丢弃的商品数量
        for i, x in enumerate(arrivals):  # 按到达顺序逐件处理
            if i >= w:  # 窗口左端滑出时，撤销那件商品对计数的贡献
                cnt[arrivals[i - w]] -= marked[i - w]  # 只有被保留的商品才需要从计数中扣除
            if cnt[x] >= m:  # 窗口内该商品已达到上限 m
                ans += 1  # 只能丢弃当前这件
            else:  # 否则保留当前这件
                marked[i] = 1  # 打上“保留”标记，便于滑出窗口时撤销
                cnt[x] += 1  # 该商品在窗口内的保留数加一
        return ans  # 返回最少丢弃次数
