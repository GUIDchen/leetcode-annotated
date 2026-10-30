// 题目：2811. 判断是否能拆分数组（Check if it is Possible to Split Array）
// 思路：前缀和 + 记忆化搜索。dfs(i, j) 判断区间 nums[i..j] 能否被拆完：枚举切点 k，左段 [i, k] 与右段 [k + 1, j] 各自要么长度为 1、要么元素和达到 m，且两段内部都能继续拆，才说明整体可行。
// 时间复杂度：O(n^3)，共有 O(n^2) 个状态、每个状态枚举 O(n) 个切点；空间复杂度：O(n^2)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canSplitArray(vector<int>& nums, int m) {  // nums：输入数组；m：每段的元素和阈值；返回能否拆完
        int n = nums.size();  // n：数组长度
        vector<int> s(n + 1);  // 前缀和数组，s[i] 表示 nums 前 i 个元素之和
        for (int i = 1; i <= n; ++i) {  // 递推前缀和，于是区间 [l, r] 的元素和为 s[r + 1] - s[l]
            s[i] = s[i - 1] + nums[i - 1];  // 累加 nums[i - 1] 得到前 i 个元素之和
        }
        int f[n][n];  // f[i][j] 记忆化：-1 表示未计算，0 表示不可行，1 表示可行
        memset(f, -1, sizeof f);  // 全部初始化为 -1，表示这些状态还没有被搜索过
        function<bool(int, int)> dfs = [&](int i, int j) {  // 递归函数 dfs(i, j)：判断子数组 nums[i..j] 能否被拆完
            if (i == j) {  // 区间只剩一个元素时天然合法，这是递归出口
                return true;  // 单元素段直接可行
            }
            if (f[i][j] != -1) {  // 命中记忆：这个区间之前已经算过
                return f[i][j] == 1;  // 直接返回上次算出的结果（1 可行，0 不可行）
            }
            for (int k = i; k < j; ++k) {  // 枚举切点 k，把 [i, j] 切成左段 [i, k] 与右段 [k + 1, j]
                bool a = k == i || s[k + 1] - s[i] >= m;  // 左段长度为 1，或其元素和达到 m，都是合法的切出段
                bool b = k == j - 1 || s[j + 1] - s[k + 1] >= m;  // 右段同理：长度为 1，或元素和达到 m
                if (a && b && dfs(i, k) && dfs(k + 1, j)) {  // 左右两段都合法，且两段内部都能继续拆完
                    f[i][j] = 1;  // 记录该状态可行
                    return true;  // 立即返回，不再尝试其他切点
                }
            }
            f[i][j] = 0;  // 所有切点都失败，记为不可行
            return false;  // 返回 false
        };
        return dfs(0, n - 1);  // 从整个数组 [0, n - 1] 开始搜索
    }
};  // 类定义结束