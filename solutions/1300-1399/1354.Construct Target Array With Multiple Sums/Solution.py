# 题目：1354. 多次求和构造目标数组（Construct Target Array With Multiple Sums）
# 思路：倒推。设最大元素为 mx、其余元素之和为 t，则 mx 必由 t 反复累加而来，故把 mx 一次性换成 mx % t（整除时取 t），直到最大值变成 1。
# 时间复杂度：O(n log n + n log(max))；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def isPossible(self, target: List[int]) -> bool:  # 判断 target 能否由「全 1 数组、每次把某个元素替换为当前总和」构造出来
        s = sum(target)  # 记录所有元素之和，倒推时用它算「其余元素之和」
        pq = [-x for x in target]  # Python 的 heapq 是小顶堆，取负值即可模拟大顶堆
        heapify(pq)  # 原地建堆，时间 O(n)
        while -pq[0] > 1:  # 堆顶（最大值）仍大于 1，说明还能继续倒推
            mx = -heappop(pq)  # 弹出当前最大值并还原符号
            t = s - mx  # 其余元素之和，也正是上一步被反复加上的那个总和
            if t == 0 or mx - t < 1:  # t 为 0（只剩一个元素）或减一次 t 后不再为正数时，该状态不可能出现
                return False  # 无法由全 1 构造出来
            x = (mx % t) or t  # 一次跳过多次加法；整除时取模为 0，用 or t 保证元素至少为 1
            heappush(pq, -x)  # 把倒推出的新值（取负）放回堆中
            s = s - mx + x  # 同步更新总和：去掉 mx，加上 x
        return True  # 已倒推到全 1，说明 target 可以构造
