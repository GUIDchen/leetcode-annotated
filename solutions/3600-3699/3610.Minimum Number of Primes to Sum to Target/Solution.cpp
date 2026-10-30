// 3610. 目标和所需的最小质数个数 / Minimum Number of Primes to Sum to Target
// 核心思路：先试除已有质数预处理出前 1000 个质数，再把其中最小的 m 个质数当作物品做完全背包，求凑出目标和 n 所需的最少质数个数。
// 复杂度：时间 O(M·π(√M) + m·n)，空间 O(n)；M = 1000。
class Solution {  // 题解类
public:  // 公有接口部分
    int minNumberOfPrimes(int n, int m) {  // 主函数：用最小的 m 个质数凑出目标和 n 的最少个数
        static vector<int> primes;  // 静态质数表，只在第一次调用时构建一次
        if (primes.empty()) {  // 质数表为空说明尚未预处理
            int x = 2;  // 从 2 开始逐个试除
            int M = 1000;  // 需要的前 M 个质数
            while ((int) primes.size() < M) {  // 一直生成到够 M 个质数为止
                bool is_prime = true;  // 先假设当前数 x 是质数
                for (int p : primes) {  // 用已有质数试除
                    if (p * p > x) break;  // 试除因子已超过平方根，说明 x 是质数
                    if (x % p == 0) {  // 能被整除说明不是质数
                        is_prime = false;  // 标记为合数
                        break;  // 无需再试除，直接跳出
                    }  // 条件分支结束
                }  // 试除循环结束
                if (is_prime) primes.push_back(x);  // 确认为质数就收进质数表
                x++;  // 继续检查下一个数
            }  // 预生成循环结束
        }  // 预处理分支结束

        vector<int> f(n + 1, INT_MAX);  // f[i] 表示用前 m 个质数凑出 i 所需的最少质数个数
        f[0] = 0;  // 凑出 0 不需要任何质数
        for (int x : vector<int>(primes.begin(), primes.begin() + m)) {  // 只遍历最小的 m 个质数，每个质数可重复使用（完全背包）
            for (int i = x; i <= n; ++i) {  // 从 x 开始向后推导每个可达的和
                if (f[i - x] != INT_MAX) {  // f[i - x] 可达时才可转移
                    f[i] = min(f[i], f[i - x] + 1);  // 比较“不用这个质数”和“再用一个质数”两种方案
                }  // 条件分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        return f[n] < INT_MAX ? f[n] : -1;  // 不可达时返回 -1，否则返回最少个数
    }  // 主函数结束
};  // 类定义结束
