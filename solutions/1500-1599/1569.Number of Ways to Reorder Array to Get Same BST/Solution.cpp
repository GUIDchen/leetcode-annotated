// 题目：1569. 将子数组重新排序得到同一个二叉搜索树的方案数（Number of Ways to Reorder Array to Get Same BST）
// 思路：BST 由根与左右子树唯一确定；先预处理组合数，再 DFS：方案数 = C(|左|+|右|, |左|) * 左方案 * 右方案。
// 时间复杂度：O(n^2)，预处理组合数加递归划分数组；空间复杂度：O(n^2)，组合数二维表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfWays(vector<int>& nums) {  // nums：构成同一棵 BST 的插入序列
        int n = nums.size();  // 元素个数
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        int c[n][n];  // 组合数表：c[i][j] 表示从 i 个里取 j 个的方案数
        memset(c, 0, sizeof(c));  // 先把整张表清零
        c[0][0] = 1;  // 边界：0 个里取 0 个只有一种方案
        for (int i = 1; i < n; ++i) {  // 逐行递推杨辉三角
            c[i][0] = 1;  // 取 0 个的方案数恒为 1
            for (int j = 1; j <= i; ++j) {  // 枚举取 j 个
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;  // 帕斯卡公式，边算边取模防溢出
            }
        }
        function<int(vector<int>)> dfs = [&](vector<int> nums) -> int {  // 递归函数：求以 nums[0] 为根的方案数（按值捕获外部组合数表）
            if (nums.size() < 2) {  // 空序列或单元素序列都只有一种排列
                return 1;  // 递归出口
            }
            vector<int> left, right;  // 分别收集比根小、比根大的元素
            for (int& x : nums) {  // 按原顺序扫描序列
                if (x < nums[0]) {  // 比根小，应归入左子树
                    left.push_back(x);  // 放入左子树序列
                } else if (x > nums[0]) {  // 比根大，应归入右子树
                    right.push_back(x);  // 放入右子树序列
                }
            }
            int m = left.size(), n = right.size();  // 左右子树的规模
            int a = dfs(left), b = dfs(right);  // 左右子树各自的合法方案数
            return c[m + n][m] * 1ll * a % mod * b % mod;  // 左右序列交叉排列并乘上子树方案数，逐步取模防溢出
        };
        return (dfs(nums) - 1 + mod) % mod;  // 减去原序列自身这一种方案，加 mod 避免出现负数
    }
};