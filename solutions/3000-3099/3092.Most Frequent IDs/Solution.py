# 题目：3092. 最高频率的 ID（Most Frequent IDs）
# 思路：cnt 记录每个 ID 的当前频次，用小根堆存频次的相反数来模拟大根堆；lazy 做延迟删除：更新前把旧频次登记为「待删」，堆顶失效时就弹出。
# 时间复杂度：O(n log n)，每次 heappush/heappop 都是对数级；空间复杂度：O(n)，cnt、lazy 与堆最多各存 O(n) 个元素。
class Solution:  # LeetCode 约定的题解类
    def mostFrequentIDs(self, nums: List[int], freq: List[int]) -> List[int]:  # nums 是 ID 序列，freq 是对应的频次增量
        cnt = Counter()  # ID -> 当前频次（Counter 缺失键默认取 0）
        lazy = Counter()  # 频次值 -> 该值在堆里已失效的次数（延迟删除计数）
        ans = []  # 每次操作后的最大频次
        pq = []  # 堆，存频次的相反数，从而用小根堆模拟大根堆
        for x, f in zip(nums, freq):  # 按顺序同时取出 ID 与频次增量
            lazy[cnt[x]] += 1  # 旧频次即将失效，先登记一次「待删除」
            cnt[x] += f  # 更新该 ID 的真实频次
            heappush(pq, -cnt[x])  # 新频次的相反数入堆，堆顶对应最大频次
            while pq and lazy[-pq[0]] > 0:  # 堆顶若是已失效的旧频次就弹掉
                lazy[-pq[0]] -= 1  # 消耗一次待删除标记
                heappop(pq)  # 弹出失效的堆顶
            ans.append(0 if not pq else -pq[0])  # 堆顶取负即当前最大频次；堆空则为 0
        return ans  # 返回每次操作后的最大频次数组
