// 题目：4041. 构造子集和的最少操作次数 II（Minimum Operations to Form Subset Sum II）
// 思路：0-1 背包 DP，f[w] 表示凑出子集和 w 的最少操作次数；对每个数 x 逆序枚举容量 w，外层只用「翻倍 x*2^i」，内层再嵌套「先减半 i 次、后翻倍 j 次」得 floor(x/2^i)*2^j，两者代价分别为 i 与 i+j。
// 复杂度：时间复杂度 O(n * sum * log^2(sum))，n 为 nums 长度；空间复杂度 O(sum)，即 DP 数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int sum) {  // nums：可选数字；sum：目标和；返回最少操作次数，无法达成返回 -1
        const int inf = 1e9;  // 无穷大，表示该和暂时不可达
        vector<int> f(sum + 1, inf);  // f[w]：凑出子集和 w 所需的最少操作次数
        f[0] = 0;  // 边界：凑出 0 不需要任何操作

        for (int x : nums) {  // 依次枚举每个可选数字（每个数最多用一次）
            for (int w = sum; w >= 0; --w) {  // 逆序枚举容量，保证本轮不会重复使用同一个数
                for (int i = 0, y = x; y <= w; i++, y *= 2) {  // 只翻倍的分支：y = x * 2^i，代价为 i
                    f[w] = min(f[w], f[w - y] + i);  // 用 y 填 w-y 这部分，总代价 = 凑 w-y 的代价 + i
                }  // 只翻倍的循环结束

                for (int i = 1, y = x / 2; y > 0; i++, y /= 2) {  // 先减半 i 次：y = floor(x / 2^i)，代价为 i
                    for (int j = 0, z = y; z <= w; j++, z *= 2) {  // 再在 y 的基础上翻倍 j 次：z = y * 2^j，代价为 j
                        f[w] = min(f[w], f[w - z] + i + j);  // 总代价 = 凑 w-z 的代价 + i + j
                    }  // 内层翻倍的循环结束
                }  // 减半枚举行的循环结束
            }  // 容量 w 的枚举结束
        }  // 数字 x 的枚举结束

        return f[sum] < inf ? f[sum] : -1;  // 可达就返回最小代价，否则返回 -1
    }  // 方法结束
};  // 题解类结束
