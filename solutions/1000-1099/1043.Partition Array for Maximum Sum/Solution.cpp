// 题目：1043. 分隔数组以得到最大和（Partition Array for Maximum Sum）
// 思路：动态规划，f[i] 表示前 i 个元素划分后的最大和；枚举最后一段的长度 len（不超过 k），把它整体替换为段内最大值 mx 后累加。
// 时间复杂度：O(nk)，每个位置枚举不超过 k 种段长；空间复杂度：O(n)，DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSumAfterPartitioning(vector<int>& arr, int k) {  // arr 是原数组，k 是每段的最大长度，返回划分后的最大和
        int n = arr.size();  // 数组元素个数 n
        int f[n + 1];  // DP 数组：f[i] 表示前 i 个元素划分后能得到的最大和
        memset(f, 0, sizeof(f));  // 初始化为 0，f[0] 天然表示空前缀的和为 0
        for (int i = 1; i <= n; ++i) {  // 从前 1 个元素开始递推到前 n 个
            int mx = 0;  // 最后一段的最大值，随着 j 左移逐步扩大
            for (int j = i; j > max(0, i - k); --j) {  // j 是最后一段的起点（1 基），段长为 i - j + 1，且不超过 k
                mx = max(mx, arr[j - 1]);  // 把 arr[j-1] 纳入最后一段，更新段内最大值
                f[i] = max(f[i], f[j - 1] + mx * (i - j + 1));  // 方案一：沿用之前的划分；方案二：前 j-1 个的最优和加上最后一段全变成 mx 的和
            }  // 最后一段长度枚举结束
        }  // 前缀长度递推结束
        return f[n];  // 返回前 n 个元素划分后的最大和
    }  // 方法结束
};  // 类结束