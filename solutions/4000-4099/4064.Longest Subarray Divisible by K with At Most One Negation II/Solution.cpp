// 4064. 至多一次取反能被 K 整除的最长子数组 II  Longest Subarray Divisible by K with At Most One Negation II
// 核心思路：先算出前缀和余数，再对每个余数按首次出现位置排序；用双指针把已就绪的起点批量并入 best 数组，O(n + k) 得到答案。
// 复杂度：时间 O(n + k log k)，空间 O(n + k)。

class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {  // 返回至多取反一个元素后，和能被 k 整除的最长子数组长度
        int n = nums.size();  // 数组长度
        vector<int> p(n + 1);  // p[i] 表示前 i 个元素之和模 k
        for (int i = 0; i < n; ++i) {  // 递推计算每个前缀和余数
            p[i + 1] = (p[i] + nums[i]) % k;  // 用上一个前缀和余数递推
            if (p[i + 1] < 0) {  // C++ 取模可能为负
                p[i + 1] += k;  // 归一化为非负余数
            }
        }

        vector<int> first(k, -1);  // first[q] 记录余数 q 首次出现的下标，-1 表示未出现
        for (int i = 0; i <= n; ++i) {  // 遍历全部 n+1 个前缀位置
            if (first[p[i]] == -1) {  // 余数 p[i] 尚未被记录
                first[p[i]] = i;  // 记下它的最早下标
            }
        }

        vector<int> order;  // 收集所有真正出现过的余数
        for (int q = 0; q < k; ++q) {  // 按余数从小到大扫描
            if (first[q] != -1) {  // 该余数出现过才收集
                order.push_back(q);  // 加入待处理列表
            }
        }

        ranges::sort(order, [&](int a, int b) {  // 按首次出现下标升序排序
            return first[a] < first[b];  // 下标小者在前，便于后续双指针推进
        });

        vector<int> pos(k);  // pos[a] 记录余数 a 对应的 order 处理进度
        vector<int> best(k, INT_MAX);  // best[t] 记录能凑出余数 t 的最早起点
        for (int q = 0; q < k; ++q) {  // 初始化可用起点
            best[q] = first[q] == -1 ? INT_MAX : first[q];  // 出现过的余数用其首次下标，否则保持不可用
        }

        int ans = 0;  // 记录最长子数组长度
        for (int i = 0; i < n; ++i) {  // 枚举右端点 i
            int a = nums[i] % k;  // 当前元素对 k 取余
            if (a < 0) {  // C++ 取模可能为负
                a += k;  // 归一化为非负余数
            }

            while (pos[a] < order.size() && first[order[pos[a]]] <= i) {  // 把所有已可用的起点并入 best
                int q = order[pos[a]++];  // 取出当前起点余数并让指针后移
                int t = (q + 2 * a) % k;  // 取反 nums[i] 后，需要匹配的新余数
                best[t] = min(best[t], first[q]);  // 用更早的起点更新 best
            }

            int s = p[i + 1];  // 以 i 结尾的前缀和余数
            if (best[s] != INT_MAX) {  // 存在可匹配的起点
                ans = max(ans, i + 1 - best[s]);  // 用区间长度更新答案
            }
        }
        return ans;  // 返回最终最大长度
    }
};