// 3653. 区间乘法查询后的异或 I（XOR After Range Multiplication Queries I）
// 核心思路：直接按题意模拟每个查询，从 l 开始以 k 为步长把区间内的元素乘上 v 并取模，最后把整个数组异或起来。
// 复杂度：时间 O(Σ((r-l)/k + 1))，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有接口
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {  // 依次执行所有查询，返回最终数组所有元素的异或值
        const int mod = 1e9 + 7;  // 取模常量 10^9 + 7
        for (const auto& q : queries) {  // 遍历每个查询
            int l = q[0], r = q[1], k = q[2], v = q[3];  // 拆出区间左端点 l、右端点 r、步长 k、乘数 v
            for (int idx = l; idx <= r; idx += k) {  // 从 l 开始按步长 k 枚举区间内的下标（l + t*k <= r）
                nums[idx] = 1LL * nums[idx] * v % mod;  // 该位置乘上 v 并取模；用 1LL 提升为 long long 防止溢出
            }  // 本次查询的下标枚举结束
        }  // 查询处理结束
        int ans = 0;  // 异或结果从 0 开始
        for (int x : nums) {  // 遍历最终数组
            ans ^= x;  // 逐个异或累加
        }  // 遍历结束
        return ans;  // 返回所有元素的异或值
    }  // xorAfterQueries 结束
};  // 类定义结束
