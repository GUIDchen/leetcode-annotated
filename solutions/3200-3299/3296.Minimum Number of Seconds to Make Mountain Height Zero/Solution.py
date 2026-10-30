# 题目：3296. 移山所需的最少秒数（Minimum Number of Seconds to Make Mountain Height Zero）
# 思路：可行性对时间单调，用 bisect_left 在 0..1e16 上二分秒数；判定时由 wt*k(k+1)/2 <= t 解出每个工人能削的块数并求和。
# 时间复杂度：O(n log(1e16))，n 为工人数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minNumberOfSeconds(self, mountainHeight: int, workerTimes: List[int]) -> int:  # mountainHeight 是总高度，workerTimes 是每个工人削第 1 块所需的时间倍数
        def check(t: int) -> bool:  # 判定函数：限时 t 秒时所有工人最多能削掉多少高度
            h = 0  # 累计可削掉的总高度
            for wt in workerTimes:  # 枚举每个工人
                h += int(sqrt(2 * t / wt + 1 / 4) - 1 / 2)  # 解不等式 wt*k(k+1)/2 <= t 得 k，取整后即为该工人能削的块数
            return h >= mountainHeight  # 总高度够就说明 t 秒可行

        return bisect_left(range(10**16), True, key=check)  # range 提供升序候选时间，key=check 让 bisect_left 找到第一个可行的秒数
