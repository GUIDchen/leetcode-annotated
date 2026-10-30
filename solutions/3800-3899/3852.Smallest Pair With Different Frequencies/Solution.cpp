// 3852. 不同频率的最小数对 / Smallest Pair With Different Frequencies（简单）
// 核心思路：统计每个值的出现次数，字典序最优的左端必然是全局最小值 x，再在其余出现过的值中挑出频次与 cnt[x] 不同的最小 y，找不到则返回 [-1, -1]。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 设计一个算法：找频率不同的最小数对 (x, y)
public:  // 对外接口区
    vector<int> minDistinctFreqPair(vector<int>& nums) {  // 返回满足 x < y 且频次不同的最小数对，无解时返回 [-1, -1]
        const int inf = INT_MAX;  // 用 INT_MAX 充当“未找到”的哨兵
        unordered_map<int, int> cnt;  // 统计每个值出现的次数
        int x = inf;  // x 取数组最小值：它作数对左端时字典序必然最小

        for (int v : nums) {  // 遍历数组
            cnt[v]++;  // 累加该值的频次
            x = min(x, v);  // 同时维护全局最小值
        }  // 统计结束

        int minY = inf;  // 在剩余值中找频次与 cnt[x] 不同的最小 y
        for (auto& [y, _] : cnt) {  // 遍历所有出现过的值
            if (y < minY && cnt[x] != cnt[y]) {  // 比当前候选更小，且频次与 x 不同
                minY = y;  // 更新更小的 y
            }  // 候选判断结束
        }  // 遍历结束

        if (minY == inf) {  // 没有任何值与最小值的频次不同，说明没有合法数对
            return {-1, -1};  // 返回无解标记
        }  // 无解分支结束
        return {x, minY};  // 返回字典序最小的合法数对
    }  // 方法结束
};  // 类结束
