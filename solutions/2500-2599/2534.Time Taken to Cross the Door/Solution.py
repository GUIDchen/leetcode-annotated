# 题目：2534. 通过门的时间（Time Taken to Cross the Door）
# 核心思路：两个方向各用一个双端队列 + 时间模拟。按到达时刻把人们按方向入队；两侧都有人时沿用上一次的放行方向（同一侧会连续通过直到该侧无人），只有一侧有人就放行该侧，都无人则时钟空转。
# 时间复杂度：O(n)，每人入队、出队各一次；空间复杂度：O(n)，两个队列与长度 n 的答案数组。
class Solution:  # LeetCode 约定的题解类
    def timeTaken(self, arrival: List[int], state: List[int]) -> List[int]:  # arrival[i] 是第 i 人的到达时刻，state[i] 是他的方向（0 或 1），返回每个人过门的时刻
        q = [deque(), deque()]  # 两个队列：q[0]、q[1] 分别按方向存放排队者的下标
        n = len(arrival)  # 总人数
        t = i = 0  # t 是当前时刻，i 是下一个尚未到达的人
        st = 1  # 上一次放行的方向，初始按题意取 1
        ans = [0] * n  # 记录每个人的过门时刻
        while i < n or q[0] or q[1]:  # 还有人没到达或还有人没进门就继续模拟
            while i < n and arrival[i] <= t:  # 把当前时刻及之前已到达的人全部入队
                q[state[i]].append(i)  # 按方向塞进对应队列的队尾
                i += 1  # 指向下一个尚未到达的人
            if q[0] and q[1]:  # 两侧都有人排队，就沿用上一次的放行方向
                ans[q[st].popleft()] = t  # 该方向队首出队，他的过门时刻就是当前 t
            elif q[0] or q[1]:  # 只有一侧有人，只能放行这一侧
                st = 0 if q[0] else 1  # 把「上次放行方向」更新为实际放行的那一侧
                ans[q[st].popleft()] = t  # 该侧队首出队并记录过门时刻
            else:  # 两侧都没人排队，门只能空转
                st = 1  # 没有可放行的人，把放行方向复位，等下一批到达者决定
            t += 1  # 门每单位时间最多通过一人，时刻前进一秒
        return ans  # 返回每个人的过门时刻数组
