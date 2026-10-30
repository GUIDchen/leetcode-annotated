// 题目：1349. 参加考试的最大学生数（Maximum Students Taking Exam）
// 思路：按行做状态压缩 DP（记忆化搜索）：位掩码 mask 表示本行坐人的位置，要求 mask 只能落在好座位上且本行不出现左右相邻；转移时把本行 mask 左右各平移一位后从下一行的可用座位里剔除，保证对角线也不相邻。
// 时间复杂度：O(m * 4^n)，每行 2^n 个状态、每个状态枚举 2^n 个 mask；空间复杂度：O(m * 2^n)，记忆化表大小为 2^n * m。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxStudents(vector<vector<char>>& seats) {  // seats：二维字符矩阵，'#' 表示坏座位不能坐人，'.' 表示好座位
        int m = seats.size();  // m：行数，也就是 DP 的层数
        int n = seats[0].size();  // n：列数，也就是状态压缩的位宽
        vector<int> ss(m);  // ss[i] 用位掩码记录第 i 行的好座位位置（第 j 位为 1 表示该位置能坐人）
        vector<vector<int>> f(1 << n, vector<int>(m, -1));  // 记忆化表 f[seat][i]：第 i 行可用座位为 seat 时，从第 i 行到最后一行能坐的最大人数，-1 表示尚未计算
        for (int i = 0; i < m; ++i) {  // 逐行扫描输入矩阵
            for (int j = 0; j < n; ++j) {  // 逐列扫描当前行
                if (seats[i][j] == '.') {  // 遇到好座位
                    ss[i] |= 1 << j;  // 把第 j 位置 1，表示这个座位可以坐人
                }  // if 语句结束
            }  // 列循环结束
        }  // 行循环结束，每行的可用座位掩码都准备好了
        function<int(int, int)> dfs = [&](int seat, int i) -> int {  // 记忆化搜索：seat 是第 i 行允许坐人的位置集合，i 是当前行号
            if (f[seat][i] != -1) {  // 如果这个状态已经算过，直接复用，避免重复搜索
                return f[seat][i];  // 返回缓存值
            }  // if 语句结束
            int ans = 0;  // ans 保存当前状态下的最大人数
            for (int mask = 0; mask < 1 << n; ++mask) {  // 枚举本行所有可能的坐法 mask
                if ((seat | mask) != seat || (mask & (mask << 1)) != 0) {  // 两个剪枝：(seat | mask) != seat 表示坐到了坏座位；mask & (mask << 1) 非零表示本行有左右相邻
                    continue;  // 该坐法非法，直接跳过
                }  // continue 结束本次枚举
                int cnt = __builtin_popcount(mask);  // 统计本行坐下的人数，即 mask 中 1 的个数
                if (i == m - 1) {  // 如果已经是最后一行，后面没有行需要约束
                    ans = max(ans, cnt);  // 直接用本行人数更新答案
                } else {  // 否则还要继续向下一行转移
                    int nxt = ss[i + 1];  // nxt 初值是下一行的好座位掩码
                    nxt &= ~(mask >> 1);  // mask >> 1 把本行的人影子移到左下方，从下一行剔除，避免左下角对角相邻
                    nxt &= ~(mask << 1);  // mask << 1 把本行的人影子移到右下方，从下一行剔除，避免右下角对角相邻
                    ans = max(ans, cnt + dfs(nxt, i + 1));  // 本行人数 + 后续行最优解，取最大值
                }  // else 块结束
            }  // mask 枚举结束
            return f[seat][i] = ans;  // 把结果写回记忆化表并返回
        };  // lambda 定义结束；外面套 function<int(int,int)> 是为了让这个 lambda 能递归调用自身
        return dfs(ss[0], 0);  // 从第 0 行、第一行的可用座位掩码出发求全局最优
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，逐字节保持不变）