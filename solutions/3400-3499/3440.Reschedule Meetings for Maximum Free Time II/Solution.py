# 3440. 重新安排会议得到最多空余时间 II / Reschedule Meetings for Maximum Free Time II
# 核心思路：至多平移一场会议；用前缀/后缀最大空闲数组判断该会议能否塞进左侧或右侧空隙，能则其两侧空闲可连成一整段。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义题解类
    def maxFreeTime(  # 方法签名开始（跨行书写）
        self, eventTime: int, startTime: List[int], endTime: List[int]  # 参数：总时长、各会议开始与结束时间
    ) -> int:  # 返回可获得的最大空余时间
        n = len(startTime)  # 会议场数
        pre = [0] * n  # pre[i]：第 0..i 段空闲的最大值
        suf = [0] * n  # suf[i]：第 i..n-1 段空闲的最大值
        pre[0] = startTime[0]  # 首场会议之前的空闲
        suf[n - 1] = eventTime - endTime[-1]  # 最后一场会议之后的空闲
        for i in range(1, n):  # 从左到右维护前缀最大空闲
            pre[i] = max(pre[i - 1], startTime[i] - endTime[i - 1])  # 取前一段前缀与第 i 段间隙的较大者
        for i in range(n - 2, -1, -1):  # 从右到左维护后缀最大空闲
            suf[i] = max(suf[i + 1], startTime[i + 1] - endTime[i])  # 取后一段后缀与第 i 段间隙的较大者
        ans = 0  # 答案初值
        for i in range(n):  # 枚举被平移的会议 i
            l = 0 if i == 0 else endTime[i - 1]  # 会议 i 的左侧边界
            r = eventTime if i == n - 1 else startTime[i + 1]  # 会议 i 的右侧边界
            w = endTime[i] - startTime[i]  # 会议 i 的时长
            ans = max(ans, r - l - w)  # 会议留在原地时，其左右两侧合并的空闲
            if i and pre[i - 1] >= w:  # 左侧存在能放下会议 i 的空隙
                ans = max(ans, r - l)  # 则左右空闲连成整段 r-l
            elif i + 1 < n and suf[i + 1] >= w:  # 否则看右侧是否存在足够空隙
                ans = max(ans, r - l)  # 同样可连成整段 r-l
        return ans  # 返回最大空余时间
