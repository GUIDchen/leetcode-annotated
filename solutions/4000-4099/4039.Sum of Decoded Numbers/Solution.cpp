// 题目：4039. 解码值之和 / Sum of Decoded Numbers
// 核心思路：把每个编码值拆成底数部分与最后一位的切分位置，切片得到底数与指数后，用快速幂求值并累加取模
// 复杂度：时间复杂度 O(n log y)，空间复杂度 O(log v)
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    int sumDecoded(vector<long long>& nums) {  // 对每个编码值解码后求幂，返回所有结果之和取模的值
        const long long mod = 1000000007;  // 取模常量
        long long ans = 0;  // 答案累加器

        for (long long v : nums) {  // 逐个处理编码值 v
            long long d = v / 10;  // 去掉最后一位得到底数部分 d
            int w = v % 10;  // 最后一位就是切分位置 w

            string s = to_string(d);  // 底数部分转成字符串，便于按下标切分
            long long x = stoll(s.substr(0, w));  // 前 w 位作为底数 x
            long long y = stoll(s.substr(w));  // 剩余位作为指数 y

            ans = (ans + qpow(x, y, mod)) % mod;  // 把 x 的 y 次幂对 mod 取模后累加到答案
        }  // 结束编码值遍历

        return ans;  // 返回解码值之和对 mod 取模的结果
    }  // 结束方法

private:  // 私有辅助函数
    long long qpow(long long x, long long y, long long mod) {  // 快速幂：计算 x^y mod mod
        long long res = 1;  // 结果初始化为 1
        while (y) {  // 指数未归零时继续迭代
            if (y & 1) {  // 当前二进制最低位为 1 时把 x 乘进结果
                res = res * x % mod;  // 累乘并取模
            }  // 结束该二进制位判断
            x = x * x % mod;  // 底数平方，对应指数右移一位
            y >>= 1;  // 指数右移一位
        }  // 结束快速幂循环
        return res;  // 返回幂值
    }  // 结束快速幂函数
};  // 结束类定义
