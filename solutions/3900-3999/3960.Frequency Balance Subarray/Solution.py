# 3960. 频率平衡子数组 / Frequency Balance Subarray
# 核心思路：枚举左端点 l 并逐步右移右端点 r，用 cnt 记录各元素的出现次数、用 freq 记录“出现次数 -> 拥有该次数的元素个数”，
#          当子数组只含一种元素，或 freq 恰好为两种互成 2 倍关系的频次时，用当前窗口长度刷新最长长度。
# 复杂度：时间 O(n^2)（枚举所有子数组），空间 O(n)（两个计数器）。

class Solution:
    def getLength(self, nums: List[int]) -> int:  # 求最长的“频率平衡”子数组长度
        n = len(nums)  # 数组长度
        ans = 1  # 至少可以取单个元素，答案下界为 1
        for l in range(n):  # 枚举子数组的左端点
            cnt = Counter()  # 记录窗口内每个元素的出现次数
            freq = Counter()  # 记录每种出现次数被多少个不同元素拥有
            for r in range(l, n):  # 右端点逐步右移，扩大窗口
                x = nums[r]  # 本轮新加入窗口的元素
                if freq[cnt[x]]:  # 旧的频次 cnt[x] 若仍被统计，则先把它移出频次表
                    freq[cnt[x]] -= 1  # 该频次的元素个数减一
                    if freq[cnt[x]] == 0:  # 减一后正好减到 0
                        freq.pop(cnt[x])  # 说明已没有元素使用该频次，从表中彻底删除
                cnt[x] += 1  # 元素 x 的出现次数加一
                freq[cnt[x]] += 1  # 频次表中为新的出现次数增加一个元素
                if (len(cnt) == 1) or (  # 频率平衡条件之一：子数组只含一种元素
                    len(freq) == 2  # 否则要求恰好存在两种频次
                    and (freq[cnt[x] * 2] or (cnt[x] % 2 == 0 and freq[cnt[x] // 2]))  # 且当前频次与另一频次互成 2 倍关系（f 与 2f）
                ):
                    ans = max(ans, r - l + 1)  # 当前窗口频率平衡，尝试更新最长长度
        return ans  # 返回最长频率平衡子数组的长度
