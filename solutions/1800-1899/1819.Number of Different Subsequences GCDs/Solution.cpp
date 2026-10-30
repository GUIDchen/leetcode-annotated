// 题目：1819. 序列中不同最大公约数的数目（Number of Different Subsequences GCDs）
// 思路：枚举可能的 GCD 值 x，把 nums 中所有 x 的倍数依次求 gcd；若某个倍数区间内的 gcd 恰好等于 x，说明 x 是一个可达到的子序列 GCD。
// 时间复杂度：O(M log M)，M = max(nums)，调和级数级别的枚举量；空间复杂度：O(M)，布尔数组标记哪些数出现在 nums 中。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countDifferentSubsequenceGCDs(vector<int>& nums) {  // nums：输入数组
        int mx = *max_element(nums.begin(), nums.end());  // 数组最大值，作为枚举上界
        vector<bool> vis(mx + 1);  // vis[v] 表示数值 v 是否在数组中出现过
        for (int& x : nums) {  // 遍历数组做存在性标记
            vis[x] = true;  // 标记 x 出现过
        }
        int ans = 0;  // 不同子序列 GCD 的个数
        for (int x = 1; x <= mx; ++x) {  // 枚举候选 GCD 值 x
            int g = 0;  // 累积当前 x 的所有倍数中出现过的数的 gcd，0 与任何数 gcd 仍是该数
            for (int y = x; y <= mx; y += x) {  // 按倍数步长枚举所有 x 的倍数
                if (vis[y]) {  // 只有出现过的数才能参与子序列
                    g = gcd(g, y);  // 把 y 并入累积 gcd
                    if (g == x) {  // gcd 恰好等于 x，说明 x 可被某个子序列取到
                        ++ans;  // 计数加一
                        break;  // 已经确认 x 可达，无需继续枚举倍数
                    }
                }
            }
        }
        return ans;  // 返回不同 GCD 的总数
    }
};  // 结束 Solution 类定义