// 题目：3155. 可升级服务器的最大数量（Maximum Number of Upgradable Servers）
// 核心思路：第 i 类服务器若升级 k 台就卖出 count[i]-k 台，需满足 money[i]+(count[i]-k)*sell[i] >= k*upgrade[i]，解出 k 的上界后与 count[i] 取 min；各类服务器互不影响。
// 时间复杂度：O(n)，n 为服务器种类数，每类只做一次除法；空间复杂度：O(n)，仅答案数组（不计输入）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxUpgrades(vector<int>& count, vector<int>& upgrade, vector<int>& sell, vector<int>& money) {  // count：每类服务器的数量；upgrade/sell：升级成本与旧服务器售价；money：可用资金
        int n = count.size();  // 服务器种类数，也是答案数组的长度
        vector<int> ans;  // 依次存放每一类服务器最多能升级的台数
        for (int i = 0; i < n; ++i) {  // 逐类独立计算，类与类之间互不影响
            ans.push_back(min(count[i], (int) ((1LL * count[i] * sell[i] + money[i]) / (upgrade[i] + sell[i]))));  // 由 money+(cnt-k)*sell >= k*upgrade 解出 k 的上界；1LL 把乘法提升到 64 位以防溢出
        }  // 本类服务器计算完毕
        return ans;  // 返回每类服务器最多可升级的台数
    }  // 方法结束
};  // 类定义结束