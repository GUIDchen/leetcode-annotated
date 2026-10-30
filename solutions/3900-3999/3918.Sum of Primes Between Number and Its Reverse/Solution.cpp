// 3918. Sum of Primes Between Number and Its Reverse | 数与其逆序数之间的质数和（中等）
// 核心思路：数值上界只有 1000，先用埃拉托斯特尼筛在全局预处理素数表；单次查询时把 n 的数字逆序得到 r，取 min(n, r) 与 max(n, r) 作为闭区间两端，枚举区间并把素数累加。
// 复杂度：预处理 O(MX log log MX) 时间、O(MX) 空间；每次查询 O(log n + MX) 时间、O(1) 额外空间。
const int MX = 1000;  // 数值上界
bool isPrime[MX + 1];  // 素数标记数组，下标范围 0..MX

auto init = [] {  // 利用全局变量初始化在 main 之前执行一次埃氏筛
    for (int i = 0; i <= MX; ++i) isPrime[i] = true;  // 先把 0..MX 全部标记为素数
    isPrime[0] = isPrime[1] = false;  // 0 和 1 不是素数
    for (int i = 2; i * i <= MX; ++i) {  // 外层只需枚举到 sqrt(MX)
        if (isPrime[i]) {  // i 仍是素数时才用它去筛倍数
            for (int j = i * i; j <= MX; j += i) {  // 从 i*i 开始把所有 i 的倍数划掉（更小的倍数已被更小的素数筛过）
                isPrime[j] = false;  // 标记为合数
            }  // 内层循环结束
        }  // if 结束
    }  // 外层循环结束
    return 0;  // 返回值仅用于给 lambda 一个确定的类型，没有实际含义
}();  // 立即执行这个 lambda，筛表在程序启动时就完成

class Solution {  // 定义题解类
public:  // 公有接口
    int sumOfPrimesInRange(int n) {  // 返回 n 与其逆序数之间（含两端）的所有素数之和
        int r = 0;  // 存放 n 的逆序数
        int tmp = n;  // 用临时变量逐位拆分，保留原数 n
        while (tmp) {  // 还有未处理的数位
            r = r * 10 + tmp % 10;  // 把最低位接到逆序数的末尾
            tmp /= 10;  // 去掉已处理的最低位
        }  // while 结束
        int low = min(n, r);  // 区间左端取 n 与 r 的较小者
        int high = max(n, r);  // 区间右端取 n 与 r 的较大者
        int ans = 0;  // 素数之和
        for (int x = low; x <= high; ++x) {  // 枚举闭区间 [low, high]
            if (isPrime[x]) ans += x;  // 查预处理好的素数表，是素数就累加
        }  // 循环结束
        return ans;  // 返回区间内的素数之和
    }  // 方法结束
};  // 类定义结束
