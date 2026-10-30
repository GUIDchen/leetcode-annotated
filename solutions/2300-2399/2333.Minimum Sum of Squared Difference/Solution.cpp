// 题目：2333. 最小差值平方和（Minimum Sum of Squared Difference）
// 思路：先统计 nums1 与 nums2 逐位绝对差的桶 cnt 及总差 s；若总差不超过 k 就能全清零。否则按「每次把差减 1」贪心，从最大的差值逐层往下削，因为削平大差值对平方和的收益最高。
// 时间复杂度：O(n + M)，M = 10⁵ 为差值上界，每层桶只搬运一次；空间复杂度：O(M)，计数桶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {  // nums1/nums2 为两个数组，k1/k2 分别是它们各自可增减的总次数
        int k = k1 + k2;  // 两种操作对差值的削弱效果相同，合并成一个总预算
        long long s = 0;  // s 累计所有绝对差之和，也就是把差值全部清零所需的最少操作数
        int mx = 0;  // 记录最大差值，作为后面倒序遍历桶的起点
        vector<int> cnt(100001);  // 值域计数桶：cnt[v] 表示差值恰为 v 的位置个数（差值不超过 10⁵）
        for (int i = 0; i < nums1.size(); ++i) {  // 逐位比较两个数组
            int v = abs(nums1[i] - nums2[i]);  // 当前这一位的绝对差
            ++cnt[v];  // 差值 v 的出现次数加一
            s += v;  // 把差值累加进总和
            mx = max(mx, v);  // 维护最大差值
        }  // 统计结束
        if (s <= k) {  // 总差值不超过预算，说明可以把每个差值都压到 0
            return 0;  // 平方和自然为 0
        }  // 全清零分支结束
        for (int v = mx; v > 0 && k > 0; --v) {  // 从最大差值往下逐层削平，预算用完立即停止
            if (cnt[v] == 0) {  // 这一层没有元素，直接看下一层
                continue;  // 跳过空桶
            }  // 空桶判断结束
            int take = min(cnt[v], k);  // 本层最多能把 take 个差值从 v 降到 v-1
            k -= take;  // 扣除这些搬运消耗的预算
            cnt[v] -= take;  // 差值 v 的元素个数减少 take
            cnt[v - 1] += take;  // 被削平的元素落到 v-1 这一层
        }  // 逐层削平结束
        long long ans = 0;  // 累加最终的平方和
        for (int v = 0; v <= mx; ++v) {  // 桶的上界只需到 mx，更大的桶一定为空
            ans += 1LL * v * v * cnt[v];  // 差值 v 的每个位置贡献 v²，共 cnt[v] 个；1LL 防止 v*v 溢出
        }  // 平方和统计结束
        return ans;  // 返回最小平方和
    }  // 方法结束
};  // 类结束
