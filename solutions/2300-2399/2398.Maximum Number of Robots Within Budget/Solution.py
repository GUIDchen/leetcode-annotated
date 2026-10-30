# 题目：2398. 预算内的最多机器人数目（Maximum Number of Robots Within Budget）
# 思路：滑动窗口 + 单调队列；窗口代价 = 窗口长度 × 运行成本之和 + 窗口内最大充电时间，超预算则移动左端点。
# 时间复杂度：O(n)，每个下标最多入队、出队一次；空间复杂度：O(n)，双端队列最多保存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def maximumRobots(  # 方法签名分多行书写，这里先换行再列参数
        self, chargeTimes: List[int], runningCosts: List[int], budget: int  # chargeTimes 充电时间、runningCosts 运行成本、budget 预算
    ) -> int:  # 返回值为最多机器人数目
        q = deque()  # 单调队列，存窗口内下标；队首是充电时间最大的那个
        ans = s = l = 0  # ans：答案；s：窗口运行成本之和；l：窗口左端点
        for r, (t, c) in enumerate(zip(chargeTimes, runningCosts)):  # 枚举右端点 r，同时取出充电时间 t 与运行成本 c
            s += c  # 把当前机器人的运行成本累加进窗口总和
            while q and chargeTimes[q[-1]] <= t:  # 维护单调递减：比当前 t 小的队尾都无用了，直接弹出
                q.pop()  # 弹出被压过的下标
            q.append(r)  # 当前下标入队，成为新的候选最大值
            while q and (r - l + 1) * s + chargeTimes[q[0]] > budget:  # 代价 = 人数 × 成本之和 + 最大充电时间，超预算就收缩左边界
                if q[0] == l:  # 左端点就是队首的最大值元素
                    q.popleft()  # 它要离开窗口，从队首弹出，露出次大值
                s -= runningCosts[l]  # 从总和中扣掉左端点的运行成本
                l += 1  # 左端点右移一格
            ans = max(ans, r - l + 1)  # 用当前合法窗口长度更新答案
        return ans  # 返回满足预算的最多机器人数目
