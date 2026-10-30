// 题目：1462. 课程表 IV（Course Schedule IV）
// 思路：把先修关系看成有向图的边，用 Floyd 算法求传递闭包 f[i][j]（i 是否是 j 的先修课，含间接关系），再按 queries 逐条查表。
// 时间复杂度：O(n^3 + q)，三重循环求闭包，q 为询问数；空间复杂度：O(n^2)，布尔矩阵存可达性。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {  // n：课程数；prerequisites：直接先修关系；queries：询问对；返回每个询问的布尔结果
        bool f[n][n];  // f[i][j] 为真表示 i 是 j 的先修课程（直接或间接）
        memset(f, false, sizeof(f));  // 把整张布尔矩阵初始化为 false
        for (auto& p : prerequisites) {  // 遍历每条直接先修关系
            f[p[0]][p[1]] = true;  // p[0] 是 p[1] 的直接先修课，先标记这条边
        }  // for 循环体结束
        for (int k = 0; k < n; ++k) {  // Floyd 传递闭包：k 是中间点，按它中转
            for (int i = 0; i < n; ++i) {  // i 是起点（先修课候选）
                for (int j = 0; j < n; ++j) {  // j 是终点（后继课）
                    f[i][j] |= (f[i][k] && f[k][j]);  // 若 i 能到 k 且 k 能到 j，则 i 也能到 j；|= 把已有结果与新结论合并
                }  // 内层 for 循环体结束
            }  // 中层 for 循环体结束
        }  // 外层 for 循环体结束
        vector<bool> ans;  // 按询问顺序存放答案
        for (auto& q : queries) {  // 逐条处理询问
            ans.push_back(f[q[0]][q[1]]);  // 直接查闭包矩阵即可，O(1) 得到答案
        }  // for 循环体结束
        return ans;  // 返回全部询问的结果
    }  // 方法体结束
};  // 类定义结束