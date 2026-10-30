// 题目：4040. 构造子集和的最少操作次数 I（Minimum Operations to Form Subset Sum I）
// 思路：0-1 背包 DP，f[w] 表示凑出子集和 w 的最少操作次数；对每个数 x 逆序枚举容量 w，分别尝试「翻倍 i 次得 x*2^i」与「减半 i 次得 floor(x/2^i)」两条分支来更新 f[w]。
// 复杂度：时间复杂度 O(n * sum * log(sum))，n 为 nums 长度；空间复杂度 O(sum)，即 DP 数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int sum) {  // nums：可选数字；sum：目标和；返回最少操作次数，无法达成返回 -1
        const int inf = 1e9;  // 无穷大，表示该和暂时不可达
        vector<int> f(sum + 1, inf);  // f[w]：凑出子集和 w 所需的最少操作次数
        f[0] = 0;  // 边界：凑出 0 不需要任何操作

        for (int x : nums) {  // 依次枚举每个可选数字（0-1 背包，每个数最多用一次）
            for (int w = sum; w >= 0; --w) {  // 逆序枚举容量，保证本轮不会重复使用同一个数
                int i = 0, y = x;  // i：对 x 已做的操作次数；y：操作 i 次后得到的值
                while (y <= w) {  // 不断翻倍，直到超过当前容量 w 为止
                    f[w] = min(f[w], f[w - y] + i);  // 用 y 填 w-y 这部分，总代价 = 凑 w-y 的代价 + i 次操作
                    ++i;  // 操作次数加一
                    y <<= 1;  // y 翻倍：x -> 2x -> 4x ...
                }  // 翻倍分支的 while 循环结束

                i = 1;  // 换一条分支：从「减半」开始，i 从 1 计数（0 次就是原值 x，上面已算过）
                y = x >> 1;  // y = floor(x / 2)，即减半 1 次的结果
                while (y > 0) {  // 一直减半，直到值变成 0
                    if (y <= w) {  // 该值不超过剩余容量才可能用上
                        f[w] = min(f[w], f[w - y] + i);  // 用 y 填 w-y 这部分，总代价 = 凑 w-y 的代价 + i 次操作
                    }  // 容量判断分支结束
                    ++i;  // 操作次数加一
                    y >>= 1;  // y 减半：x -> floor(x/2) -> floor(x/4) ...
                }  // 减半分支的 while 循环结束
            }  // 容量 w 的枚举结束
        }  // 数字 x 的枚举结束

        return f[sum] == inf ? -1 : f[sum];  // 目标仍不可达返回 -1，否则返回最少操作次数
    }  // 方法结束
};  // 题解类结束
