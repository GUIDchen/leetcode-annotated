# 题目：373. 查找和最小的 K 对数字（Find K Pairs with Smallest Sums）
# 思路：每个 nums1[i] 对应一条递增候选链 (i,0),(i,1),…，把小顶堆初始化为各链队首，每次弹出最小和并压入同链下一个，重复至多 k 次。
# 时间复杂度：O((k + m) log m)，堆操作；空间复杂度：O(k + m)，堆与答案数组。
class Solution:  # LeetCode 约定的题解类
    def kSmallestPairs(  # 参数换行书写（源文件原样），nums1、nums2 升序，返回和最小的 k 对
        self, nums1: List[int], nums2: List[int], k: int  # 参数列表的续行，语义同上
    ) -> List[List[int]]:  # 返回类型：若干对 [nums1[i], nums2[j]]
        q = [[u + nums2[0], i, 0] for i, u in enumerate(nums1[:k])]  # 初始堆：只取 nums1 前 k 个元素，每条链的队首是 (u+nums2[0], i, 0)
        heapify(q)  # 原地把列表堆化，满足小顶堆性质
        ans = []  # 收集结果
        while q and k > 0:  # 堆非空且还没取够 k 对时继续
            _, i, j = heappop(q)  # 弹出当前和最小的三元组（和、i、j），和用 _ 忽略
            ans.append([nums1[i], nums2[j]])  # 按下标取真实值组成答案对
            k -= 1  # 已取一对，剩余配额减一
            if j + 1 < len(nums2):  # 该链还有下一个候选才继续入堆
                heappush(q, [nums1[i] + nums2[j + 1], i, j + 1])  # 同一条链的下一个下标 j+1 入堆，保证链内和递增
        return ans  # 返回和最小的至多 k 对数字
