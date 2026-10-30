// 3770. 可表示为连续质数和的最大质数 / Largest Prime from Consecutive Prime Sum
// 核心思路：先用埃氏筛求出 5×10^5 以内的全部质数，再把从 2 开始的连续质数累加和中本身为质数的值收集成升序表，最后二分查表。
// 复杂度：时间 O(MX·log log MX + log MX)，空间 O(MX)。
static const int MX = 500000;  // 预处理上界
static vector<bool> IS_PRIME(MX + 1, true);  // 埃氏筛的质数标记数组
static vector<int> PRIMES;  // 质数列表
static vector<int> S;  // 结果表：可表示为连续质数和且本身为质数的数（升序）

auto init = [] {  // 用 lambda 在程序启动前完成一次性预处理
    IS_PRIME[0] = false;  // 0 不是质数
    IS_PRIME[1] = false;  // 1 不是质数

    for (int i = 2; i <= MX; i++) {  // 埃氏筛主循环
        if (IS_PRIME[i]) {  // i 是质数
            PRIMES.push_back(i);  // 记录该质数
            if (1LL * i * i <= MX) {  // 仅在 i*i 不越界时才需要划掉倍数
                for (int j = i * i; j <= MX; j += i) {  // 从 i*i 开始划掉 i 的所有倍数
                    IS_PRIME[j] = false;  // 标记为合数
                }
            }
        }
    }

    S.push_back(0);  // 结果表以 0 开头，保证 n 很小时也能取到合法值
    int t = 0;  // 连续质数的累加和
    for (int x : PRIMES) {  // 依次累加每个质数
        t += x;  // 累加当前质数
        if (t > MX) break;  // 累加和超过上界，后续只会更大，停止
        if (IS_PRIME[t]) {  // 累加和本身也是质数
            S.push_back(t);  // 记录该质数
        }
    }

    return 0;  // lambda 的返回值，仅用于满足静态初始化
}();

class Solution {  // 定义解法类
public:  // 公有方法区
    int largestPrime(int n) {  // 求不超过 n 的最大“可表示为连续质数和”的质数
        auto it = upper_bound(S.begin(), S.end(), n);  // 找到第一个大于 n 的位置
        return *(it - 1);  // 它前一个元素就是答案
    }  // 方法结束
};  // 类结束
