// 题目：2523. 范围内最接近的两个质数（Closest Prime Numbers in Range）
// 思路：先用线性筛筛出 [2, right] 的所有质数，再在落在 [left, right] 的质数中找相邻差最小的一对。
// 时间复杂度：O(right)，每个合数只被筛一次；空间复杂度：O(right)，标记数组与质数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> closestPrimes(int left, int right) {  // left/right：闭区间上下界，返回区间内最接近的两个质数
        int cnt = 0;  // 已筛出的质数个数，同时作为质数表的下一个写入位置
        bool st[right + 1];  // st[i] 为 true 表示 i 被标记为合数（变长数组，大小 right+1）
        memset(st, 0, sizeof st);  // 整体清零，即先假设 [0, right] 内每个数都是质数
        int prime[right + 1];  // 质数表：按从小到大顺序存放筛出的质数
        for (int i = 2; i <= right; ++i) {  // 线性筛：从 2 枚举到 right，逐个判定 i 是否为质数
            if (!st[i]) {  // 没被标记过，说明 i 是质数
                prime[cnt++] = i;  // 把 i 追加到质数表末尾，并让计数加一
            }  // if 分支结束
            for (int j = 0; prime[j] <= right / i; ++j) {  // 用 i 乘已有的质数去筛合数；用除法避免 prime[j]*i 溢出 int
                st[prime[j] * i] = true;  // prime[j]*i 一定是合数，打上标记
                if (i % prime[j] == 0) {  // prime[j] 是 i 的最小质因子
                    break;  // 此时必须跳出：保证每个合数只被它的最小质因子筛一次
                }  // if 分支结束
            }  // 内层枚举结束
        }  // 筛法结束，[2, right] 内的所有质数都在 prime[0..cnt-1]
        int i = -1, j = -1;  // i 记录首个、j 记录最后一个落在区间内的质数在质数表中的下标
        for (int k = 0; k < cnt; ++k) {  // 顺序扫描质数表（质数表本身递增，因此首尾就是最小与最大）
            if (prime[k] >= left && prime[k] <= right) {  // 只关心落在 [left, right] 闭区间内的质数
                if (i == -1) {  // 第一次遇到区间内的质数
                    i = k;  // 记下左端点的下标
                }  // if 分支结束
                j = k;  // 不断更新，循环结束时 j 就是最右端质数的下标
            }  // if 分支结束
        }  // 扫描结束
        vector<int> ans = {-1, -1};  // 默认答案：区间内凑不出一对时返回 [-1, -1]
        if (i == j || i == -1) return ans;  // 区间内质数不足两个（含一个都没有），直接返回默认答案
        int mi = 1 << 30;  // 记录当前最小间隔，初值取足够大的 2^30
        for (int k = i; k < j; ++k) {  // 只在区间内的质数之间枚举相邻两数，只有相邻质数的差才可能是答案
            int d = prime[k + 1] - prime[k];  // 相邻两个质数的差值
            if (d < mi) {  // 找到更小的间隔
                mi = d;  // 更新最小间隔
                ans[0] = prime[k];  // 记录这对质数中较小的那个
                ans[1] = prime[k + 1];  // 记录这对质数中较大的那个
            }  // if 分支结束
        }  // 枚举结束
        return ans;  // 返回最接近（间隔最小）的一对质数
    }  // 方法结束
};  // 类定义结束