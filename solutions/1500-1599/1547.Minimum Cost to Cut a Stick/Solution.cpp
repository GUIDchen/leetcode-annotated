// 题目：1547. 切棍子的最小成本（Minimum Cost to Cut a Stick）
// 思路：把 0 与 n 也放进切点数组并排序，做区间 DP：f[i][j] 表示切完 cuts[i] 到 cuts[j] 这段木棍的最小成本，
// 时间复杂度：O(m^3)（m 为切点个数，三重循环枚举区间与切点）；空间复杂度：O(m^2)（DP 表）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(int n, vector<int>& cuts) {  // n：木棍长度；cuts：所有需要切的切点位置
        cuts.push_back(0);  // 把木棍左端点 0 补成一个"切点"，让整根木棍能被区间下标表示
        cuts.push_back(n);  // 把木棍右端点 n 也补进去，闭合整根木棍的区间
        sort(cuts.begin(), cuts.end());  // 升序排序，使相邻切点之间正好是一段完整的木棍
        int m = cuts.size();  // 切点总数（原有切点 + 两个端点）
        int f[110][110]{};  // f[i][j]：切完 cuts[i]..cuts[j] 这段木棍的最小成本，值初始化为 0
        for (int l = 2; l < m; ++l) {  // 枚举区间跨度 l：跨度为 0 或 1 的区间内部没有切点，不需切割
            for (int i = 0; i + l < m; ++i) {  // 枚举区间左端点 i
                int j = i + l;  // 由左端点与跨度推出右端点 j
                f[i][j] = 1 << 30;  // 先置成极大值，后续用 min 更新出真正的最小成本
                for (int k = i + 1; k < j; ++k) {  // 枚举"最后切的一刀"落在 cuts[k] 处
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j] + cuts[j] - cuts[i]);  // 左右两段子问题的成本，加上这一刀的代价（当前整段长度）
                }
            }
        }
        return f[0][m - 1];  // 答案：从 0 到 n 整根木棍切完的最小成本（首尾端点的区间）
    }
};