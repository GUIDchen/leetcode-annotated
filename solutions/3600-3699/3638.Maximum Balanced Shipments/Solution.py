# 3638. 平衡装运的最大数量 / Maximum Balanced Shipments
# 核心思路：贪心扫描，只要当前重量小于该批已见最大值，就立刻把这一批切出来，批数加一并重新开批
# 时间复杂度 O(n)，空间复杂度 O(1)
#
class Solution:  # 题目要求实现的类
    def maxBalancedShipments(self, weight: List[int]) -> int:  # 返回可划分出的平衡装运批数的最大值
        ans = mx = 0  # ans 记录批数，mx 记录当前批的最大重量
        for x in weight:  # 依次遍历每个重量
            mx = max(mx, x)  # 更新当前批的最大值
            if x < mx:  # 当前重量小于批内最大值，可以切分出这一批
                ans += 1  # 批数加一
                mx = 0  # 重置最大值，开始新的一批
        return ans  # 返回最大批数
