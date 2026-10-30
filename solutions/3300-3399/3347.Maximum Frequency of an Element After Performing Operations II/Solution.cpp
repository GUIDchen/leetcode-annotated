// 题目：3347. 执行操作后元素的最高频率 II（Maximum Frequency of an Element After Performing Operations II）
// 思路：每个 nums[i] 都能通过一次操作变成 [x-k, x+k] 内任意值，用差分事件表统计能落到某个值上的元素个数，再与「原本次数 + 操作次数上限」取小。
// 时间复杂度：O(n log n)，建表 O(n)、map 有序扫描 O(n log n)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxFrequency(vector<int>& nums, int k, int numOperations) {  // nums：原数组；k：每次操作可增减的最大幅度；numOperations：最多可执行的操作次数
        unordered_map<int, int> cnt;  // cnt[x]：x 在原数组中本来出现的次数（这些元素不需要消耗操作）
        map<int, int> d;  // 差分事件表：键是坐标，有序遍历即可获得前缀和

        for (int x : nums) {  // 为每个元素建立它能够覆盖到的区间
            cnt[x]++;  // 统计原值 x 的出现次数
            d[x];  // 在 x 处插入一个 0 值事件，保证扫描时一定能遍历到坐标 x，且不影响前缀和
            d[x - k]++;  // 区间左端：[x-k, x+k] 从这里开始可以覆盖
            d[x + k + 1]--;  // 区间右端后一位：x+k 之后不再覆盖，事件 -1 抵消
        }  // 结束建表循环

        int ans = 0, s = 0;  // ans：当前最优答案；s：差分前缀和，即能变成当前坐标的元素个数
        for (const auto& [x, t] : d) {  // 按坐标从小到大扫描事件表
            s += t;  // 累加事件，得到能变成 x 的元素个数
            ans = max(ans, min(s, cnt[x] + numOperations));  // 原本就是 x 的元素不耗操作，其余元素每个至多一次操作且总数受 numOperations 限制
        }  // 结束扫描

        return ans;  // 返回最高频率
    }  // 结束方法
};  // 结束类
