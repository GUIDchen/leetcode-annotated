// 题目：2008. 出租车的最大盈利（Maximum Earnings From Taxi）
// 思路：按起点排序后做记忆化搜索：dfs(i) 表示只考虑第 i 单及之后的订单能获得的最大盈利，每次要么跳过第 i 单，要么接单后跳到第一个起点不小于本单终点的订单，两者取较大值。
// 时间复杂度：O(m log m)，每次状态转移二分查找一次；空间复杂度：O(m)，记忆化数组加递归深度。
class Solution {  // LeetCode 约定的题解类
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {  // n 是道路总长度（本题无需用到）；rides[i] = [起点, 终点, 小费]；返回能获得的最大盈利
        sort(rides.begin(), rides.end());  // 按起点升序排序，才能对「下一个可接的订单」做二分查找
        int m = rides.size();  // m 是订单总数
        long long f[m];  // f[i] 记忆化：从第 i 单开始能获得的最大盈利，-1 表示还没算过
        memset(f, -1, sizeof(f));  // 用 -1 填满整个记忆化数组，long long 全 1 的位模式正好是 -1
        function<long long(int)> dfs = [&](int i) -> long long {  // 记忆化搜索：dfs(i) 表示只考虑第 i 单及之后订单时的最大盈利
            if (i >= m) {  // 下标越界说明后面没有订单可接
                return 0;  // 递归边界：盈利为 0
            }  // if (i >= m) 结束
            if (f[i] != -1) {  // 之前已经算过，直接复用缓存
                return f[i];  // 返回缓存值，避免重复搜索
            }  // if (f[i] != -1) 结束
            auto& r = rides[i];  // 取出当前订单，后面反复使用它的字段
            int st = r[0], ed = r[1], tip = r[2];  // st/ed 是起点与终点，tip 是这一单额外获得的小费
            int j = lower_bound(rides.begin() + i + 1, rides.end(), ed, [](auto& a, int val) { return a[0] < val; }) - rides.begin();  // 二分找第一个起点不小于 ed 的订单下标 j：下一单必须在本次行程结束之后才出发；自定义比较器按起点比较
            return f[i] = max(dfs(i + 1), dfs(j) + ed - st + tip);  // 两种选择取较大值：不接第 i 单，或接单后跳到 j，本次盈利为 ed - st + tip；顺带写入记忆化数组
        };  // lambda 定义结束
        return dfs(0);  // 从第 0 单开始搜索全局最优解
    }  // maxTaxiEarnings 方法结束
};  // Solution 类结束
