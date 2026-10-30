// 题目：2941. 子数组的最大 GCD-Sum（Maximum GCD-Sum of a Subarray）
// 思路：枚举右端点，利用「终点固定时子数组的 gcd 只有 O(log V) 种」维护 (起点, gcd) 列表，长度达到 k 就更新答案。
// 时间复杂度：O(n log V log V)，每个右端点最多 O(log V) 个不同 gcd，每次求 gcd 为 O(log V)；空间复杂度：O(n)，前缀和与列表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxGcdSum(vector<int>& nums, int k) {  // nums：输入数组；k：子数组允许的最小长度
        int n = nums.size();  // n：数组长度
        long long s[n + 1];  // 前缀和数组，长度为 n+1（这里是 GNU 扩展的可变长数组）
        s[0] = 0;  // 空前缀和为 0
        for (int i = 1; i <= n; ++i) {  // 依次递推每个前缀和
            s[i] = s[i - 1] + nums[i - 1];  // s[i] 表示 nums[0..i-1] 的元素之和
        }  // 前缀和计算结束
        vector<pair<int, int>> f;  // f：以 i-1 结尾的 (起点, gcd) 列表，gcd 去重后不超过 O(log V) 项
        long long ans = 0;  // ans：记录最大值，初始为 0
        for (int i = 0; i < n; ++i) {  // 枚举子数组的右端点 i
            vector<pair<int, int>> g;  // g：把右端点扩展到 i 之后的新列表
            for (auto [j, x] : f) {  // 继承所有以 i-1 结尾的区间
                int y = gcd(x, nums[i]);  // 区间右端扩到 i 之后的新 gcd
                if (g.empty() || g.back().second != y) {  // gcd 相同只保留最靠左（也就是最长）的那一项
                    g.emplace_back(j, y);  // 记录起点 j 与新的 gcd 值
                }  // 去重判断结束
            }  // 继承旧列表结束
            f = move(g);  // 用新列表替换旧列表，move 避免深拷贝
            f.emplace_back(i, nums[i]);  // 补上只含 nums[i] 本身的区间
            for (auto [j, x] : f) {  // 枚举所有以 i 结尾的区间（每项代表一类相同 gcd）
                if (i - j + 1 >= k) {  // 区间长度至少为 k 才合法
                    ans = max(ans, (s[i + 1] - s[j]) * x);  // 用前缀和求出区间和，乘以 gcd 后更新最大值
                }  // 长度判断结束
            }  // 枚举区间结束
        }  // 右端点枚举结束
        return ans;  // 返回最大的 gcd 与区间和之积
    }  // 方法结束
};  // 类结束