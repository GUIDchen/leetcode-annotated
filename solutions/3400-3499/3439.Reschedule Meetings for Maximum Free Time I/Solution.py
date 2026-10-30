# 3439. 重新安排会议得到最多空余时间 I / Reschedule Meetings for Maximum Free Time I
# 核心思路：把空闲时长抽成 n+1 段数组，连续 k+1 段空闲可用平移 k 场会议合并成一段，故用定长滑动窗口求最大和。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义题解类
    def maxFreeTime(  # 方法签名开始（跨行书写）
        self, eventTime: int, k: int, startTime: List[int], endTime: List[int]  # 参数：总时长、最多平移的会议数、各会议开始与结束时间
    ) -> int:  # 返回可获得的最大空余时间
        nums = [startTime[0]]  # nums 收集所有空闲时长，先放首场会议之前的空闲
        for i in range(1, len(endTime)):  # 枚举相邻会议之间的间隙
            nums.append(startTime[i] - endTime[i - 1])  # 上一场结束到本场开始的空闲
        nums.append(eventTime - endTime[-1])  # 最后一场会议之后的空闲
        ans = s = 0  # ans 为答案，s 为当前窗口内的空闲和
        for i, x in enumerate(nums):  # 滑动窗口遍历所有空闲段
            s += x  # 右端元素加入窗口
            if i >= k:  # 窗口长度达到 k+1，说明这 k 场会议可被平移合并
                ans = max(ans, s)  # 用窗口和更新答案
                s -= nums[i - k]  # 左端元素移出窗口
        return ans  # 返回最大空余时间
