// 题目：2961. 双模幂运算（Double Modular Exponentiation）
// 思路：用一个快速幂函数按公式依次计算 (a^b mod 10)^c mod m，与 target 比较，相等就把下标加入答案。
// 时间复杂度：O(n * (log b + log c))，每个四元组做两次快速幂；空间复杂度：O(1)，除答案数组外只用常数空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {  // variables 每项为 [a, b, c, m]，target 为目标值
        vector<int> ans;  // 保存所有满足条件的下标
        auto qpow = [&](long long a, int n, int mod) {  // 快速幂 lambda：返回 a^n mod mod，a 用 long long 防止乘法溢出
            long long ans = 1;  // 幂的累积结果，初始为 1
            for (; n; n >>= 1) {  // 指数每次右移一位，直到为 0
                if (n & 1) {  // 当前最低位为 1，需要把这一份 a 乘进来
                    ans = ans * a % mod;  // 乘入并取模
                }  // 最低位判断结束
                a = a * a % mod;  // a 自乘，为下一位的权重做准备
            }  // 指数循环结束
            return (int) ans;  // 转回 int 返回
        };  // lambda 定义结束
        for (int i = 0; i < variables.size(); ++i) {  // 依次处理每个四元组
            auto e = variables[i];  // 取出当前四元组
            int a = e[0], b = e[1], c = e[2], m = e[3];  // 拆出 a、b、c、m
            if (qpow(qpow(a, b, 10), c, m) == target) {  // 先算 a^b mod 10，再算它的 c 次方 mod m
                ans.push_back(i);  // 与 target 相等则记录下标
            }  // 条件判断结束
        }  // 四元组循环结束
        return ans;  // 返回所有好下标
    }  // 方法体结束
};  // 题解类结束