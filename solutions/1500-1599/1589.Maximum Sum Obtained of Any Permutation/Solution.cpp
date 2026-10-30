// 题目：1589. 所有排列中的最大和（Maximum Sum Obtained of Any Permutation）
// 思路：用差分数组统计每个下标被多少个区间覆盖，再把最大的数与最大的覆盖次数配对，即得最大和。
// 时间复杂度：O(n log n)，两处排序主导；空间复杂度：O(n)，差分数组（C++ 版用变长数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {  // nums：可任意重排的数组；requests：查询区间列表
        int n = nums.size();  // 数组长度
        int d[n];  // 差分数组，最终统计每个下标被多少个区间覆盖
        memset(d, 0, sizeof(d));  // 差分初值全部为 0
        for (auto& req : requests) {  // 对每个查询区间做差分标记
            int l = req[0], r = req[1];  // 区间左右端点
            d[l]++;  // 区间起点处覆盖次数 +1
            if (r + 1 < n) {  // 右端点后一位仍在数组内时才需要抵消
                d[r + 1]--;  // 区间结束后取消覆盖，防止越界访问
            }
        }
        for (int i = 1; i < n; ++i) {  // 差分数组求前缀和，还原出真实覆盖次数
            d[i] += d[i - 1];  // 累加前一位，得到第 i 位被覆盖的次数
        }
        sort(nums.begin(), nums.end());  // 数值升序排列
        sort(d, d + n);  // 覆盖次数升序排列
        long long ans = 0;  // 用 64 位累加，避免乘法溢出
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        for (int i = 0; i < n; ++i) {  // 小数值配小覆盖次数，按同序配对
            ans = (ans + 1LL * nums[i] * d[i]) % mod;  // 乘出 64 位结果后立即取模
        }
        return ans;  // 返回最大可能和
    }
};