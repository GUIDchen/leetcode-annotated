# 题目：1601. 最多可达成的换楼请求数目（Maximum Number of Achievable Transfer Requests）
# 思路：二进制枚举请求子集，用出入度计数判断该子集能否让每栋楼人数守恒，取最大的合法子集大小。
# 时间复杂度：O(2^m * m)，枚举子集并逐个校验；空间复杂度：O(n)，一个出入度计数数组。
class Solution:  # LeetCode 约定的题解类
    def maximumRequests(self, n: int, requests: List[List[int]]) -> int:  # n 为楼栋数，requests[i] = [from, to] 表示一次换楼请求
        def check(mask: int) -> bool:  # 判断 mask 选出的这批请求能否同时全部满足
            cnt = [0] * n  # 每栋楼的净人数变化（搬入为 +，搬出为 -）
            for i, (f, t) in enumerate(requests):  # 同时拿到请求下标与搬出楼 f、搬入楼 t
                if mask >> i & 1:  # 第 i 位为 1 表示该请求被选中
                    cnt[f] -= 1  # 搬出，该楼人数减少
                    cnt[t] += 1  # 搬入，该楼人数增加
            return all(v == 0 for v in cnt)  # 所有楼净变化为 0 才说明人数守恒、该子集可行

        # 枚举所有 2^m 种请求子集，取其中最大的合法子集
        ans = 0  # 合法请求子集的最大大小
        for mask in range(1 << len(requests)):  # 枚举所有请求子集
            cnt = mask.bit_count()  # 统计子集里选了多少个请求
            if ans < cnt and check(mask):  # 子集更大且合法时才更新答案
                ans = cnt  # 记录新的最优值
        return ans  # 返回最多可同时满足的请求数
