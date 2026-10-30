// 题目：3312. 查询排序后的最大公约数（Sorted GCD Pair Queries）
// 思路：从大到小枚举 g，先由「能被 g 整除的元素个数」算出 gcd 是 g 的倍数的数对总数 C(v,2)，再减去所有更大倍数上已统计好的数对，得到 gcd 恰为 g 的数对个数；接着做前缀和，使 cntG[g] 表示 gcd <= g 的数对个数，最后对每个查询二分出第一个前缀和大于 q 的下标。
// 复杂度：时间 O(M log M + q log M)，M = max(nums)，枚举倍数部分是调和级数；空间 O(M)，两个长度为 M+1 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {  // nums：原数组；queries：在所有两两 gcd 升序排成的序列中的下标（从 0 开始）
        int mx = ranges::max(nums);  // 数组最大值，决定计数数组的长度
        vector<int> cnt(mx + 1);  // cnt[v]：数值 v 在 nums 中出现的次数
        vector<long long> cntG(mx + 1);  // cntG[g]：先存 gcd 恰为 g 的数对个数，后面会被就地改成前缀和
        for (int x : nums) {  // 统计每个数值的出现次数
            ++cnt[x];  // 值 x 的出现次数加一
        }  // for 循环结束
        for (int i = mx; i; --i) {  // 从大到小枚举 g，保证算 g 时它的所有倍数都已处理完
            long long v = 0;  // v：nums 中能被 g 整除的元素个数
            for (int j = i; j <= mx; j += i) {  // 枚举 g 的所有倍数 j
                v += cnt[j];  // 累加这些倍数在数组中出现的次数
                cntG[i] -= cntG[j];  // 减去 gcd 恰为更大倍数 j 的数对，剩下的才是 gcd 恰为 g 的
            }  // 内层 for 循环结束
            cntG[i] += 1LL * v * (v - 1) / 2;  // 先加上「gcd 是 g 的倍数」的数对总数，即从 v 个元素里选两个的组合数
        }  // 外层 for 循环结束
        for (int i = 2; i <= mx; ++i) {  // 把 cntG 就地转成前缀和：cntG[i] 变为 gcd <= i 的数对个数
            cntG[i] += cntG[i - 1];  // 累加上前一项的前缀和
        }  // for 循环结束
        vector<int> ans;  // 保存每个查询的答案
        for (auto&& q : queries) {  // 逐个处理查询 q
            ans.push_back(upper_bound(cntG.begin(), cntG.end(), q) - cntG.begin());  // 找到第一个前缀和大于 q 的下标，正好等于第 q 个（0 起始）gcd 的值；下标 0、1 的前缀和恒为 0，天然对齐
        }  // for 循环结束
        return ans;  // 返回所有查询的结果
    }  // 方法结束
};  // 类定义结束
