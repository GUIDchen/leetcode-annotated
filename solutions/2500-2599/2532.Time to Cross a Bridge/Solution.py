# 题目：2532. 过桥的时间（Time to Cross a Bridge）
# 核心思路：时间离散模拟。按往返过桥耗时升序排序，等待堆存相反数让下标最大（最慢）者优先出堆，工作堆存 (完成时刻, 下标)；回程优先于去程，无人可过桥时把时钟快进到最早完成时刻。
# 时间复杂度：O(k log k + (n + k) log k)，共 O(n + k) 次过桥、每次常数次堆操作；空间复杂度：O(k)，四个堆最多存 k 个工人。
class Solution:  # LeetCode 约定的题解类
    def findCrossingTime(self, n: int, k: int, time: List[List[int]]) -> int:  # n 为待搬箱子数、k 为工人数；time[i] = [左到右, 捡箱, 右到左, 放箱]，返回搬完全部箱子的时刻
        time.sort(key=lambda x: x[0] + x[2])  # 按往返过桥总耗时升序排序：下标越大代表越慢、越优先
        cur = 0  # 当前模拟时刻
        wait_in_left, wait_in_right = [], []  # 两侧等待过桥的工人下标，堆里存相反数
        work_in_left, work_in_right = [], []  # 两侧正在搬箱子的工人，元素为 (完成时刻, 工人下标)
        for i in range(k):  # 初始时所有工人都在左岸
            heappush(wait_in_left, -i)  # 存 -i，小根堆的堆顶就对应下标最大即最慢的工人
        while 1:  # 持续模拟，唯一出口是右岸彻底空闲时的 return
            while work_in_left:  # 把左岸已经搬完箱子的人转回等待堆
                t, i = work_in_left[0]  # 查看完成时刻最早的工人
                if t > cur:  # 最早的人还没完成
                    break  # 本轮不再转移
                heappop(work_in_left)  # 弹出这件已完成的任务
                heappush(wait_in_left, -i)  # 该工人回到左岸等待过桥，仍以相反数入堆
            while work_in_right:  # 把右岸已经放完箱子的人转回等待堆
                t, i = work_in_right[0]  # 查看右岸完成时刻最早的工人
                if t > cur:  # 还没完成就停止转移
                    break  # 本轮不再转移
                heappop(work_in_right)  # 弹出这件已完成的任务
                heappush(wait_in_right, -i)  # 该工人回到右岸等待回程
            left_to_go = n > 0 and wait_in_left  # 左岸还有箱子且有人在等，才可能出发（这里用的是真值判断）
            right_to_go = bool(wait_in_right)  # 右岸有人等待就应优先回程，显式转成布尔值便于阅读
            if not left_to_go and not right_to_go:  # 两侧都没人能过桥，只能等工人搬完
                nxt = inf  # 用无穷大作为下一时刻的初值
                if work_in_left:  # 左岸还有正在搬箱子的人
                    nxt = min(nxt, work_in_left[0][0])  # 候选时刻：左岸最早完成时间
                if work_in_right:  # 右岸还有正在放箱子的人
                    nxt = min(nxt, work_in_right[0][0])  # 候选时刻：右岸最早完成时间
                cur = nxt  # 时钟直接快进到最早的完成时刻，避免空转
                continue  # 进入下一轮重新处理事件
            if right_to_go:  # 右岸有人等待时，回程优先于去程（题面规定）
                i = -heappop(wait_in_right)  # 取出右岸最慢的工人，并把相反数还原成下标
                cur += time[i][2]  # 时钟推进他「右岸到左岸」的过桥耗时
                if n == 0 and not wait_in_right and not work_in_right:  # 箱子已全部搬完且右岸再无他人
                    return cur  # 全部完成，返回最终时刻
                heappush(work_in_left, (cur + time[i][3], i))  # 他已到左岸开始放箱子，登记完成时刻
            else:  # 否则一定是左岸有人可出发（两侧都无人的情况已被 continue 排除）
                i = -heappop(wait_in_left)  # 取出左岸最慢的工人，并把相反数还原成下标
                cur += time[i][0]  # 时钟推进他「左岸到右岸」的过桥耗时
                n -= 1  # 他从左岸带走一个箱子，待搬数量减一
                heappush(work_in_right, (cur + time[i][1], i))  # 他到右岸开始捡箱子，登记完成时刻
