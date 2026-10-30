# 3767. 选择 K 个任务的最大总分数 / Maximize Points After Choosing K Tasks
# 核心思路：先假设全部任务都用技术 2，再按“技术1 - 技术2”的差值降序排序，前 k 个强制换成技术 1，其余任务仅在换成技术 1 不亏时才换。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # 定义解法类
    def maxPoints(self, technique1: List[int], technique2: List[int], k: int) -> int:  # 用技术 1 恰好处理 k 个任务，求能获得的最大总分数
        n = len(technique1)  # 任务数量
        idx = sorted(range(n), key=lambda i: -(technique1[i] - technique2[i]))  # 按“技术1 - 技术2”的差值降序排序下标
        ans = sum(technique2)  # 先假设所有任务都使用技术 2
        for i in idx[:k]:  # 前 k 个任务必须换成技术 1
            ans -= technique2[i]  # 减去技术 2 的分数
            ans += technique1[i]  # 加上技术 1 的分数
        for i in idx[k:]:  # 剩余任务只有在技术 1 不劣于技术 2 时才切换
            if technique1[i] >= technique2[i]:  # 换成技术 1 不会亏
                ans -= technique2[i]  # 减去技术 2 的分数
                ans += technique1[i]  # 加上技术 1 的分数
        return ans  # 返回最大总分数
