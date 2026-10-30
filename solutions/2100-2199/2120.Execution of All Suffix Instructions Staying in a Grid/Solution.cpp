// 题目：2120. 执行所有后缀指令（Execution of All Suffix Instructions Staying in a Grid）
// 核心思路：用哈希表把四个方向映射为坐标增量，对每个后缀从起点逐个试走，越界即停，步数就是答案。
// 时间复杂度：O(m^2)，m = |s|，每个后缀最坏走满整个串；空间复杂度：O(m)，答案数组与常数大小的方向表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {  // n：网格边长；startPos：起点；s：指令串
        int m = s.size();  // 指令串长度，也是后缀个数
        vector<int> ans(m);  // 为每个后缀预留一格答案
        unordered_map<char, vector<int>> mp;  // 方向字符 → (行增量, 列增量)
        mp['L'] = {0, -1};  // 左：行不变，列减一
        mp['R'] = {0, 1};  // 右：行不变，列加一
        mp['U'] = {-1, 0};  // 上：行减一，列不变
        mp['D'] = {1, 0};  // 下：行加一，列不变
        for (int i = 0; i < m; ++i) {  // 枚举后缀起点 i
            int x = startPos[0], y = startPos[1];  // 每个后缀都回到题给起点，x 为行坐标、y 为列坐标
            int t = 0;  // 记录这个后缀成功执行了多少步
            for (int j = i; j < m; ++j) {  // 按顺序尝试后缀中的每条指令
                int a = mp[s[j]][0], b = mp[s[j]][1];  // 取出这条指令的行增量与列增量
                if (0 <= x + a && x + a < n && 0 <= y + b && y + b < n) {  // 只有走完后仍在网格内才允许走
                    x += a;  // 原地更新行坐标
                    y += b;  // 原地更新列坐标
                    ++t;  // 成功走出一步，计数加一
                } else  // 走完会越界，说明这条及之后的指令都执行不了
                    break;  // 立即跳出内层循环
            }
            ans[i] = t;  // 把该后缀的步数写进答案
        }
        return ans;  // 返回全部后缀的执行步数
    }
};