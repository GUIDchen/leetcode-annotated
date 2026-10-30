class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string tictactoe(vector<vector<int>>& moves) {  // moves：按时间顺序的落子坐标，A 先手
        int n = moves.size();  // 总落子步数
        int cnt[8]{};  // 8 个计数器：0~2 三行、3~5 三列、6 主对角线、7 副对角线
        for (int k = n - 1; k >= 0; k -= 2) {  // 倒序遍历、步长 2，只看同一玩家落下的格子
            int i = moves[k][0], j = moves[k][1];  // 取出这一步的行 i 与列 j
            cnt[i]++;  // 第 i 行的计数加一（行 i 对应计数器 i）
            cnt[j + 3]++;  // 第 j 列的计数加一（第 j 列映射到 j+3）
            if (i == j) {  // 落子在主对角线上
                cnt[6]++;  // 主对角线计数加一
            }  // 结束主对角线判断
            if (i + j == 2) {  // 落子在副对角线上（i + j == 2）
                cnt[7]++;  // 副对角线计数加一
            }  // 结束副对角线判断
            if (cnt[i] == 3 || cnt[j + 3] == 3 || cnt[6] == 3 || cnt[7] == 3) {  // 行、列或某条对角线已经凑满 3 个
                return k % 2 == 0 ? "A" : "B";  // k 为偶数说明这一步是 A 下的，否则是 B
            }  // 结束 if 判断
        }  // 结束倒序遍历
        return n == 9 ? "Draw" : "Pending";  // 下满 9 步还没人赢就是平局，否则仍在进行中
    }  // tictactoe 方法结束
};  // Solution 类定义结束