// 题目：3233. 统计不是特殊数字的数字数量（Find the Count of Numbers Which Are Not Special）
// 思路：特殊数字恰好是素数的平方。先用埃氏筛预处理到 sqrt(1e9) 的素数表，再数出 [l, r] 中平方根为素数的个数，用区间长度减掉它。
// 时间复杂度：预处理 O(√R log log √R)，单次查询 O(√R)；空间复杂度：O(√R)，用于存放素数表。
const int m = 31623;  // sqrt(1e9) 的上取整，筛表规模上限
bool primes[m + 1];  // primes[i] 表示 i 是否为素数；全局数组默认零初始化

auto init = [] {  // 用立即执行的 lambda 在程序启动时建好筛表
    memset(primes, true, sizeof(primes));  // 先把所有数都标记为素数
    primes[0] = primes[1] = false;  // 0 和 1 都不是素数
    for (int i = 2; i <= m; ++i) {  // 埃拉托斯特尼筛：从小到大枚举每个数
        if (primes[i]) {  // 只有素数才需要去筛它的倍数
            for (int j = i * 2; j <= m; j += i) {  // 从 2i 开始，把所有 i 的倍数标记掉
                primes[j] = false;  // j 是 i 的倍数，标记为合数
            }  // 内层循环结束
        }  // 素数分支结束
    }  // 外层循环结束
    return 0;  // lambda 需要一个返回类型，这里随意返回 0
}();  // 立即调用，保证静态初始化阶段就完成筛表

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int nonSpecialCount(int l, int r) {  // 统计区间 [l, r] 中不是“特殊数字”的个数
        int lo = ceil(sqrt(l));  // 特殊数字形如 p²，其平方根的下界
        int hi = floor(sqrt(r));  // 特殊数字形如 p²，其平方根的上界
        int cnt = 0;  // 区间内特殊数字的个数
        for (int i = lo; i <= hi; ++i) {  // 枚举所有可能的素数底数
            if (primes[i]) {  // 底数是素数时，i² 才是特殊数字
                ++cnt;  // 计入一个特殊数字
            }  // 判断结束
        }  // 循环结束
        return r - l + 1 - cnt;  // 区间总个数减去特殊数字个数，即答案
    }  // 方法结束
};  // 类定义结束