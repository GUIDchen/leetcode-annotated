// 题目：2963. 统计好分割方案的数目（Count the Number of Good Partitions）
// 思路：先记下每个数字最后出现的位置，再按「段尾最远可达位置」把数组切成 k 个极大段，相同数字不会跨段，答案就是 2^(k-1)。
// 时间复杂度：O(n + log k)，扫描两遍数组外加一次快速幂；空间复杂度：O(n)，哈希表存每个数字的最后下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfGoodPartitions(vector<int>& nums) {  // nums：输入数组；返回把数组切成若干段（同一种数字不能落在不同段）的方案数
        unordered_map<int, int> last;  // 记录每个数字最后出现的位置，用来确定一段至少要延伸到多远
        int n = nums.size();  // 缓存数组长度
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，填充每个数字的最后出现下标
            last[nums[i]] = i;  // 直接覆盖写入，最终留下的就是最新（最后）下标
        }  // for 结束
        const int mod = 1e9 + 7;  // 取模的模数，10^9+7 是常用的大质数
        int j = -1, k = 0;  // j：当前段必须延伸到的最右下标（-1 表示还没开始）；k：极大不可分段的个数
        for (int i = 0; i < n; ++i) {  // 再从左到右扫描一遍，划分出必须整体处理的极大段
            j = max(j, last[nums[i]]);  // 段尾至少要覆盖当前数字的最后出现位置，取历史最大值保证段内不被切开
            k += i == j;  // i 正好等于段尾（i == j 记 1）说明一个极大段在此结束，k 加一
        }  // 扫描结束
        auto qpow = [&](long long a, int n, int mod) {  // 快速幂 lambda：计算 a^n % mod（把指数按二进制拆分）
            long long ans = 1;  // 幂的累积结果，乘法单位元是 1
            for (; n; n >>= 1) {  // 每轮把指数右移一位，直到指数为 0
                if (n & 1) {  // 如果当前最低位是 1，说明这一位对应的幂要乘进答案
                    ans = ans * a % mod;  // 乘入并立刻取模，防止溢出
                }  // if 结束
                a = a * a % mod;  // 底数自乘，对应二进制中的下一位
            }  // for 结束
            return (int) ans;  // 转成 int 返回（题目保证答案在 int 范围内）
        };  // 快速幂 lambda 结束
        return qpow(2, k - 1, mod);  // k 个极大段之间有 k-1 个可切位置，每个位置切或不切，共 2^(k-1) 种方案
    }  // 方法结束
};  // 类定义结束