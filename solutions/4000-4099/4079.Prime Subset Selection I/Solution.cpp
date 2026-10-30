// 4079. 选择质数子集 I（Prime Subset Selection I）
// 核心思路：先用埃氏筛预处理 1e6 以内的质数表，再按升序贪心取质数：只要当前质数不超过 n 且不超过剩余额度 s 就选入，这样个数最多。
// 复杂度：预处理 O(M log log M)（M = 1e6），单次查询 O(答案长度)，空间 O(M)。
class Solution {  // 题解类
    static const int mx = 1000000;  // 筛法上界 1e6
    static vector<int> primes;  // 静态质数表（升序）

public:  // 对外接口
    vector<int> maxPrimes(int n, int s) {  // 在质数不超过 n、所选质数之和不超过 s 的前提下，选出数量尽可能多的质数
        vector<int> ans;  // 选出的质数列表
        for (int p : primes) {  // 按升序尝试每个质数
            if (p > n || p > s) {  // 当前质数超过上限 n，或剩余额度 s 不足以再选它
                break;  // 后面的质数只会更大，同样不行，直接结束
            }  // 条件分支结束
            ans.push_back(p);  // 贪心地选入当前最小的可用质数
            s -= p;  // 扣减已占用的额度
        }  // 遍历结束
        return ans;  // 返回选出的质数列表（升序且个数最多）
    }  // 方法结束
};  // 类定义结束

const int Solution::mx;  // 为 static const 成员在类外提供定义（被 odr 使用时需要）
vector<int> Solution::primes = [] {  // 用 lambda 在程序启动时筛出 1e6 以内的所有质数
    vector<bool> isPrime(mx + 1, true);  // 布尔筛表，初始都标记为质数
    isPrime[0] = isPrime[1] = false;  // 0 和 1 不是质数
    vector<int> primes;  // 本地收集质数

    for (int i = 2; i <= mx; i++) {  // 从小到大扫描每个数
        if (isPrime[i]) {  // i 仍被标记为质数
            primes.push_back(i);  // 把 i 收进质数表
            if (i <= mx / i) {  // 判断 i * i 是否溢出 int
                for (int j = i * i; j <= mx; j += i) {  // 把 i 从 i * i 开始的所有倍数标记为合数
                    isPrime[j] = false;  // 倍数置为合数
                }  // 内层循环结束
            }  // 溢出保护判断结束
        }  // 条件分支结束
    }  // 外层循环结束
    return primes;  // 返回筛出的质数表
}();  // 立即执行上面的 lambda，完成静态成员初始化