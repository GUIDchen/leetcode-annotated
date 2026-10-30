# 题目：3279. 活塞占据的最大总区域（Maximum Total Area Occupied by Pistons）
# 思路：每个活塞的位移随时间线性变化，轨迹是三角波；用差分字典记录斜率变化的时刻，再按时刻分段累加总面积取最大。
# 时间复杂度：O(n log n)，需要排序折点；空间复杂度：O(n)，差分表最多 2n 个折点。
class Solution:  # LeetCode 约定的题解类
    def maxArea(self, height: int, positions: List[int], directions: str) -> int:  # height：区域高度；positions/directions：各活塞初始位置与方向
        delta = defaultdict(int)  # 差分表：时刻 -> 到该时刻为止斜率的增量
        diff = res = 0  # diff：当前斜率；res：当前总占据面积（所有活塞位置之和）
        for pos, dir in zip(positions, directions):  # 按顺序遍历每个活塞的初始位置与方向
            res += pos  # 初始时刻的总面积就是所有初始位置之和
            if dir == "U":  # 初始向上运动
                diff += 1  # 初始斜率为 +1：向上运动时总面积随时间增加
                delta[height - pos] -= 2  # 撞到上边界后转为向下，斜率由 +1 变 -1
                delta[height * 2 - pos] += 2  # 从上边界折返再撞下边界后重新向上，斜率由 -1 变 +1
            else:  # 初始向下运动
                diff -= 1  # 初始斜率为 -1：向下运动时总面积随时间减少
                delta[pos] += 2  # 撞到下边界后转为向上，斜率由 -1 变 +1
                delta[height + pos] -= 2  # 再撞到上边界后转为向下，斜率由 +1 变 -1
        ans = res  # 答案先包含初始时刻的总面积
        pre = 0  # 上一个处理过的时刻，初始为 0
        for cur, d in sorted(delta.items()):  # 按时刻从早到晚扫描所有斜率变化点
            res += (cur - pre) * diff  # 用上一段的斜率把总面积线性推进到当前时刻
            pre = cur  # 更新已处理到的时刻
            diff += d  # 叠加当前时刻的斜率变化量，供下一段使用
            ans = max(ans, res)  # 用当前时刻的总面积更新最大值
        return ans  # 返回扫描过程中出现过的最大总面积
