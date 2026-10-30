// 题目：2931. 购买物品的最大开销（Maximum Spending After Buying Items）
// 思路：每行价格从左到右递增，用最小堆做多路归并，每次取全局最便宜的物品，第 d 天取到的价格乘以 d 累加。
// 时间复杂度：O(mn log m)，m 行 n 列、堆中最多同时存在 m 个元素；空间复杂度：O(m)，只额外保存这个堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxSpending(vector<vector<int>>& values) {  // values：m 行 n 列的价格矩阵，每行从左到右递增
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;  // 最小堆，元素为（价格, 行号, 列号），按元组字典序比较即按价格比较
        int m = values.size(), n = values[0].size();  // m：商品行数；n：每行的物品数
        for (int i = 0; i < m; ++i) {  // 初始化：把每行最右端（即每行最贵）的元素放进堆
            pq.emplace(values[i][n - 1], i, n - 1);  // 每行只能从右往左取，所以起点固定是第 n-1 列
        }
        long long ans = 0;  // 累计总开销，用 long long 防止大数相乘溢出
        for (int d = 1; pq.size(); ++d) {  // d 是第几天（从 1 开始），堆空说明所有物品都已买完
            auto [v, i, j] = pq.top();  // 取出当前全局最便宜的价格 v 及其来源行号、列号
            pq.pop();  // 该元素已出堆，准备结算
            ans += 1LL * v * d;  // 第 d 天买它，贡献 v * d，乘 1LL 避免 int * int 溢出
            if (j) {  // 该行左边还有更便宜的物品可以继续取
                pq.emplace(values[i][j - 1], i, j - 1);  // 把同行前一个元素补进堆，保证每行元素按价格顺序被取
            }
        }
        return ans;  // 返回最大总开销
    }
};  // 类定义结束