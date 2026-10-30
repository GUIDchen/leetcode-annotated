// 题目：3333. 找到初始输入字符串 II（Find the Original Typed String II）
// 思路：先把字符串切成连续相同字符的段，各段长度的乘积是总方案数；段数不足 k 时，再用前缀和优化的 DP 统计“长度小于 k”的非法方案，总数减去非法数即为答案。
// 时间复杂度：O(n + m·k)，m 为段数；空间复杂度：O(m·k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int possibleStringCount(string word, int k) {  // word 是最终输入串，k 是初始串长度的下界；返回可能的初始串数量
        const int mod = 1e9 + 7;  // 取模常量，防止结果溢出
        vector<int> nums;  // nums 保存每段“最多能少写”的字符数，即段长减一
        long long ans = 1;  // ans 先记录不考虑长度下界时的总方案数
        int cur = 0;  // 当前连续段的长度计数
        int n = word.size();  // 字符串长度

        for (int i = 0; i < n; ++i) {  // 一次扫描，把字符串切成若干连续相同字符的段
            cur++;  // 当前段长度加一
            if (i == n - 1 || word[i] != word[i + 1]) {  // 到达串尾或字符发生变化，说明当前段结束
                if (cur > 1) {  // 段长大于 1 才说明有多打出来的字符可删
                    if (k > 0) {  // 只有仍受长度下界约束时才记录该段余量
                        nums.push_back(cur - 1);  // 该段最多可以少写 cur-1 个字符
                    }  // 内层 if 结束
                    ans = ans * cur % mod;  // 该段有 cur 种可能的原始长度，累乘进总方案数
                }  // 段长判断结束
                cur = 0;  // 重置计数，准备统计下一段
                k--;  // 每结束一段 k 减一，扫描完后 k 表示“下界与段数之差”
            }  // 当前段处理结束
        }  // 扫描结束

        if (k < 1) {  // 剩余计数小于 1 说明段数已达到下界，所有方案都合法
            return ans;  // 直接返回总方案数
        }  // 提前返回结束

        int m = nums.size();  // m 是连续段的个数
        vector<vector<int>> f(m + 1, vector<int>(k, 0));  // f[i][j]：前 i 段一共只产生 j 个字符（j < k）的方案数，即非法方案
        f[0][0] = 1;  // 空前缀产生 0 个字符，方案数为 1

        for (int i = 1; i <= m; ++i) {  // 逐段递推
            int x = nums[i - 1];  // 第 i 段最多可以少写 x 个字符
            vector<long long> s(k + 1, 0);  // 前缀和数组 s，s[j] 表示 f[i-1][0..j-1] 之和
            for (int j = 0; j < k; ++j) {  // 计算前缀和
                s[j + 1] = (s[j] + f[i - 1][j]) % mod;  // s[j+1] 就是前 j+1 项之和
            }  // 前缀和计算结束
            for (int j = 0; j < k; ++j) {  // 枚举前 i 段产生的总字符数 j
                int l = max(0, j - x);  // 合法下界 l：第 i 段至少要贡献 j-x 个字符
                f[i][j] = (s[j + 1] - s[l] + mod) % mod;  // 用前缀和做区间求和，得到总长度为 j 的非法方案数
            }  // 区间求和结束
        }  // 逐段递推结束

        long long sum = 0;  // sum 累加所有“总长度不足 k”的非法方案
        for (int j = 0; j < k; ++j) {  // 枚举总长度 j
            sum = (sum + f[m][j]) % mod;  // 累加非法方案数并取模
        }  // 累加结束

        return (ans - sum + mod) % mod;  // 总方案数减去非法方案，加 mod 防止出现负数
    }  // 方法结束
};  // 类定义结束
