# 题目：2931. 购买物品的最大开销（Maximum Spending After Buying Items）
# 思路：每行价格从左到右递增，用最小堆做多路归并，每次弹出全局最小值；它是第 d 件被买的物品，故贡献 价格 * d。
# 时间复杂度：O(mn log m)，m 行 n 列、堆中最多 m 个元素；空间复杂度：O(m)，只额外保存这个堆。
class Solution:  # LeetCode 约定的题解类
    def maxSpending(self, values: List[List[int]]) -> int:  # values：每行递增的二维价格表
        n = len(values[0])  # 每行的列数，也是该行从右往左取时的起始下标
        pq = [(row[-1], i, n - 1) for i, row in enumerate(values)]  # 堆元素为（价格, 行号, 列号），先把每行最右端元素放进去
        heapify(pq)  # 原地建堆，O(m) 时间，比逐个 heappush 的 O(m log m) 更省
        ans = d = 0  # ans：累计花销；d：已经买到第几件（等价于第几天）
        while pq:  # 堆空说明所有物品都已被买走
            d += 1  # 天数递增，d 正好等于当前这件商品是第几件被买的
            v, i, j = heappop(pq)  # 弹出当前全局最便宜的价格及它的来源位置
            ans += v * d  # 第 d 天买这个物品，贡献 v * d
            if j:  # 该行左边还有元素可取
                heappush(pq, (values[i][j - 1], i, j - 1))  # 把同行前一个元素入堆，保证行内元素按顺序被取
        return ans  # 返回最大总开销
