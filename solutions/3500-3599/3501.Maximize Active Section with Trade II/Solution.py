# 题目：3501. 操作后最大活跃区段数 II（Maximize Active Section with Trade II）
# 思路：一次操作的净收益恰是被一段 '1' 隔开的两段连续 '0' 的长度之和，故答案为全局 '1' 的个数加区间内可配对 '0' 段的最大收益；对相邻 '0' 段长之和建 ST 表，每个查询 O(1) 取内部最优，再单独处理左右边界残段。
# 时间复杂度：O(n log n + q)，建表 O(n log n)、每个查询 O(1)；空间复杂度：O(n log n) 存稀疏表。
class Solution:  # LeetCode 约定的题解类
    def maxActiveSectionsAfterTrade(  # s：二进制字符串；queries：每个 [L, R] 询问子串 s[L..R] 的最优答案
        self, s: str, queries: List[List[int]]  # 方法签名：返回与 queries 等长的答案数组
    ) -> List[int]:  # 返回值为整数列表
        n = len(s)  # 字符串长度
        active = s.count('1')  # 全局 '1' 的个数：操作只把 '0' 变 '1'，这个基数在任何查询里都保留
        if '0' not in s:  # 全是 '1'：没有被 '1' 包围的 '0' 段，任何操作都无效
            return [active] * len(queries)  # 每个查询的答案都等于 n

        zeros = []  # zeros[k] = [第 k 段连续 '0' 的起始下标, 长度]
        idx = [0] * n  # idx[i] = 下标 i 所属的 '0' 段编号
        for i in range(n):  # 从左到右扫描，切出所有连续 '0' 段
            if s[i] == '0':  # 只有 '0' 位置才需要处理
                if i and s[i - 1] == '0':  # 与前一个字符同为 '0'，说明它延续着当前这段
                    zeros[-1][1] += 1  # 当前 '0' 段长度加一
                else:  # 否则它是新一段 '0' 的开头
                    zeros.append([i, 1])  # 记录新段的起点，初始长度为 1
            idx[i] = len(zeros) - 1  # 记录下标 i 指向的段编号；'1' 位置取最近出现的一段 '0'

        m = len(zeros) - 1  # 可配对区间数：相邻两段 '0' 一共 m 对
        K = m.bit_length() if m else 0  # ST 表层数 = ceil(log2(m))，m 为 0 时无需建表
        st = [[0] * max(m, 0) for _ in range(max(K, 1))]  # st[k][i]：从第 i 对开始、跨度 2^k 的相邻 '0' 段长度和的最大值
        for i in range(m):  # 初始化第 0 层：第 i 与第 i+1 两段 '0' 的长度之和
            st[0][i] = zeros[i][1] + zeros[i + 1][1]  # 第 i 对 '0' 段作为一次操作的收益
        for k in range(1, K):  # 逐层构建稀疏表
            for i in range(m - (1 << k) + 1):  # 只填起点不越界的那部分
                st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))])  # 左右两个 2^(k-1) 长区间取较大值

        def query(l: int, r: int) -> int:  # 区间最大值查询：返回第 l 到第 r 对 '0' 段的最大收益
            if l > r or m <= 0:  # 区间为空或根本没有 '0' 段
                return 0  # 没有可配对的段，收益为 0
            k = (r - l + 1).bit_length() - 1  # 取不超过区间长度的最大 2 的幂次
            return max(st[k][l], st[k][r - (1 << k) + 1])  # 用两个长度 2^k 的重叠区间覆盖整个查询区间

        ans = []  # 每个查询的答案
        for L, R in queries:  # 逐个查询独立处理
            iL, iR = idx[L], idx[R]  # 左右端点各自落在哪一段 '0' 上
            cntL = -1 if iL < 0 else zeros[iL][1] - (L - zeros[iL][0])  # 左边界若切在 '0' 段中间，它在区间内的后缀长度；不在 '0' 段上记为 -1
            cntR = -1 if iR < 0 else R - zeros[iR][0] + 1  # 右边界若切在 '0' 段中间，它在区间内的前缀长度；不在 '0' 段上记为 -1
            start = iL + 1  # 区间内部完整 '0' 段的起始编号（跳过左端残段）
            end = iR - (s[R] == '0')  # 右端若落在 '0' 段上则该段被截断、不能整段参与，end 为末尾完整段的下一编号
            best = active  # 不操作时的基线答案
            if start < end:  # 区间内至少存在一对完整的相邻 '0' 段
                best = max(best, active + query(start, end - 1))  # 用 ST 表取完全落在区间内的最大收益
            if s[L] == '0' and s[R] == '0' and iL + 1 == iR:  # 左右残段分属两个相邻的 '0' 段，中间恰好夹一段 '1'
                best = max(best, active + cntL + cntR)  # 两段残段可以直接配对
            if s[L] == '0' and iL + 1 < iR + (s[R] == '1'):  # 左残段与它右侧的第一段完整 '0' 配对
                best = max(best, active + cntL + zeros[iL + 1][1])  # 收益为左残段长度 + 右侧整段长度
            if s[R] == '0' and iL < iR - 1:  # 右残段与它左侧的第一段完整 '0' 配对
                best = max(best, active + cntR + zeros[iR - 1][1])  # 收益为右残段长度 + 左侧整段长度
            ans.append(best)  # 记下该查询的最优答案
        return ans  # 返回每个查询的答案
