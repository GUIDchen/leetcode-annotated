// 题目：2657. 找到两个数组的前缀公共数组（Find the Prefix Common Array of Two Arrays）
// 核心思路：逐位扩展前缀，同时维护两个数组前缀内各值的出现次数，累加每个值两次出现次数的较小值就是公共元素个数。
// 时间复杂度：O(n^2)，每扩展一位都要扫一遍值域；空间复杂度：O(n)，两个计数数组。
class Solution {  // 题解类
public:  // 方法对外可见
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {  // A、B 都是 1..n 的排列；返回每个前缀的公共元素个数
        int n = A.size();  // 数组长度 n
        vector<int> ans(n);  // ans[i] 存放前 i+1 个位置上的公共元素个数
        vector<int> cnt1(n + 1), cnt2(n + 1);  // 值域为 1..n，分别统计 A、B 前缀中各值的出现次数
        for (int i = 0; i < n; ++i) {  // 逐位扩展前缀
            ++cnt1[A[i]];  // 把 A[i] 计入 A 的前缀频次
            ++cnt2[B[i]];  // 把 B[i] 计入 B 的前缀频次
            for (int j = 1; j <= n; ++j) {  // 枚举所有可能出现的值
                ans[i] += min(cnt1[j], cnt2[j]);  // 值 j 同时出现在两个前缀中时按较少出现次数计入公共元素
            }  // 值域循环结束，第 i 个前缀统计完毕
        }  // 前缀循环结束
        return ans;  // 返回每个前缀的公共元素个数
    }
};  // class Solution 结束