// 题目：3645. 最优激活顺序得到的最大总和（Maximum Total from Optimal Activation Order）
// 核心思路：激活上限相同的元素互相竞争同一份名额，而不同上限的组之间互不影响；于是按 limit 分组，组内价值从大到小排序，每组只取最多 min(limit, 组大小) 个最大的价值，累加即为最优。
// 复杂度：时间 O(n log n)，分组后组内排序主导；空间 O(n)，需要存放所有分组。
class Solution {  // LeetCode 题解类
public:  // 对外接口
    long long maxTotal(vector<int>& value, vector<int>& limit) {  // value：各元素的价值；limit：各元素对应的激活上限
        unordered_map<int, vector<int>> g;  // 哈希表：把「激活上限」映射到该组的价值列表
        int n = value.size();  // 元素个数
        for (int i = 0; i < n; ++i) {  // 逐个元素归组
            g[limit[i]].push_back(value[i]);  // 上限相同的元素放进同一组
        }
        long long ans = 0;  // 累加所有组的最优贡献
        for (auto& [lim, vs] : g) {  // 逐组处理，lim 为该组上限，vs 为该组价值
            sort(vs.begin(), vs.end(), greater<int>());  // 组内按价值从大到小排序
            for (int i = 0; i < min(lim, (int) vs.size()); ++i) {  // 该组最多只能贡献 lim 个元素，也不能超过组内元素个数
                ans += vs[i];  // 取价值最大的前若干个
            }
        }
        return ans;  // 返回可得到的最大总和
    }
};
