// 题目：1672. 最富有客户的资产总量（Richest Customer Wealth）
// 思路：每行是一位客户的账户列表，用 accumulate 求行和，再与当前最大值比较。
// 时间复杂度：O(m·n)，每个数字只被累加一次；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumWealth(vector<vector<int>>& accounts) {  // accounts：二维资产表，每一行是一位客户
        int ans = 0;  // 记录最大总资产；资产非负，初值取 0 即可
        for (auto& v : accounts) {  // 逐行遍历每位客户，用引用避免整行拷贝
            ans = max(ans, accumulate(v.begin(), v.end(), 0));  // accumulate 把该行求和，再与 ans 取较大值
        }  // 遍历结束，ans 已覆盖全部客户
        return ans;  // 返回最富有客户的资产总量
    }  // 类定义结束
};