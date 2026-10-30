// 题目：2954. 统计感冒序列的数目（Count the Number of Infection Sequences）
// 思路：把未感染人群按已感染位置切成若干段；答案是未感染全排列 s! 除以各段内部顺序 x!，中间段再乘 2^(x-1) 表示两侧先感染的先后选择。
// 时间复杂度：O(n + m log MOD)，预处理阶乘加若干次快速幂；空间复杂度：O(n)，阶乘表。
const int MX = 1e5;  // 阶乘预计算的上界（n 最大 1e5）
const int MOD = 1e9 + 7;  // 取模常量
int fac[MX + 1];  // fac[i] 保存 i! % MOD，全局共享避免重复计算

auto init = [] {  // 全局 lambda：程序启动时立刻执行，完成阶乘表预计算
    fac[0] = 1;  // 0! = 1，递推的起点
    for (int i = 1; i <= MX; ++i) {  // 从 1 一直算到 MX
        fac[i] = 1LL * fac[i - 1] * i % MOD;  // 用 long long 中转防止乘法溢出后再取模
    }  // 递推循环结束
    return 0;  // 返回值只为了给 init 一个非 void 类型
}();  // 就地调用该 lambda，触发预计算

int qpow(long long a, long long n) {  // 快速幂：计算 a^n % MOD
    long long ans = 1;  // 累乘结果，从 1 开始
    for (; n > 0; n >>= 1) {  // 逐位处理指数 n
        if (n & 1) {  // 当前二进制位为 1 时把 a 乘进答案
            ans = (ans * a) % MOD;  // 累乘并取模
        }  // if 分支结束
        a = (a * a) % MOD;  // 底数平方，准备处理下一位
    }  // 指数位移循环结束
    return ans;  // 返回 a^n % MOD
}  // qpow 函数结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSequence(int n, vector<int>& sick) {  // n：总人数；sick：初始已感染者的下标；返回可能的感染序列数目
        int m = sick.size();  // 初始已感染人数
        vector<int> nums(m + 1);  // nums 保存每段连续未感染人群的长度，共 m+1 段

        nums[0] = sick[0];  // 第一个感染者左边的未感染人数
        nums[m] = n - sick[m - 1] - 1;  // 最后一个感染者右边的未感染人数
        for (int i = 1; i < m; i++) {  // 遍历相邻两个感染者之间的空隙
            nums[i] = sick[i] - sick[i - 1] - 1;  // 两者之间的未感染人数
        }  // 空隙遍历结束

        int s = accumulate(nums.begin(), nums.end(), 0);  // 累计所有未感染人数
        long long ans = fac[s];  // 先取未感染人群的全排列 s!
        for (int x : nums) {  // 逐段扣除段内的排列重复
            if (x > 0) {  // 长度大于 0 的段才需要处理
                ans = ans * qpow(fac[x], MOD - 2) % MOD;  // 乘上 x! 的逆元（费马小定理），等价于除以 x!
            }  // if 分支结束
        }  // 循环结束
        for (int i = 1; i < nums.size() - 1; ++i) {  // 只剩中间段：它们被两侧的感染者夹住，存在混合的感染顺序
            if (nums[i] > 1) {  // 长度大于 1 时才有先感染哪一侧的选择
                ans = ans * qpow(2, nums[i] - 1) % MOD;  // 每段贡献 2^(x-1) 种内部顺序
            }  // if 分支结束
        }  // 循环结束
        return ans;  // 返回感染序列总数
    }  // 方法结束
};  // 类定义结束