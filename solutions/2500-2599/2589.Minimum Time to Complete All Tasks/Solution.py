# 题目：2589. 完成所有任务的最少时间（Minimum Time to Complete All Tasks）
# 思路：按截止时间升序排序，先抵扣时间窗内已占用的时刻，再从窗口最右端往左补齐剩余时长（越靠后越利于后续任务）。
# 时间复杂度：O(n * maxEnd)，每个任务只扫描自己的时间窗；空间复杂度：O(maxEnd)，vis 数组固定 2010 个元素。
class Solution:  # LeetCode 约定的题解类
    def findMinimumTime(self, tasks: List[List[int]]) -> int:  # tasks 的每个元素是 [start, end, duration]
        tasks.sort(key=lambda x: x[1])  # 按截止时刻 x[1] 升序排序，先安排结束得早的任务
        vis = [0] * 2010  # vis[i] 标记第 i 个时刻是否已被占用（题目时刻上界约 2000）
        ans = 0  # 累计被占用的时刻数，即最少需要的时间
        for start, end, duration in tasks:  # 依次处理每个任务并解包出窗口左右端与时长
            duration -= sum(vis[start : end + 1])  # 窗口内已被占用的时刻可以抵扣本任务的部分时长
            i = end  # 从窗口最右端开始找空闲时刻
            while i >= start and duration > 0:  # 只要还在窗口内且仍有剩余时长就继续
                if not vis[i]:  # 该时刻尚未被占用
                    duration -= 1  # 占用一个时刻，剩余时长减一
                    vis[i] = 1  # 把该时刻标记为已占用
                    ans += 1  # 答案计数加一
                i -= 1  # 指针左移，尝试更靠前的时刻
        return ans  # 返回最少需要占用的时刻总数
