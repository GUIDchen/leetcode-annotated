// 题目：3040. 相同分数的最大操作数目 II（Maximum Number of Operations With the Same Score II）
// 思路：首次操作只有删首对、删尾对、删首尾三种，枚举这三种分数，再用记忆化 DFS 在区间 [i, j] 上求最多还能删多少对。
// 时间复杂度：O(n²)，每个区间只计算一次、每次三种选择；空间复杂度：O(n²)，记忆化数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxOperations(vector<int>& nums) {  // nums：输入数组
        int n = nums.size();  // 数组长度，也是区间右端点的上界
        auto g = [&](int i, int j, int s) -> int {  // 闭包：在子数组 nums[i..j] 上、以 s 为固定分数求最大操作数
            vector<vector<int>> f(n, vector<int>(n, -1));  // 记忆化数组，-1 表示该区间还没有计算过
            function<int(int, int)> dfs = [&](int i, int j) -> int {  // 递归搜索；用 function 包一层才能在自己的函数体里递归调用
                if (j - i < 1) {  // 区间内不足两个元素
                    return 0;  // 无法再操作，返回 0
                }
                if (f[i][j] != -1) {  // 该区间已经算过
                    return f[i][j];  // 直接复用记忆化结果
                }
                int ans = 0;  // 当前区间能继续操作的最大次数
                if (nums[i] + nums[i + 1] == s) {  // 选择一：删掉最左边两个元素
                    ans = max(ans, 1 + dfs(i + 2, j));  // 本次操作算一次，区间左端点右移两位
                }
                if (nums[i] + nums[j] == s) {  // 选择二：删掉最左与最右各一个元素
                    ans = max(ans, 1 + dfs(i + 1, j - 1));  // 本次操作算一次，区间左右各收缩一位
                }
                if (nums[j - 1] + nums[j] == s) {  // 选择三：删掉最右边两个元素
                    ans = max(ans, 1 + dfs(i, j - 2));  // 本次操作算一次，区间右端点左移两位
                }
                return f[i][j] = ans;  // 结果写入记忆化数组并返回
            };
            return dfs(i, j);  // 从给定区间开始搜索
        };
        int a = g(2, n - 1, nums[0] + nums[1]);  // 情形一：首次删最左两个，分数固定为它们之和
        int b = g(0, n - 3, nums[n - 2] + nums[n - 1]);  // 情形二：首次删最右两个，分数固定为它们之和
        int c = g(1, n - 2, nums[0] + nums[n - 1]);  // 情形三：首次删最左与最右各一个，分数固定为它们之和
        return 1 + max({a, b, c});  // 首次操作本身算一次，再加上三种情形里最好的后续次数
    }
};