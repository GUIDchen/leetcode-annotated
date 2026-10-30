// 题目：1222. 可以攻击国王的皇后（Queens That Can Attack the King）
// 思路：从国王出发沿 8 个方向逐格射线扫描，每个方向上遇到的第一个皇后才能攻击国王，收集后跳过该方向。
// 时间复杂度：O(q + 8*8)，q 为皇后个数，棋盘固定 8x8；空间复杂度：O(1)，定长棋盘表加答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {  // queens：皇后坐标列表；king：国王坐标
        int n = 8;  // 国际象棋棋盘固定是 8x8
        bool s[8][8]{};  // 棋盘占用表，值初始化为 false，用于 O(1) 查询某格是否有皇后
        for (auto& q : queens) {  // 遍历所有皇后，把位置记到棋盘上
            s[q[0]][q[1]] = true;  // 标记该位置存在皇后
        }  // 建表结束
        vector<vector<int>> ans;  // 收集所有能攻击国王的皇后坐标
        for (int a = -1; a <= 1; ++a) {  // 行方向偏移：-1、0、1
            for (int b = -1; b <= 1; ++b) {  // 列方向偏移：-1、0、1，组合起来共 8 个方向
                if (a || b) {  // 跳过 (0,0)，那不是方向而是原地
                    int x = king[0] + a, y = king[1] + b;  // 从国王所在位置沿该方向迈出第一步
                    while (x >= 0 && x < n && y >= 0 && y < n) {  // 只要还没走出棋盘，就沿同一方向一直前进
                        if (s[x][y]) {  // 该方向上遇到的第一个皇后
                            ans.push_back({x, y});  // 它能攻击国王，加入答案
                            break;  // 更远的皇后被它挡住，该方向不用再看
                        }  // 分支结束
                        x += a;  // 行继续沿该方向前进一格
                        y += b;  // 列继续沿该方向前进一格
                    }  // 该方向扫描结束
                }  // 方向组合分支结束
            }  // 列偏移循环结束
        }  // 行偏移循环结束
        return ans;  // 返回答案，顺序与方向枚举顺序一致
    }  // 方法结束
};  // 类定义结束