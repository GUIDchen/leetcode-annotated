# 题目：2163. 删除元素后和的最小差值（Minimum Difference in Sums After Removal of Elements）
# 核心思路：预处理 pre[i]（前 i 个元素里选 n 个的最小和）与 suf[i]（后缀 i 起选 n 个的最大和），再枚举分界点最小化 pre[i] - suf[i+1]。
# 时间复杂度：O(m log n)，m 为数组长度；空间复杂度：O(m)，两个前缀/后缀数组。
class Solution:  # LeetCode 约定的题解类
    def minimumDifference(self, nums: List[int]) -> int:  # nums：长度是 3 的倍数的数组
        m = len(nums)  # 数组总长度
        n = m // 3  # 三等分后每份要取的元素个数

        s = 0  # 堆内元素之和，也就是当前最小的 n 个数之和
        pre = [0] * (m + 1)  # pre[i]：前 i 个元素中选 n 个能得到的最小和
        q1 = []  # 用负数模拟大根堆，方便弹出最大值
        for i, x in enumerate(nums[: n * 2], 1):  # 下标从 1 开始；第一份最多到 2n，给后面留出 n 个元素
            s += x  # 先无条件加入累加
            heappush(q1, -x)  # 存负数，堆顶就是原有元素里的最大值
            if len(q1) > n:  # 堆内元素超过 n 个
                s -= -heappop(q1)  # 弹出最大值（取负还原），保持 n 个元素之和最小
            pre[i] = s  # 记录前 i 个元素选 n 个的最小和

        s = 0  # 复用累加变量，开始计算后缀
        suf = [0] * (m + 1)  # suf[i]：从第 i 个元素到末尾选 n 个能得到的最大和
        q2 = []  # 小根堆，堆顶就是最小值
        for i in range(m, n, -1):  # 从右往左扫，必须给第一份留出 n 个位置
            x = nums[i - 1]  # 当前元素（下标转成 0 起始）
            s += x  # 先无条件加入累加
            heappush(q2, x)  # 放进小根堆
            if len(q2) > n:  # 堆内元素超过 n 个
                s -= heappop(q2)  # 弹出最小值，保持 n 个元素之和最大
            suf[i] = s  # 记录后缀选 n 个的最大和

        return min(pre[i] - suf[i + 1] for i in range(n, n * 2 + 1))  # 枚举分界点，取最小的 pre[i] - suf[i+1]
