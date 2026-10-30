# 题目：2865. 美丽塔 I（Beautiful Towers I）
# 思路：枚举山顶下标 i，两侧高度都必须沿远离山顶的方向逐格不升，故每步取 y = min(y, maxHeights[j])，把两侧和加上山顶即该方案的总和。
# 时间复杂度：O(n^2)，每个山顶向左右各扫一遍；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def maximumSumOfHeights(self, maxHeights: List[int]) -> int:  # maxHeights 是每座塔的高度上限
        ans, n = 0, len(maxHeights)  # ans 记录最大高度和；n 是塔的数量
        for i, x in enumerate(maxHeights):  # 枚举每座塔作为山顶，x 是它的高度上限
            y = t = x  # y 是向两侧推进时允许的当前高度，t 是当前方案的高度和
            for j in range(i - 1, -1, -1):  # 从山顶向左扫
                y = min(y, maxHeights[j])  # 左塔不能高于右塔，取 min 保持非递增
                t += y  # 把这座塔的高度累加进总和
            y = x  # 右侧重新从山顶高度出发
            for j in range(i + 1, n):  # 从山顶向右扫
                y = min(y, maxHeights[j])  # 右塔不能高于左塔，取 min 保持非递增
                t += y  # 把这座塔的高度累加进总和
            ans = max(ans, t)  # 用当前山顶方案的总和刷新答案
        return ans  # 返回所有方案中的最大高度和
