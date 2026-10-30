// 3896. 将数组转换为交替质数数组的最少操作次数 / Minimum Operations to Transform Array into Alternating Prime
// 核心思路：筛出 2e5 以内的质数；偶数下标用二分提升到最近的质数，奇数下标若已是质数则加 1（2 需加 2）使其变成合数。
// 复杂度：时间 O(MX log log MX + n log MX)，空间 O(MX)，其中 MX = 2e5。
class Solution {  // 定义题解类
public:  // 公有接口
    int minOperations(vector<int>& nums) {  // nums 为待变换数组，返回最少操作次数
        int ans = 0;  // 累计所需的最少操作次数
        for (int i = 0; i < nums.size(); ++i) {  // 逐位扫描数组
            int x = nums[i];  // 取出当前下标的原始值
            if ((i & 1) == 0) {  // 偶数下标最终必须是质数（只能单调增大）
                auto it = lower_bound(primes.begin(), primes.end(), x);  // 二分找到第一个不小于 x 的质数
                ans += *it - x;  // 补足到该质数的差值即本位的操作次数
            } else if (isPrime[x]) {  // 奇数下标最终必须是合数，只有原本是质数才需改动
                ans += x == 2 ? 2 : 1;  // 质数加 1 即为合数，x = 2 时须加 2 才得到合数
            }  // 奇数下标处理结束
        }  // 整轮扫描结束
        return ans;  // 返回最少操作次数
    }  // minOperations 结束

private:  // 以下为静态预处理部分（质数表与质数列表）
    static constexpr int MX = 200000;  // 数值上界 2e5，与题目元素范围一致
    inline static vector<bool> isPrime = [] {  // 静态惰性初始化：埃氏筛得到质数标记表
        vector<bool> p(MX + 1, true);  // 先假定 0..MX 全为质数
        p[0] = p[1] = false;  // 0 与 1 不是质数
        for (int i = 2; i <= MX / i; ++i) {  // 只需用不超过 sqrt(MX) 的数去筛
            if (p[i]) {  // i 仍是质数时才用它筛掉倍数
                for (int j = i * i; j <= MX; j += i) {  // 从 i*i 起，步长 i 标记所有倍数
                    p[j] = false;  // 倍数必为合数
                }  // 该质数的倍数筛除结束
            }  // 质数判断结束
        }  // 外层筛法结束
        return p;  // 返回筛好的质数标记表
    }();  // 立即执行 lambda 完成静态初始化

    inline static vector<int> primes = [] {  // 静态惰性初始化：按升序收集全部质数，供二分查找
        vector<int> res;  // 升序质数列表
        for (int i = 2; i <= MX; ++i) {  // 从 2 线性扫描到 MX
            if (isPrime[i]) {  // 只收集质数
                res.push_back(i);  // 记录该质数
            }  // 是质数则收集结束
        }  // 扫描结束
        return res;  // 返回升序质数表
    }();  // 立即执行 lambda 完成静态初始化
};  // Solution 类定义结束
