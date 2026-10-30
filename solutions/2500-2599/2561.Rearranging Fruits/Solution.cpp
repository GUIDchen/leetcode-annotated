// 题目：2561. 重排水果（Rearranging Fruits）
// 核心思路：先算两筐各类水果的净差值，差值为奇数则无解；把「需要换走」的水果值收集排序，每次交换取「直接换」与「借全局最小值中转两次」中更便宜的方案。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，存放差值表与待交换的水果值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minCost(vector<int>& basket1, vector<int>& basket2) {  // basket1、basket2：两个等长果篮
        int n = basket1.size();  // 两筐大小相同，共用一个 n
        unordered_map<int, int> cnt;  // 键是水果值，值是 basket1 比 basket2 多出的个数（负数表示少）
        for (int i = 0; i < n; ++i) {  // 同步遍历两个果篮
            cnt[basket1[i]]++;  // 第一筐出现一次，计数加一
            cnt[basket2[i]]--;  // 第二筐出现一次，计数减一
        }
        int mi = 1 << 30;  // 全局最小水果值，初值取一个足够大的数
        vector<int> nums;  // 收集所有需要转移的水果值，每种多出的部分只取一半
        for (auto& [x, v] : cnt) {  // C++17 结构化绑定遍历哈希表：x 是水果值，v 是净差值
            if (v % 2) {  // 某类水果总个数为奇数，无法平分
                return -1;  // 题目要求此时返回 -1
            }
            for (int i = abs(v) / 2; i; --i) {  // 多出 |v| 个，其中一半必须换到对面去
                nums.push_back(x);  // 记录一个待交换的水果值
            }
            mi = min(mi, x);  // 顺便更新全局最小值，用于中转策略
        }
        ranges::sort(nums);  // C++20 的 ranges 排序，等价于 sort(nums.begin(), nums.end())
        int m = nums.size();  // 待交换水果的总个数（必为偶数）
        long long ans = 0;  // 累计最小代价，数值可能超过 int，用 long long
        for (int i = 0; i < m / 2; ++i) {  // 每个交换消掉两个元素，只需处理较小的一半
            ans += min(nums[i], mi * 2);  // 直接交换 nums[i]，或借全局最小值中转两次（代价 2 * mi），取较小者
        }
        return ans;  // 返回最小总代价
    }
};