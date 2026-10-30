# 题目：1326. 灌溉花园的最少水龙头数目（Minimum Number of Taps to Open to Water a Garden）
# 思路：先预处理每个左端点能覆盖到的最远右端点 last，再像「跳跃游戏 II」那样贪心扫描，一旦覆盖出现断点就返回 -1。
# 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，last 长度为 n+1。
class Solution:  # 题解类
    def minTaps(self, n: int, ranges: List[int]) -> int:  # n：花园的段数（共 n+1 个点）；ranges[i]：第 i 个水龙头的灌溉半径
        last = [0] * (n + 1)  # last[l] 表示从 l 出发能覆盖到的最远右端点
        for i, x in enumerate(ranges):  # 枚举每个水龙头，处理它的覆盖区间
            l, r = max(0, i - x), i + x  # 覆盖区间为 [l, r]，左端点裁到 0
            last[l] = max(last[l], r)  # 同一左端点保留能伸得最远的那个
  # 空行：预处理与贪心扫描分界
        ans = mx = pre = 0  # ans 最少水龙头数；mx 当前最远覆盖；pre 上一段覆盖的右端点
        for i in range(n):  # 从左到右扫描需要浇水的每一段
            mx = max(mx, last[i])  # 更新当前位置能到达的最远点
            if mx <= i:  # 连当前点都覆盖不到，说明出现断点
                return -1  # 无法浇满，返回 -1
            if pre == i:  # 已走到上一段的尽头，需要再开一个水龙头
                ans += 1  # 水龙头计数加一
                pre = mx  # 新一段的覆盖范围扩展到 mx
        return ans  # 返回最少水龙头数
