// 题目：2830. 销售利润最大化（Maximize the Profit as the Salesman）
// 思路：把报价按结束位置排序后做线性 DP：f[i] 表示前 i 条报价能拿到的最大利润，转移时二分出所有结束位置早于当前报价起点的报价数量 j，在「不做当前报价」与「做当前报价」之间取较大值。
// 时间复杂度：O(m log m)，m 为报价条数，排序与每次 lower_bound 都是这个量级；空间复杂度：O(m)，排序后的报价数组、结束位置数组 g 与 DP 数组 f 各占 O(m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {  // n：房屋数量（本解法未直接使用）；offers：每项为 {起点, 终点, 利润}
        sort(offers.begin(), offers.end(), [](const vector<int>& a, const vector<int>& b) {  // 按报价的结束位置（下标 1）升序排序
            return a[1] < b[1];  // 结束位置更小的报价排在前面，保证 DP 依赖的区间顺序
        });  // 排序结束，offers 现在按结束位置单调不减
        n = offers.size();  // 复用参数 n 表示报价条数，便于后面书写 DP 边界
        vector<int> f(n + 1);  // f[i]：只考虑前 i 条报价时的最大利润，元素默认初始化为 0
        vector<int> g;  // g 依次保存每条报价的结束位置，用于二分定位不冲突的前缀
        for (auto& o : offers) {  // 遍历排序后的所有报价
            g.push_back(o[1]);  // 取出结束位置，使 g 与 offers 顺序一致且单调不减
        }  // g 构造完成
        for (int i = 1; i <= n; ++i) {  // 依次计算 f[1] 到 f[n]
            auto o = offers[i - 1];  // 当前要决策的报价（offers 下标从 0 开始，故用 i-1）
            int j = lower_bound(g.begin(), g.end(), o[0]) - g.begin();  // 第一个结束位置 >= 当前起点的下标，它之前（共 j 条）的报价都与当前报价时间不重叠
            f[i] = max(f[i - 1], f[j] + o[2]);  // 二选一取较大：放弃当前报价（f[i-1]）或接下当前报价（前 j 条的最优值加上本条利润 o[2]）
        }
        return f[n];  // 前 n 条报价的最优利润即为答案
    }
};