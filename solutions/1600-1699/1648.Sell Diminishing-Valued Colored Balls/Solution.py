# 题目：1648. 销售价值减少的颜色球（Sell Diminishing-Valued Colored Balls）
# 思路：降序排序后按高度分层卖球，一次把当前最高的一批球削平到次高水平，用等差数列求和批量计价；订单不足以整层削平时再拆出零头。
# 时间复杂度：O(n log n + n)，排序后每轮至少吞并一个不同高度；空间复杂度：O(1)，原地排序加常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, inventory: List[int], orders: int) -> int:  # inventory：每种颜色球的初始数量；orders：要卖出的总球数，返回最大总价值
        inventory.sort(reverse=True)  # 降序排序，方便每次从当前最高的高度整层削平
        mod = 10**9 + 7  # 取模常数
        ans = i = 0  # ans 累加总价值；i 指向当前最高层的下一个下标
        n = len(inventory)  # 颜色种数
        while orders > 0:  # 只要还有订单没卖完就继续分层处理
            while i < n and inventory[i] >= inventory[0]:  # 把与当前最高高度相同的颜色全部并入这一层
                i += 1  # 高度相同的颜色越多，一次能削平的数量越大
            nxt = 0  # nxt 初值 0，表示所有颜色都在同一层时下一层为 0
            if i < n:  # 还有更低的颜色时取它的高度作为下一层
                nxt = inventory[i]  # nxt 记录下一层高度
            cnt = i  # cnt 是当前最高层的颜色种数
            x = inventory[0] - nxt  # x 是这一层最多能降低的高度差
            tot = cnt * x  # tot 是把这层削到 nxt 需要的总球数
            if tot > orders:  # 订单不够削完整的一层，需要拆出零头
                decr = orders // cnt  # 每个颜色平均能降 decr 层
                a1, an = inventory[0] - decr + 1, inventory[0]  # 等差数列的首项 a1 与末项 an（价值随卖出递减）
                ans += (a1 + an) * decr // 2 * cnt  # 整层部分：等差数列求和后乘以颜色种数
                ans += (inventory[0] - decr) * (orders % cnt)  # 零头部分：剩下 orders % cnt 个球按 a1 - 1 的价格卖出
            else:  # 否则订单足够削完整一层
                a1, an = nxt + 1, inventory[0]  # 这一层的价值从 nxt + 1 递减到当前最高价
                ans += (a1 + an) * x // 2 * cnt  # 整层总价值 = 等差数列和 × 颜色种数
                inventory[0] = nxt  # 把最高高度降到 nxt，进入下一层
            orders -= tot  # 扣掉本轮卖出的球数（可能把订单扣成 0 或负数，循环随即结束）
            ans %= mod  # 每轮都对答案取模，避免数值过大
        return ans  # 返回最大总价值（已取模）
