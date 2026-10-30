// 题目：3080. 执行操作标记数组中的元素（Mark Elements on Array by Performing Queries）
// 思路：先按 (值, 下标) 排序，用指针 j 单调前进；每条查询标记指定下标，再从最小元素起补足 k 个未标记元素，同时维护未标记元素之和。
// 时间复杂度：O(n log n)，排序是瓶颈，其后扫描总共 O(n)；空间复杂度：O(n)，标记数组与排序数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {  // nums：原数组；queries：每条形如 [index, k] 的查询
        int n = nums.size();  // 数组长度
        long long s = accumulate(nums.begin(), nums.end(), 0LL);  // s 维护当前所有未标记元素之和，初值为全部元素之和
        vector<bool> mark(n);  // mark[i] 表示下标 i 是否已被标记
        vector<pair<int, int>> arr;  // 把 (元素值, 下标) 打包，便于按值排序
        for (int i = 0; i < n; ++i) {  // 遍历数组，构造排序用的二元组
            arr.emplace_back(nums[i], i);  // 记录元素值及其原始下标
        }
        sort(arr.begin(), arr.end());  // 按值升序排序（值相同时下标小的在前），用于贪心取最小元素
        vector<long long> ans;  // 依次保存每条查询之后的未标记元素和
        int m = queries.size();  // 查询条数
        for (int i = 0, j = 0; i < m; ++i) {  // j 是排序数组 arr 上只前进不回退的指针
            int index = queries[i][0], k = queries[i][1];  // 本查询要标记的下标 index，以及还要标记的最小元素个数 k
            if (!mark[index]) {  // 该下标尚未被标记时才需要从总和中扣减
                mark[index] = true;  // 标记该下标
                s -= nums[index];  // 从总和中减去被标记元素的值
            }
            for (; k && j < n; ++j) {  // 从最小元素开始找前 k 个尚未标记的元素
                if (!mark[arr[j].second]) {  // 只处理还没被标记过的元素
                    mark[arr[j].second] = true;  // 标记该元素
                    s -= arr[j].first;  // 从总和中减去它的值
                    --k;  // 还需要标记的元素个数减一
                }
            }
            ans.push_back(s);  // 记录本条查询执行完后的未标记元素和
        }
        return ans;  // 返回每条查询对应的答案
    }
};