# 题目：1774. 最接近目标价格的甜点成本（Closest Dessert Cost）
# 思路：DFS 枚举「每种配料选或不选」得到全部配料子集和并排序，再对每种基料二分查找最接近目标的那一档子集和。
# 时间复杂度：O(2^m·log 2^m + n·2^m·log 2^m)，m 为配料种数、n 为基料种数；空间复杂度：O(2^m) 存子集和。
class Solution:  # LeetCode 约定的题解类
    def closestCost(  # baseCosts：基料价格；toppingCosts：配料价格；target：目标价格
        self, baseCosts: List[int], toppingCosts: List[int], target: int  # self 是实例本身
    ) -> int:  # 返回最接近 target 的甜点总价
        def dfs(i, t):  # 内部 DFS：枚举配料子集，i 是当前配料下标，t 是已选总和
            if i >= len(toppingCosts):  # 所有配料都决定完了
                arr.append(t)  # 记录一种子集和
                return  # 递归出口
            dfs(i + 1, t)  # 不选第 i 种配料
            dfs(i + 1, t + toppingCosts[i])  # 选第 i 种配料

        arr = []  # 保存所有配料子集和
        dfs(0, 0)  # 从第 0 种配料、总和 0 开始枚举
        arr.sort()  # 从小到大排序，便于二分查找
        d = ans = inf  # d：当前最小价格差；ans：当前最优总价格

        # 选择一种冰激淋基料
        for x in baseCosts:  # 枚举每一种基料
            # 枚举子集和
            for y in arr:  # 枚举每一种配料子集和
                # 二分查找
                i = bisect_left(arr, target - x - y)  # 找到第一个不小于目标补数的位置
                for j in (i, i - 1):  # 只检查 i 和 i-1 两个候选位置
                    if 0 <= j < len(arr):  # 下标合法才检查
                        t = abs(x + y + arr[j] - target)  # 当前总价与目标的绝对差
                        if d > t or (d == t and ans > x + y + arr[j]):  # 差更小，或差相同但总价更小，就更新
                            d = t  # 更新最小差
                            ans = x + y + arr[j]  # 更新答案总价
        return ans  # 返回最接近目标的价格
