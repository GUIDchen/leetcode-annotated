// 题目：351. 安卓系统手势解锁（Android Unlock Patterns）
// 思路：预处理 cross[i][j]（i 到 j 必须已使用的中间点），对每个起点做回溯 DFS，再按角、边、中心的对称性合并计数。
// 时间复杂度：O(9!)，即所有合法手势路径数；空间复杂度：O(1)，只有 cross、vis 与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfPatterns(int m, int n) {  // m、n 分别为手势点数的最少值与最多值
        int cross[10][10];  // cross[i][j]：从 i 直接连到 j 时必须已经过的中间点，0 表示可直接连
        memset(cross, 0, sizeof(cross));  // 整体清零，即默认任意两点之间没有阻挡点
        bool vis[10];  // vis[k] 表示数字 k 在这次手势里是否已被使用
        memset(vis, false, sizeof(vis));  // 初始时 1~9 全部未使用
        cross[1][3] = cross[3][1] = 2;  // 1 与 3 之间隔着 2
        cross[1][7] = cross[7][1] = 4;  // 1 与 7 之间隔着 4
        cross[1][9] = cross[9][1] = 5;  // 1 与 9 之间隔着 5
        cross[2][8] = cross[8][2] = 5;  // 2 与 8 之间隔着 5
        cross[3][7] = cross[7][3] = 5;  // 3 与 7 之间隔着 5
        cross[3][9] = cross[9][3] = 6;  // 3 与 9 之间隔着 6
        cross[4][6] = cross[6][4] = 5;  // 4 与 6 之间隔着 5
        cross[7][9] = cross[9][7] = 8;  // 7 与 9 之间隔着 8

        function<int(int, int)> dfs = [&](int i, int cnt) {  // 用 std::function 包装 lambda 以便递归：i 是当前落点，cnt 是已选点数
            if (cnt > n) {  // 点数超过上限 n，这条路径不再合法
                return 0;  // 该分支贡献 0 种方案
            }  // 结束上限判断
            vis[i] = true;  // 标记当前点已被使用，后续点不能再选它
            int ans = cnt >= m ? 1 : 0;  // 已选点数达到下限 m 时，当前前缀本身就算一个合法手势
            for (int j = 1; j < 10; ++j) {  // 枚举下一个可能落下的数字 1~9
                int x = cross[i][j];  // 查询从 i 连到 j 需要预先经过的中间点
                if (!vis[j] && (x == 0 || vis[x])) {  // j 未用过，且中间没有阻挡点或者阻挡点已用过，才允许连接
                    ans += dfs(j, cnt + 1);  // 递归统计以 j 为下一步的所有合法手势数
                }  // 结束条件判断
            }  // 结束下一个点的枚举
            vis[i] = false;  // 回溯：撤销使用标记，让其它分支能复用该点
            return ans;  // 返回以 i 为起点的合法手势总数
        };  // lambda 定义结束

        return dfs(1, 1) * 4 + dfs(2, 1) * 4 + dfs(5, 1);  // 利用对称性：1/3/7/9 四个角等价、2/4/6/8 四条边等价、中心 5 单独一类
    }  // 方法结束
};  // 类定义结束