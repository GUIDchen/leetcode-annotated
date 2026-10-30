// 题目：2412. 完成所有交易的初始最少钱数（Minimum Money Required Before Transactions）
// 思路：先累加所有亏损交易的钱坑总和 s，再枚举把哪一笔交易放在最后完成，取 s 加该笔所需资金的最大值。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只用了常数个 long long 变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumMoney(vector<vector<int>>& transactions) {  // transactions 每项是 [花费, 回款]
        long long s = 0, ans = 0;  // s 是所有亏损交易的净亏损之和，ans 记录最终答案
        for (auto& e : transactions) {  // 第一趟：统计无法回避的总资金缺口
            s += max(0, e[0] - e[1]);  // 只累加亏损（花费大于回款）的那部分差额
        }
        for (auto& e : transactions) {  // 第二趟：枚举哪一笔交易被安排在最后完成
            if (e[0] > e[1]) {  // 亏损交易放最后：前面的钱坑已计入 s，还需它的回款额作为起步资金
                ans = max(ans, s + e[1]);  // 用该方案更新答案
            } else {  // 盈利交易放最后：只需再备出它自己的花费
                ans = max(ans, s + e[0]);  // 用该方案更新答案
            }
        }
        return ans;  // 返回所需的最小初始钱数
    }
};