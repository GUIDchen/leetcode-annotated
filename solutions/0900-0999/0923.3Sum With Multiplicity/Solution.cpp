// 题目：923. 三数之和的多种可能（3Sum With Multiplicity）
// 思路：值域只有 0..100，用计数数组代替哈希表；固定 j 后扣掉自身，使 cnt 只统计下标大于 j 的后缀，再枚举 i<j 查补数 c 的个数。
// 时间复杂度：O(n^2)，双重枚举 i、j；空间复杂度：O(V)，V=101 为值域大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int threeSumMulti(vector<int>& arr, int target) {  // arr：原数组；target：三数之和的目标值
        const int mod = 1e9 + 7;  // 题目要求结果对 1e9+7 取模
        int cnt[101]{};  // 值域是 [0,100]，用计数数组统计每个值出现次数，{} 保证全部初始化为 0
        for (int x : arr) {  // 先遍历一遍数组，统计全量频次
            ++cnt[x];  // 数值 x 的计数加一
        }  // 统计结束
        int n = arr.size();  // n 是数组长度，供后面的双重循环使用
        int ans = 0;  // 累计满足 arr[i]+arr[j]+arr[k]==target 的下标三元组个数
        for (int j = 0; j < n; ++j) {  // 固定中间下标 j，从前往后枚举
            --cnt[arr[j]];  // 先把 arr[j] 自己从计数中扣掉，使 cnt 只代表下标 > j 的后缀
            for (int i = 0; i < j; ++i) {  // 枚举 i < j，保证 i<j<k 的下标顺序
                int c = target - arr[i] - arr[j];  // 由 a+b+c=target 反解第三个数 c
                if (c >= 0 && c <= 100) {  // c 必须落在值域内，才可能出现在数组中
                    ans = (ans + cnt[c]) % mod;  // 后缀里每个等于 c 的下标都能构成一组，累加后取模
                }  // 内层 if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        return ans;  // 返回取模后的方案总数
    }  // 方法结束
};  // 类定义结束