// 题目：2431. 最大限度地提高购买水果的口味（Maximize Total Tastiness of Purchased Fruits）
// 思路：记忆化搜索，dfs(i, j, k) 表示从第 i 个水果开始、剩余预算 j、剩余优惠券 k 时能取得的最大口味值。
// 时间复杂度：O(n * maxAmount * maxCoupons)，每个状态只算一次；空间复杂度：O(n * maxAmount * maxCoupons)，记忆化数组开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxTastiness(vector<int>& price, vector<int>& tastiness, int maxAmount, int maxCoupons) {  // price：各水果价格；tastiness：各水果口味值；maxAmount：预算；maxCoupons：优惠券张数
        int n = price.size();  // 水果总数，也是递归的终点下标
        memset(f, 0, sizeof f);  // 记忆化数组清零；0 表示该状态尚未计算过
        function<int(int i, int j, int k)> dfs;  // 先声明函数对象，便于在 lambda 内部递归调用自己
        dfs = [&](int i, int j, int k) {  // i：当前水果下标；j：剩余预算；k：剩余优惠券张数
            if (i == n) return 0;  // 所有水果都已决策完，再买不到东西，收益为 0
            if (f[i][j][k]) return f[i][j][k];  // 该状态已计算过，直接返回缓存值（剪枝）
            int ans = dfs(i + 1, j, k);  // 方案一：跳过第 i 个水果，预算与券都不变
            if (j >= price[i]) ans = max(ans, dfs(i + 1, j - price[i], k) + tastiness[i]);  // 方案二：原价买下，扣掉 price[i] 并累加口味值
            if (j >= price[i] / 2 && k) ans = max(ans, dfs(i + 1, j - price[i] / 2, k - 1) + tastiness[i]);  // 方案三：用一张券半价买，花费 price[i] / 2（整除向下取整与题意一致）
            f[i][j][k] = ans;  // 把当前状态的最优解写入记忆化数组
            return ans;  // 返回该状态的最优口味值
        };
        return dfs(0, maxAmount, maxCoupons);  // 从第 0 个水果、满预算、满优惠券开始搜索
    }

private:  // 内部数据成员，不对外暴露
    int f[101][1001][6];  // 记忆化数组，三维上界取自题目数据范围（水果数 ≤ 100、金额 ≤ 1000、优惠券 ≤ 5）
};