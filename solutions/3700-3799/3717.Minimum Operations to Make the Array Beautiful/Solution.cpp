// 题目：3717. 使数组变美的最小操作次数（Minimum Operations to Make the Array Beautiful）
// 思路：从左到右做 DP，用哈希表记录「上一位置最终取值 -> 已付最小代价」；当前位置只能改成上一取值的不小于 nums[i] 的倍数且不超过 100，滚动更新取最小代价。
// 时间复杂度：O(n·S²)，S = 100 为元素取值上限；空间复杂度：O(S)，哈希表最多保存 S 个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：目标数组；返回使其变美观（相邻元素成倍数）的最少操作次数
        unordered_map<int, int> f;  // f[上一位置最终取值] = 处理到该位置为止的最小总代价
        f[nums[0]] = 0;  // 第一个元素保持原值不变，代价为 0

        for (int i = 1; i < nums.size(); i++) {  // 依次处理后面的每一个元素
            int x = nums[i];  // 当前元素的原值
            unordered_map<int, int> g;  // g[本位置最终取值] = 最小总代价
            for (auto [pre, s] : f) {  // 枚举上一位置的所有取值与对应代价
                int cur = (x + pre - 1) / pre * pre;  // 不小于 x 的最小 pre 的倍数
                while (cur <= 100) {  // 枚举所有不超过 100 的 pre 的倍数
                    int val = s + (cur - x);  // 把 x 改成 cur 的代价累加到总代价
                    auto jt = g.find(cur);  // 查找该取值的已有最优代价
                    if (jt == g.end() || jt->second > val) {  // 尚未记录或当前方案更优
                        g[cur] = val;  // 更新最优代价
                    }  // 更优判断结束
                    cur += pre;  // 试下一个倍数
                }  // 该 pre 的倍数枚举结束
            }  // 上一位置的取值枚举结束
            f = move(g);  // 滚动到本位置的状态
        }  // 所有元素处理完毕

        int ans = INT_MAX;  // 最优答案
        for (auto& it : f) {  // 枚举最后一个位置的所有取值
            ans = min(ans, it.second);  // 取最小总代价
        }  // 枚举结束
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束
