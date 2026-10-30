# 题目：3181. 执行操作可获得的最大总奖励 II（Maximum Total Reward Using Operations II）
# 思路：用一个大整数当位图，第 s 位为 1 表示总和 s 可达；对每个奖励值 v，只把小于 v 的可达和整体加 v，最后取最高可达位。
# 时间复杂度：O(n * maxV / 64)，大整数移位由字并行完成；空间复杂度：O(maxV)，一个位图整数。
class Solution:  # LeetCode 约定的题解类
    def maxTotalReward(self, rewardValues: List[int]) -> int:  # rewardValues：可选的奖励值集合
        nums = sorted(set(rewardValues))  # 排序并去重：重复的奖励值不可能被选两次
        f = 1  # 位图 f，第 s 位为 1 表示总和 s 可达，初始只把 0 标记为可达
        for v in nums:  # 逐个把奖励值当作可选操作
            f |= (f & ((1 << v) - 1)) << v  # 只取小于 v 的低位、左移 v 位后并入：等价于给这些可达和都加上 v
        return f.bit_length() - 1  # bit_length 减 1 即最高位的下标，也就是最大可达总奖励
