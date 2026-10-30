// 题目：3501. 操作后最大活跃区段数 II（Maximize Active Section with Trade II）
// 思路：一次操作的净收益恰是被一段 '1' 隔开的两段连续 '0' 的长度之和，故答案为全局 '1' 的个数加区间内可配对 '0' 段的最大收益；对相邻 '0' 段长之和建 ST 表，每个查询 O(1) 取内部最优，再单独处理左右边界残段。
// 时间复杂度：O(n log n + q)，建表 O(n log n)、每个查询 O(1)；空间复杂度：O(n log n) 存稀疏表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {  // s：二进制字符串；queries：每个 [L, R] 询问子串 s[L..R] 的最优答案
        int n = s.size();  // 字符串长度
        int active = count(s.begin(), s.end(), '1');  // 全局 '1' 的个数：操作只把 '0' 变 '1'，这个基数在任何查询里都保留
        if (s.find('0') == string::npos) {  // 全是 '1'：没有被 '1' 包围的 '0' 段，任何操作都无效
            return vector<int>(queries.size(), active);  // 每个查询的答案都等于 n
        }  // 全 '1' 的提前返回结束

        vector<pair<int, int>> zeros;  // zeros[k] = (第 k 段连续 '0' 的起始下标, 长度)
        vector<int> idx(n);  // idx[i] = 下标 i 所属的 '0' 段编号
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，切出所有连续 '0' 段
            if (s[i] == '0') {  // 只有 '0' 位置才需要处理
                if (i && s[i - 1] == '0') {  // 与前一个字符同为 '0'，说明它延续着当前这段
                    ++zeros.back().second;  // 当前 '0' 段长度加一
                } else {  // 否则它是新一段 '0' 的开头
                    zeros.emplace_back(i, 1);  // 记录新段的起点，初始长度为 1
                }  // '0' 段更新结束
            }  // if (s[i] == '0') 分支结束
            idx[i] = (int) zeros.size() - 1;  // 记录下标 i 指向的段编号；'1' 位置取最近出现的一段 '0'
        }  // 扫描结束，所有 '0' 段和下标映射都建好

        int m = (int) zeros.size() - 1;  // 可配对区间数：相邻两段 '0' 一共 m 对
        int K = m ? 32 - __builtin_clz(m) : 0;  // ST 表层数 = ceil(log2(m))
        vector<vector<int>> st(max(K, 1), vector<int>(max(m, 0)));  // st[k][i]：从第 i 对开始、跨度 2^k 的相邻 '0' 段长度和的最大值
        for (int i = 0; i < m; ++i) {  // 初始化第 0 层：第 i 与第 i+1 两段 '0' 的长度之和
            st[0][i] = zeros[i].second + zeros[i + 1].second;  // 第 i 对 '0' 段作为一次操作的收益
        }  // 第 0 层填完
        for (int k = 1; k < K; ++k) {  // 逐层构建稀疏表
            for (int i = 0; i + (1 << k) <= m; ++i) {  // 只填起点不越界的那部分
                st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);  // 左右两个 2^(k-1) 长区间取较大值
            }  // 内层结束
        }  // 外层结束，ST 表构建完成

        auto query = [&](int l, int r) {  // 区间最大值查询：返回第 l 到第 r 对 '0' 段的最大收益
            if (l > r || m <= 0) {  // 区间为空或根本没有 '0' 段
                return 0;  // 没有可配对的段，收益为 0
            }  // 边界判断结束
            int k = 31 - __builtin_clz(r - l + 1);  // 取不超过区间长度的最大 2 的幂次
            return max(st[k][l], st[k][r - (1 << k) + 1]);  // 用两个长度 2^k 的重叠区间覆盖整个查询区间
        };  // lambda 定义结束

        vector<int> ans;  // 每个查询的答案
        ans.reserve(queries.size());  // 预留容量，避免反复扩容
        for (auto& q : queries) {  // 逐个查询独立处理
            int L = q[0], R = q[1];  // 本次查询的子串边界
            int iL = idx[L], iR = idx[R];  // 左右端点各自落在哪一段 '0' 上
            int cntL = iL < 0 ? -1 : zeros[iL].second - (L - zeros[iL].first);  // 左边界若切在 '0' 段中间，它在区间内的后缀长度；不在 '0' 段上记为 -1
            int cntR = iR < 0 ? -1 : R - zeros[iR].first + 1;  // 右边界若切在 '0' 段中间，它在区间内的前缀长度；不在 '0' 段上记为 -1
            int start = iL + 1;  // 区间内部完整 '0' 段的起始编号（跳过左端残段）
            int end = iR - (s[R] == '0');  // 右端若落在 '0' 段上则该段被截断、不能整段参与，end 为末尾完整段的下一编号
            int best = active;  // 不操作时的基线答案
            if (start < end) {  // 区间内至少存在一对完整的相邻 '0' 段
                best = max(best, active + query(start, end - 1));  // 用 ST 表取完全落在区间内的最大收益
            }  // 完整段对处理结束
            if (s[L] == '0' && s[R] == '0' && iL + 1 == iR) {  // 左右残段分属两个相邻的 '0' 段，中间恰好夹一段 '1'
                best = max(best, active + cntL + cntR);  // 两段残段可以直接配对
            }  // 左右残段配对结束
            if (s[L] == '0' && iL + 1 < iR + (s[R] == '1')) {  // 左残段与它右侧的第一段完整 '0' 配对
                best = max(best, active + cntL + zeros[iL + 1].second);  // 收益为左残段长度 + 右侧整段长度
            }  // 左残段处理结束
            if (s[R] == '0' && iL < iR - 1) {  // 右残段与它左侧的第一段完整 '0' 配对
                best = max(best, active + cntR + zeros[iR - 1].second);  // 收益为右残段长度 + 左侧整段长度
            }  // 右残段处理结束
            ans.push_back(best);  // 记下该查询的最优答案
        }  // 查询处理结束
        return ans;  // 返回每个查询的答案
    }  // 方法结束
};  // 类定义结束
