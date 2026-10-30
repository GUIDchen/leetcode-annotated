// 3897. 连接二进制片段得到的最大值 / Maximum Value of Concatenated Binary Segments
// 核心思路：按「纯 1 段 → 含 1 段 → 纯 0 段」贪心排序后依次拼接，再用 2 的幂权重从最高位往低位累加得到取模结果。
// 复杂度：时间 O(n log n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有接口
    static constexpr int MOD = 1'000'000'007;  // 结果取模的模数

    int maxValue(vector<int>& nums1, vector<int>& nums0) {  // nums1[i] 个 1 与 nums0[i] 个 0 组成第 i 段，重排拼接后求最大值
        vector<pair<int, int>> pairs;  // 每段记录 (1 的个数, 0 的个数)
        int b = 0;  // 所有段的总位数
        for (int i = 0; i < nums1.size(); ++i) {  // 遍历每一段
            pairs.emplace_back(nums1[i], nums0[i]);  // 存入该段的 1/0 个数
            b += nums1[i] + nums0[i];  // 累加总位数
        }  // 段信息收集结束

        sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {  // 贪心排序：让高位的 1 尽量靠前
            auto group = [](const pair<int, int>& p) {  // 把段分成三类：纯 1 段、含 1 段、纯 0 段
                if (p.second == 0) {  // 没有 0，整段都是 1
                    return 0;  // 第 0 类：纯 1 段应排最前
                }  // 第一类判断结束
                if (p.first > 0) {  // 既有 1 又有 0
                    return 1;  // 第 1 类：1 在前的段排中间
                }  // 第二类判断结束
                return 2;  // 第 2 类：只有 0 的段排最后
            };  // 分类函数结束

            int g1 = group(a), g2 = group(b);  // 取两段各自的类别
            if (g1 != g2) {  // 类别不同时按类别升序排列
                return g1 < g2;  // 类别小的排前面
            }  // 类别比较结束
            if (g1 == 0) {  // 同为纯 1 段
                return a.first > b.first;  // 1 更多的段放前面更值钱
            }  // 纯 1 段比较结束
            if (g1 == 1) {  // 同为含 1 段
                if (a.first != b.first) {  // 先比较 1 的个数
                    return a.first > b.first;  // 1 更多的段排前面
                }  // 1 的个数比较结束
                return a.second < b.second;  // 1 的个数相同时，0 更少的排前面
            }  // 含 1 段比较结束
            return a.second < b.second;  // 纯 0 段：0 更少的排前面
        });  // 排序规则定义结束

        vector<long long> p(b, 1);  // p[i] = 2^i mod MOD，即第 i 位的权重
        for (int i = 1; i < b; ++i) {  // 递推每一位的权重
            p[i] = p[i - 1] * 2 % MOD;  // 权重翻倍后取模
        }  // 权重表构造结束

        long long ans = 0;  // 拼接后的答案（取模）
        --b;  // b 改为当前最高位的下标
        for (auto& [cnt1, cnt0] : pairs) {  // 按贪心顺序依次放置各段
            while (cnt1--) {  // 先把本段的 1 依次放到当前最高位
                ans = (ans + p[b--]) % MOD;  // 该位为 1，累加其权重并下移一位
            }  // 本段的 1 放置结束
            b -= cnt0;  // 跳过本段 0 占据的低位
        }  // 各段放置结束
        return (int) ans;  // 返回最大拼接值
    }  // maxValue 结束
};  // 类定义结束
