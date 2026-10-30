// 题目：3277. 查询子数组最大异或分数（Maximum XOR Score Subarray Queries）
// 思路：区间异或分数可递推 f[i][j] = f[i][j-1] ^ f[i+1][j]，再用 g[i][j] 维护子区间最大值，实现 O(1) 查询。
// 时间复杂度：O(n^2 + q)，预处理所有区间后每次查询 O(1)；空间复杂度：O(n^2)，两张二维表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {  // nums：原数组；queries：若干查询区间
        int n = nums.size();  // 数组长度
        vector<vector<int>> f(n, vector<int>(n));  // f[i][j]：nums[i..j] 这个区间本身的异或分数
        vector<vector<int>> g(n, vector<int>(n));  // g[i][j]：nums[i..j] 所有子区间的最大异或分数
        for (int i = n - 1; i >= 0; --i) {  // 倒序枚举左端点，保证依赖的更短区间已经算好
            f[i][i] = nums[i];  // 单元素区间的分数就是元素本身
            g[i][i] = nums[i];  // 单元素区间的最大分数也是它本身
            for (int j = i + 1; j < n; ++j) {  // 枚举右端点
                f[i][j] = f[i][j - 1] ^ f[i + 1][j];  // 区间分数递推：去掉右端点的分数异或去掉左端点的分数
                g[i][j] = max({f[i][j], g[i][j - 1], g[i + 1][j]});  // 最大分数来自：本区间、去掉右端点、去掉左端点
            }
        }
        vector<int> ans;  // 保存每个查询的答案
        for (const auto& q : queries) {  // 依次处理每个查询
            int l = q[0], r = q[1];  // 查询区间的左右端点
            ans.push_back(g[l][r]);  // 直接从预处理好的表里取答案
        }
        return ans;  // 返回所有查询的结果
    }
};
