// 题目：1900. 最佳运动员的比拼回合（The Earliest and Latest Rounds Where Players Compete）
// 思路：记忆化搜索。用位掩码枚举每一轮所有对局的胜负，强制两名指定选手本轮晋级，按晋级顺序重新编号后递归，直到他们相遇；统计相遇回合的最小值与最大值。
// 时间复杂度：O(n^2 · 2^(n/2))，每种 (l, r, n) 状态只算一次；空间复杂度：O(n^3)，记忆化数组 f 的大小。
int f[30][30][31];  // 记忆化数组：f[l][r][n] 存状态的最早/最晚回合编码，0 表示还没算过
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {  // n：选手总数；firstPlayer、secondPlayer：两名指定选手的编号（从 1 开始）
        return dfs(firstPlayer - 1, secondPlayer - 1, n);  // 编号转成 0 起的下标，交给递归函数
    }  // 公开接口结束

private:  // 下面是内部辅助函数
    vector<int> dfs(int l, int r, int n) {  // l、r：两人在当前剩余选手中的下标；n：当前剩余人数
        if (f[l][r][n] != 0) {  // 这个状态以前算过
            return decode(f[l][r][n]);  // 直接解码缓存结果返回
        }
        if (l + r == n - 1) {  // 两人位置对称，本轮就必然是彼此的对手
            f[l][r][n] = encode(1, 1);  // 缓存：相遇只要 1 轮
            return {1, 1};  // 最早与最晚回合都是 1
        }

        int min = INT_MAX, max = INT_MIN;  // 统计回合数的最小值与最大值（与标准库 min/max 同名，故下面写 std::min / std::max）
        int m = n >> 1;  // 本轮的对局数（人数一半，向下取整）

        for (int i = 0; i < (1 << m); i++) {  // 位掩码 i 枚举每场对局的胜者，第 j 位为 1 表示左侧位置 j 的选手获胜
            vector<bool> win(n, false);  // win[j] 表示位置 j 的选手是否晋级下一轮
            for (int j = 0; j < m; j++) {  // 逐场确定胜者
                if ((i >> j) & 1) {  // 第 j 位为 1：左侧选手获胜
                    win[j] = true;  // 标记左侧位置 j 晋级
                } else {  // 否则右侧选手获胜
                    win[n - 1 - j] = true;  // 对称位置 n-1-j 的选手晋级
                }
            }
            if (n & 1) {  // 人数为奇数时中间那位选手本轮轮空
                win[m] = true;  // 轮空者直接晋级
            }

            win[n - 1 - l] = false;  // 两人必须继续比赛，先取消他们对手的晋级
            win[n - 1 - r] = false;  // 同理取消另一名选手对手的晋级
            win[l] = true;  // 位置 l 的选手本轮必胜
            win[r] = true;  // 位置 r 的选手本轮必胜

            int a = 0, b = 0, c = 0;  // a、b 是两人晋级后的新下标，c 是晋级总人数（下一轮的人数）
            for (int j = 0; j < n; j++) {  // 按位置顺序重新编号
                if (j == l) a = c;  // 遇到 l，记下它在晋级者中的序号
                if (j == r) b = c;  // 遇到 r，记下它在晋级者中的序号
                if (win[j]) c++;  // 晋级人数加一
            }

            vector<int> t = dfs(a, b, c);  // 递归求下一轮的最早/最晚回合数
            min = std::min(min, t[0] + 1);  // 加上本轮，更新最早回合
            max = std::max(max, t[1] + 1);  // 加上本轮，更新最晚回合
        }

        f[l][r][n] = encode(min, max);  // 记住当前状态的结果，避免重复枚举
        return {min, max};  // 返回最早与最晚回合
    }

    int encode(int x, int y) {  // 把最早、最晚两个数压进一个 int：高位存最早，低 8 位存最晚
        return (x << 8) | y;  // 左移 8 位腾出低字节
    }

    vector<int> decode(int val) {  // 从编码里还原出 (最早, 最晚)
        return {val >> 8, val & 255};  // 高位右移取出最早，低 8 位掩码取出最晚
    }
};