# 3691. Maximum Total Subarray Value II（3691. 最大子数组总值 II）
# 核心思路：子数组价值 = 区间最大值 - 区间最小值；先用 ST 表做到 O(1) 区间最值查询，再用“负价值”列表模拟大根堆，按固定左端点、右端点从 n-1 左移的方式取前 k 大价值累加。
# 复杂度：时间 O(n log n + k log n)，空间 O(n log n)。
class SparseTableRMQ:  # 定义稀疏表（ST 表）类，支持 O(1) 区间最值查询
    def __init__(self, data: List[int]):  # 构造函数：用原数组预处理 ST 表
        self.n = len(data)  # 记录数组长度
        self.max_log = self.n.bit_length() + 1  # 倍增层数取“二进制位数 + 1”
        self.f_max = [[0] * self.max_log for _ in range(self.n)]  # 最大值表
        self.f_min = [[0] * self.max_log for _ in range(self.n)]  # 最小值表

        self.lg = [0] * (self.n + 1)  # 对数表：lg[i] = floor(log2(i))
        for i in range(2, self.n + 1):  # 从小到大递推 log2
            self.lg[i] = self.lg[i >> 1] + 1  # lg[i] = lg[i/2] + 1

        for i in range(self.n):  # 长度 1（j = 0）的区间初值就是元素本身
            self.f_max[i][0] = data[i]  # 最大值初值
            self.f_min[i][0] = data[i]  # 最小值初值

        for j in range(1, self.max_log):  # 枚举区间长度 2^j
            for i in range(self.n - (1 << j) + 1):  # 枚举起点，保证区间不越界
                self.f_max[i][j] = max(  # 最大值由左右两段长度 2^(j-1) 的区间合并得到
                    self.f_max[i][j - 1], self.f_max[i + (1 << (j - 1))][j - 1]  # 左半段与右半段取最大
                )  # 赋值语句结束
                self.f_min[i][j] = min(  # 最小值同理
                    self.f_min[i][j - 1], self.f_min[i + (1 << (j - 1))][j - 1]  # 左半段与右半段取最小
                )  # 赋值语句结束

    def query_max(self, l: int, r: int) -> int:  # 查询闭区间 [l, r] 的最大值
        k = self.lg[r - l + 1]  # 指数 k = floor(log2(区间长度))
        return max(self.f_max[l][k], self.f_max[r - (1 << k) + 1][k])  # 用两段长度 2^k 的区间覆盖 [l, r] 取最大

    def query_min(self, l: int, r: int) -> int:  # 查询闭区间 [l, r] 的最小值
        k = self.lg[r - l + 1]  # 同上，求指数 k
        return min(self.f_min[l][k], self.f_min[r - (1 << k) + 1][k])  # 用两段长度 2^k 的区间覆盖 [l, r] 取最小


class Solution:  # 定义题解类
    def maxTotalValue(self, nums: List[int], k: int) -> int:  # 主函数：取价值最大的 k 个子数组，返回价值总和
        n = len(nums)  # n 为数组长度
        st = SparseTableRMQ(nums)  # 预处理 ST 表
        pq = []  # 用堆（存负价值模拟大根堆）保存候选子数组
        for l in range(n):  # 对每个左端点 l 初始化右端点 n-1
            val = st.query_max(l, n - 1) - st.query_min(l, n - 1)  # 当前子数组价值 = 区间最大值 - 区间最小值
            heappush(pq, (-val, l, n - 1))  # 取负入堆，实现大根堆

        ans = 0  # 累加答案
        for _ in range(k):  # 一共取 k 个子数组
            val, l, r = heappop(pq)  # 弹出当前价值最大的子数组
            ans += -val  # 累加其价值（取负还原）
            if r > l:  # 右端点还能继续左移，产生后继候选
                val = st.query_max(l, r - 1) - st.query_min(l, r - 1)  # 后继价值：左端点不变、右端点减一
                heappush(pq, (-val, l, r - 1))  # 后继入堆
        return ans  # 返回前 k 大价值之和
