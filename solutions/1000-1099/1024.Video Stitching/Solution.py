# 题目：1024. 视频拼接（Video Stitching）
# 思路：先用 last[a] 记录从时刻 a 出发能到达的最远时刻，再沿时间轴贪心扫描，维护「已覆盖最远点 mx」与「当前片段起点 pre」，必要时再切一刀。
# 时间复杂度：O(n + time)，n 为片段数；空间复杂度：O(time)，last 数组长度为 time。
class Solution:  # LeetCode 约定的题解类
    def videoStitching(self, clips: List[List[int]], time: int) -> int:  # clips：片段列表，每个元素是 [起点, 终点]；time：需要覆盖的区间右端；返回最少片段数，覆盖不了返回 -1
        last = [0] * time  # last[a] 表示所有从 a 开始的片段里能延伸到的最远时刻
        for a, b in clips:  # 遍历每个片段，按起点归档最远终点
            if a < time:  # 起点 >= time 的片段对覆盖 [0, time] 没有帮助，忽略它（也避免数组越界）
                last[a] = max(last[a], b)  # 同一时刻可能有多个片段，只保留延伸得最远的那一个
        # 贪心状态：ans 已用片段数，mx 当前能覆盖到的最远时刻，pre 当前片段生效的起点
        ans = mx = pre = 0  # 三个变量同时初始化为 0
        for i, v in enumerate(last):  # 沿时间轴逐点前进，i 是当前时刻、v 是从 i 出发能到的最远时刻
            mx = max(mx, v)  # 更新当前能覆盖到的最远时刻
            if mx <= i:  # 最远只到 i，说明 i 之后断档，区间拼不出来
                return -1  # 无法完成拼接
            if pre == i:  # 走到了当前片段的尽头，必须再取一个新的片段
                ans += 1  # 片段数加一
                pre = mx  # 新片段从这里开始生效，覆盖范围推进到 mx
        # 时间轴扫描完毕，ans 就是覆盖 [0, time] 的最少片段数
        return ans  # 返回最少片段数
