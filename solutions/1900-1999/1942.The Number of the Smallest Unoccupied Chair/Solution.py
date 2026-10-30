# 题目：1942. 最小未被占据椅子的编号（The Number of the Smallest Unoccupied Chair）
# 思路：按到达时间排序，用 idle 小根堆维护空闲椅子、busy 小根堆按离开时间维护占用情况；每次到达先回收已离开者的椅子，再弹出编号最小的空闲椅子。
# 时间复杂度：O(n log n)，排序 + 堆操作；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def smallestChair(self, times: List[List[int]], targetFriend: int) -> int:  # times：每位朋友的 (到达, 离开) 时刻；targetFriend：目标朋友的下标
        n = len(times)  # n 是朋友数，也等于椅子数
        for i in range(n):  # 给每个人补上原始下标
            times[i].append(i)  # 把下标追加到时间列表末尾，排序后仍能对应到具体的人
        times.sort()  # 按到达时间升序排序
        idle = list(range(n))  # idle 堆：初始空闲椅子编号 0..n-1
        heapify(idle)  # heapify 原地整理成小根堆，堆顶是最小空闲编号
        busy = []  # busy 堆：(离开时间, 椅子编号)，离开最早的在堆顶
        for arrival, leaving, i in times:  # 按到达时间从早到晚依次安排每位朋友
            while busy and busy[0][0] <= arrival:  # 回收所有在本次到达时已经离开的椅子
                heappush(idle, heappop(busy)[1])  # heappop(busy)[1] 取出离开者的椅子编号，heappush 归还到空闲堆
            j = heappop(idle)  # 弹出编号最小的空闲椅子（弹出即视为占用）
            if i == targetFriend:  # 当前处理的正是目标朋友
                return j  # 返回他坐到的椅子编号
            heappush(busy, (leaving, j))  # 否则登记这把椅子的释放时刻，等时刻到了再还回空闲堆
