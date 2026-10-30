// 题目：1359. 有效的快递序列数目（Count All Valid Pickup and Delivery Options）
// 思路：递推。已有 i-1 份订单的排列时，加入第 i 份订单的取件与送件共有 i*(2i-1) 种插入方式，故 f(i) = f(i-1) * i * (2i-1)。
// 时间复杂度：O(n)，一次循环；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countOrders(int n) {  // 求 n 份订单的合法「取件-送件」序列总数
        const int mod = 1e9 + 7;  // 取模常量，防止中间结果溢出并满足题目要求
        long long f = 1;  // 递推值：n = 1 时只有「取 送」这一种方案
        for (int i = 2; i <= n; ++i) {  // 从已有的 i-1 份订单扩展到 i 份订单
            f = f * i * (2 * i - 1) % mod;  // 新增一对取送共有 i*(2i-1) 个合法插入位置；乘完再取模控制数值范围
        }  // 递推结束
        return f;  // 返回方案数（long long 自动转换为 int）
    }  // countOrders 结束
};  // 类定义结束