# 题目：2593. 标记所有元素后数组的分数（Find Score of an Array After Marking All Elements）
# 思路：把 (值, 下标) 建成小根堆，每次弹出最小且未标记的元素并累加分数，同时标记它的左右邻居，再循环丢弃堆顶已标记的无效元素。
# 时间复杂度：O(n log n)，每对 (值, 下标) 入堆出堆各一次；空间复杂度：O(n)，堆与标记数组。
class Solution:  # LeetCode 约定的题解类
    def findScore(self, nums: List[int]) -> int:  # nums 是输入数组
        n = len(nums)  # 数组长度
        vis = [False] * n  # vis[i] 表示下标 i 是否已被标记
        q = [(x, i) for i, x in enumerate(nums)]  # 构造 (元素值, 下标) 列表
        heapify(q)  # 原地建小根堆，弹出时先比值再比下标
        ans = 0  # 累计分数
        while q:  # 堆非空说明还有未标记的元素
            x, i = heappop(q)  # 弹出当前最小元素的值 x 与下标 i
            ans += x  # 选中的元素计入分数
            vis[i] = True  # 标记当前下标
            for j in (i - 1, i + 1):  # 枚举左右邻居
                if 0 <= j < n:  # 邻居下标合法时
                    vis[j] = True  # 把它也标记掉
            while q and vis[q[0][1]]:  # 堆顶元素若已被标记就失去意义
                heappop(q)  # 直接丢弃这些无效元素
        return ans  # 返回累计得到的分数
