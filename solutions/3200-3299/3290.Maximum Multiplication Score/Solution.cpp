// 题目：3290. 最高乘法得分（Maximum Multiplication Score）
// 思路：在 b 中按顺序挑 4 个下标，与 a 逐项相乘后求和求最大，等价于「依次匹配 a[i] 与 b[j]，可跳过 b 元素」的记忆化搜索。
// 时间复杂度：O(mn)，每个 (i,j) 状态只算一次；空间复杂度：O(mn)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxScore(vector<int>& a, vector<int>& b) {  // a：长度 4 的乘数数组；b：供挑选元素的数组
        int m = a.size(), n = b.size();  // m 是 a 的长度，n 是 b 的长度
        long long f[m][n];  // 记忆化数组：f[i][j] 表示已配好前 i 个乘数、b 的下标用到 j 时的最大得分
        memset(f, -1, sizeof(f));  // 用 -1 标记「尚未计算」：得分可能为负，不能拿 0 当哨兵
        auto dfs = [&](this auto&& dfs, int i, int j) -> long long {  // 记忆化递归 lambda（C++23 this auto 参数）：i 是 a 的下标，j 是 b 的下标
            if (j >= n) {  // b 已经用完了
                return i >= m ? 0 : LLONG_MIN / 2;  // 乘数也全部配完则成功返回 0，否则这条路径走不通，返回足够小的负数
            }  // if 结束
            if (i >= m) {  // 乘数已全部配对成功
                return 0;  // 不再需要挑元素，剩余贡献为 0
            }  // if 结束
            if (f[i][j] != -1) {  // 该状态计算过，直接复用
                return f[i][j];  // 返回记忆化结果
            }  // if 结束
            return f[i][j] = max(dfs(i, j + 1), 1LL * a[i] * b[j] + dfs(i + 1, j + 1));  // 两种选择取最大：跳过 b[j]，或用 b[j] 配 a[i] 后继续
        };  // 递归 lambda 定义结束
        return dfs(0, 0);  // 从第一个乘数、b 的第一个元素开始搜索
    }  // maxScore 结束
};  // Solution 类结束
