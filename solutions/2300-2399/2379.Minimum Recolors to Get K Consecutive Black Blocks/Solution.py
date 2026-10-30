# 题目：2379. 得到 K 个黑块的最少涂色次数（Minimum Recolors to Get K Consecutive Black Blocks）
# 思路：定长滑窗，统计每个长度为 k 的窗口内 'W' 的个数；把窗口内的 'W' 全涂成 'B' 就得到连续 k 个黑块，故答案为所有窗口中最小的 'W' 数。
# 时间复杂度：O(n)，每个字符只进出窗口一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumRecolors(self, blocks: str, k: int) -> int:  # blocks 为 'B'/'W' 字符串，k 为需要的连续黑块长度
        ans = cnt = blocks[:k].count('W')  # 用首个窗口的 'W' 数同时初始化最优答案 ans 与滑窗计数 cnt
        for i in range(k, len(blocks)):  # 窗口右端从下标 k 开始逐格右移，i 是新进入窗口的位置
            cnt += blocks[i] == 'W'  # 右端新元素若为 'W'，需涂色次数加一
            cnt -= blocks[i - k] == 'W'  # 左端滑出窗口的元素若为 'W'，需涂色次数减一
            ans = min(ans, cnt)  # 用当前窗口的涂色次数更新最小值
        return ans  # 返回最小的涂色次数
