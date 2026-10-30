# 题目：1687. 从仓库到码头运输箱子（Delivering Boxes from Storage to Ports）
# 思路：重量与换港口次数各做前缀和，f[i] 表示运完前 i 个箱子的最少行程，枚举最后一趟起点 j 做区间 DP 转移。
# 时间复杂度：O(n^2) 的区间枚举；空间复杂度：O(n)，重量前缀和、换港口次数前缀和与 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def boxDelivering(  # boxes[i] = [ports[i], weight[i]]；maxBoxes / maxWeight 是每趟的箱子数与重量上限
        self, boxes: List[List[int]], portsCount: int, maxBoxes: int, maxWeight: int  # 参数过多，源文件这里换行书写（保持原样）
    ) -> int:  # 返回最少行程数
        n = len(boxes)  # 箱子总数
        ws = list(accumulate((box[1] for box in boxes), initial=0))  # 重量前缀和：initial=0 使 ws[i] 表示前 i 个箱子的重量
        c = [int(a != b) for a, b in pairwise(box[0] for box in boxes)]  # pairwise 相邻取对，港口不同记 1，得到「是否换港口」序列
        cs = list(accumulate(c, initial=0))  # 换港口次数前缀和，initial=0 使 cs[i] 表示前 i 个箱子内部的换港口次数
        f = [inf] * (n + 1)  # f[i]：运完前 i 个箱子的最少行程数，先全部置为无穷大
        f[0] = 0  # 空区间不需要行程
        for i in range(1, n + 1):  # 按箱子个数递增求解
            for j in range(max(0, i - maxBoxes), i):  # 枚举最后一趟的起点 j，保证这一段不超过 maxBoxes 个箱子
                if ws[i] - ws[j] <= maxWeight:  # 该段重量不超过 maxWeight 才是合法的一趟
                    f[i] = min(f[i], f[j] + cs[i - 1] - cs[j] + 2)  # 转移：f[j] + 段内换港口次数 + 2（回仓库一趟 + 从仓库出发一趟）
        return f[n]  # 运完所有箱子的答案
