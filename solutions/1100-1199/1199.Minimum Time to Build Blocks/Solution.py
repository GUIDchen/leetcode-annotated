# 题目：1199. 建造街区的最短时间（Minimum Time to Build Blocks）
# 思路：把 blocks 当成小根堆，每次弹出最小的两块，较大的加上 split 放回，最后剩下的就是最短总时间。
# 时间复杂度：O(n log n)，每次 heappop/heappush 为 O(log n)；空间复杂度：O(1)，原地维护堆。
class Solution:  # LeetCode 约定的题解类
    def minBuildTime(self, blocks: List[int], split: int) -> int:  # blocks 是各街区耗时，split 是分裂耗时，返回全部建完的最短时间
        heapify(blocks)  # 原地建小根堆，使每次能以 O(log n) 取出最小耗时
        while len(blocks) > 1:  # 堆里还有两块以上就继续两两合并
            heappop(blocks)  # 弹出较小的一块并丢弃：合并后的总时间由较大的那块决定
            heappush(blocks, heappop(blocks) + split)  # 弹出次小的一块，加上 split 后放回堆（先分裂出一个人再建这一组）
        return blocks[0]  # 堆中只剩一个总耗时，即全部建完的最短时间
