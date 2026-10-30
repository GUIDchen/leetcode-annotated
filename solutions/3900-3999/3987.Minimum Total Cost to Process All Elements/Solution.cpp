// 题目：3987. Minimum Total Cost to Process All Elements（3987. 处理所有元素的成本）
// 核心思路：贪心模拟。维护当前资源 cur（初值 k），处理每个元素 x 时若 cur < x，则再执行 ceil((x-cur)/k) 次补充操作恰好够用；第 i 次操作成本为 i，于是总成本是 1+2+…+cnt = cnt·(cnt+1)/2。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公开接口
    int minimumCost(vector<int>& nums, int k) {  // 返回按顺序处理完所有元素的最小总成本
        const int MOD = 1'000'000'007;  // 取模常量 1e9+7（数字分隔符写法等价于 1000000007）
        long long cnt = 0;  // cnt 记录已经执行过的补充操作次数
        long long cur = k;  // cur 为当前可用资源，初始是 k

        for (int x : nums) {  // 按顺序处理每个元素
            long long diff = (long long) x - cur;  // diff 为处理当前元素所需的资源缺口
            if (diff > 0) {  // 资源不足，必须执行一次或多次补充操作
                long long m = (diff + k - 1LL) / k;  // 向上取整得到至少需要的补充次数 m
                cur += m * k;  // 补充后资源增加 m·k
                cnt += m;  // 操作次数累加，用于后续计算成本
            }  // if 分支结束
            cur -= x;  // 支付 x 单位资源处理当前元素
        }  // 遍历结束

        cnt %= MOD;  // 先取模，避免后面乘法溢出
        return (cnt + 1) * cnt / 2 % MOD;  // 总成本为 1+2+…+cnt = cnt·(cnt+1)/2，再取模
    }  // 方法结束
};  // 类定义结束