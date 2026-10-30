# 3672. Sum of Weighted Modes in Subarrays（子数组中加权众数的总和）
# 核心思路：小顶堆按 (-频次, 值) 维护候选众数，哈希表记录窗口频次，堆顶过期就弹出，逐个窗口累加加权众数。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # 定义 Solution 类
    def modeWeight(self, nums: List[int], k: int) -> int:  # 求所有长度为 k 的子数组的加权众数之和
        pq = []  # 小顶堆，元素为 (-频次, 值)
        cnt = defaultdict(int)  # 记录当前窗口内每个值的出现次数
        for x in nums[:k]:  # 初始化长度为 k 的第一个窗口
            cnt[x] += 1  # 该值的频次加一
            heappush(pq, (-cnt[x], x))  # 把 (-频次, 值) 压入堆

        def get_mode() -> int:  # 计算当前窗口的加权众数
            while -pq[0][0] != cnt[pq[0][1]]:  # 堆顶频次与哈希表不一致说明已是过期记录
                heappop(pq)  # 弹出过期的堆顶
            freq, val = -pq[0][0], pq[0][1]  # 取出最新的频次与对应的值
            return freq * val  # 返回加权众数（频次 × 值）

        ans = 0  # 累加每个长度为 k 的子数组的加权众数
        ans += get_mode()  # 加上第一个窗口的贡献

        for i in range(k, len(nums)):  # 窗口右移，处理每个新进入的元素
            x, y = nums[i], nums[i - k]  # x 为新进入的元素，y 为滑出的元素
            cnt[x] += 1  # 新元素频次加一
            cnt[y] -= 1  # 滑出元素频次减一
            heappush(pq, (-cnt[x], x))  # 把新元素的当前频次入堆
            heappush(pq, (-cnt[y], y))  # 把滑出元素的当前频次入堆

            ans += get_mode()  # 累加当前窗口的加权众数

        return ans  # 返回加权众数的总和
