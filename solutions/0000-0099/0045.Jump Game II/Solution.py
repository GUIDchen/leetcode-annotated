# 题目：45. 跳跃游戏 II（Jump Game II）
# 核心思路：贪心 + 按层跳跃，在当前这跳能覆盖的区间内维护最远可达位置 mx；一旦走到区间右边界就必须再跳一次，并把边界换成 mx。
# 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def jump(self, nums: List[int]) -> int:  # nums 是每个位置的最大跳跃长度，返回跳到末尾的最少步数
        ans = mx = last = 0  # ans 已用跳跃次数；mx 能到达的最远下标；last 当前跳跃区间的右边界
        for i, x in enumerate(nums[:-1]):  # 只遍历到倒数第二个位置，站在最后一位不需要再跳
            mx = max(mx, i + x)  # 用 i + x 尝试刷新能到达的最远位置
            if last == i:  # 走到了当前区间边界，说明这一步的潜力用完了，必须再跳一次
                ans += 1  # 跳跃次数加一
                last = mx  # 下一层右边界扩展成目前能到的最远处，按层扩展即贪心最优
        return ans  # 返回到达末尾的最少跳跃次数
