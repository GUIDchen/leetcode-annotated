# 题目：2234. 花园的最大总美丽值（Maximum Total Beauty of the Gardens）
# 思路：排序后用前缀和，枚举最终满园的花园数 x（从已达标数量开始），二分求剩余花园能抬到的最大高度 y，取 x*full + y*partial 的最大值。
# 时间复杂度：O(n log n)，排序 O(n log n) 且最多 n 次二分；空间复杂度：O(n)，前缀和列表 s。
class Solution:  # LeetCode 约定的题解类
    def maximumBeauty(  # 方法签名较长，按黑线换行书写，先只写参数列表开头
        self, flowers: List[int], newFlowers: int, target: int, full: int, partial: int  # self；flowers 各花园现有花朵数；newFlowers 可新增花朵数；target 满园阈值；full/partial 满园与部分美丽值
    ) -> int:  # 返回最大总美丽值
        flowers.sort()  # 原地升序排序，方便后续用前缀和与二分
        n = len(flowers)  # 花园数量
        s = list(accumulate(flowers, initial=0))  # 前缀和：s[i] 是前 i 座花园的花朵总数，initial=0 保证 s[0]=0
        ans, i = 0, n - bisect_left(flowers, target)  # ans 记录答案（初值 0）；i 是本来就已达标的花园数量
        for x in range(i, n + 1):  # 枚举最终满园的花园数 x，从 i 到 n
            newFlowers -= 0 if x == 0 else max(target - flowers[n - x], 0)  # 把第 n-x 座（新纳入满园的最小者）补到 target 并扣掉花费；x==0 时无需花费
            if newFlowers < 0:  # 剩余花朵不够再让一座花园满园
                break  # x 继续增大只会更费，直接结束枚举
            l, r = 0, n - x - 1  # 在剩余 n-x 座花园里二分，待抬平前缀的右端点区间为 [0, n-x-1]
            while l < r:  # 找「前 mid+1 座抬到 flowers[mid] 仍不超预算」的最大下标
                mid = (l + r + 1) >> 1  # 取上中位数，避免 l==mid 时死循环
                if flowers[mid] * (mid + 1) - s[mid + 1] <= newFlowers:  # 把前 mid+1 座抬到 flowers[mid] 的花费是否不超过剩余花朵
                    l = mid  # 可行则该下标可作为左边界
                else:  # 花费超出剩余花朵
                    r = mid - 1  # 只能往更小的下标找
            y = 0  # y 表示非满园花园能抬到的最大高度（对应 partial 部分的价值）
            if r != -1:  # r == -1 说明一座都抬不高，y 保持 0
                cost = flowers[l] * (l + 1) - s[l + 1]  # 先把前 l+1 座拉平到 flowers[l] 的基础花费
                y = min(flowers[l] + (newFlowers - cost) // (l + 1), target - 1)  # 剩余花朵平均分摊给 l+1 座，且高度不能达到 target
            ans = max(ans, x * full + y * partial)  # 满园 x 座 + 部分 y 座，更新最大总美丽值
        return ans  # 返回最大总美丽值
