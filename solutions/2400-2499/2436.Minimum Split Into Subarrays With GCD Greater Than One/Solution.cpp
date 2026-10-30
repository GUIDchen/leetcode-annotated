// 题目：2436. 使子数组最大公约数大于一的最小分割数（Minimum Split Into Subarrays With GCD Greater Than One）
// 思路：贪心。从左到右把能放进同一段的元素合并求 gcd，一旦 gcd 变成 1 就必须在此处切一刀，并把新段重置为当前元素。
// 时间复杂度：O(n*log V)，每个元素做一次 gcd，V 是数值大小；空间复杂度：O(1)，只用了几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSplits(vector<int>& nums) {  // nums：输入数组，返回满足「每段 gcd > 1」的最少段数
        int ans = 1, g = 0;  // ans：当前已开的段数（至少一段）；g：当前段的 gcd，用 0 作为单位元便于首个数直接成为 gcd
        for (int x : nums) {  // 从左到右依次尝试把每个元素并入当前段
            g = gcd(g, x);  // 合并后当前段的 gcd 更新为 gcd(旧 gcd, x)
            if (g == 1) {  // 当前段 gcd 变成 1，说明这一段已经非法，必须在此切开
                ++ans;  // 新开一段，段数加一
                g = x;  // 新段从当前元素 x 重新开始计算 gcd
            }
        }
        return ans;  // 返回累计得到的最少段数
    }
};