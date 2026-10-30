// 题目：2438. 二的幂数组中查询范围内的乘积（Range Product Queries of Powers）
// 思路：用 lowbit（n & -n）不断剥出最低位的 1，得到从小到大的 2 的幂数组；再对每个查询区间累乘并取模。
// 时间复杂度：O(log n + Σ(r-l+1))，分解与查询分别线性；空间复杂度：O(log n)，powers 最多存 log2(n)+1 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> productQueries(int n, vector<vector<int>>& queries) {  // n：被分解的正整数；queries：若干 [l, r] 查询区间
        vector<int> powers;  // 存放 n 的二进制分解出的所有 2 的幂，从小到大
        while (n) {  // 只要 n 还有剩余的二进制位就继续剥
            int x = n & -n;  // lowbit：取出最低位的 1 所代表的 2 的幂
            powers.push_back(x);  // 按从小到大的顺序把这个幂追加到数组
            n -= x;  // 从 n 中去掉这一位，保证下一轮取到更高的位
        }  // 分解循环结束
        vector<int> ans;  // 保存每个查询对应的答案
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        for (const auto& q : queries) {  // 依次处理每个查询区间
            int l = q[0], r = q[1];  // 取出区间左右端点（闭区间）
            long long x = 1;  // 区间乘积的累乘器，用 long long 避免中间结果溢出
            for (int j = l; j <= r; ++j) {  // 遍历区间内的每个 2 的幂
                x = x * powers[j] % mod;  // 边乘边取模，保证结果不溢出
            }  // 区间内循环结束
            ans.push_back(x);  // 记录本查询的乘积
        }  // 查询循环结束
        return ans;  // 返回所有查询的结果
    }  // productQueries 方法结束
};  // 类定义结束
