# 3851. 不违反限制的最大请求数 / Maximum Requests Without Violating the Limit（中等）
# 核心思路：按用户分组并把时间升序排序，对每个用户用队列维护最近 window 时间内的保留请求；窗口内已有 k 条时当前请求只能丢弃，最终保留数即答案。
# 复杂度：时间 O(n log n)（每组排序），空间 O(n)。
class Solution:  # 设计一个算法：统计每个用户最多能保留多少请求
    def maxRequests(self, requests: list[list[int]], k: int, window: int) -> int:  # requests[i] = [用户, 时间]，返回不违反限制时最多可保留的请求数
        g = defaultdict(list)  # 按用户分组：key 为用户，value 为该用户所有请求时间
        for u, t in requests:  # 遍历每条请求
            g[u].append(t)  # 把时间挂到对应用户下
        ans = len(requests)  # 答案先按全部保留计，后续每删除一条就减一
        for ts in g.values():  # 每个用户独立判断：用户之间互不影响
            ts.sort()  # 按时间升序排序，便于用滑动窗口检查
            kept = deque()  # deque 充当滑动窗口队列，保存窗口内决定保留的请求时间
            for t in ts:  # 按时间顺序处理该用户的每条请求
                while kept and t - kept[0] > window:  # 窗口左端与当前时间相差超过 window，说明已落在 [t-window, t] 之外
                    kept.popleft()  # 弹出队首这条过期请求
                if len(kept) < k:  # 窗口内保留数还不到 k，可以再保留一条
                    kept.append(t)  # 保留当前请求并推进队尾
                else:  # 窗口内已有 k 条，再加就超过限制
                    ans -= 1  # 只能丢弃当前请求，答案减一
        return ans  # 返回最多可保留的请求数
