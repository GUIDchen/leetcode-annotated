// 题目：1643. 第 K 条最小指令（Kth Smallest Instructions）
// 思路：先递推组合数表，再逐位贪心确定：若「以 H 开头」的方案数 x 小于 k，则本位放 V 并令 k -= x，否则本位放 H。
// 时间复杂度：O((v+h)·h)，填组合数表加逐位查询；空间复杂度：O((v+h)·h)，组合数表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外开放
    string kthSmallestPath(vector<int>& destination, int k) {  // destination = [行数, 列数]；k 是 1-based 的字典序序号，返回第 k 小的指令串
        int v = destination[0], h = destination[1];  // v：还需要走的 V（纵向）步数；h：还需要走的 H（横向）步数
        int n = v + h;  // 总共要走 n 步
        int c[n + 1][h + 1];  // 组合数表 c[i][j] 表示从 i 步里挑 j 步放 H 的方案数，即 C(i, j)
        memset(c, 0, sizeof(c));  // 先整体清零
        c[0][0] = 1;  // 边界：0 步里挑 0 步有 1 种方案
        for (int i = 1; i <= n; ++i) {  // 递推填充组合数表（帕斯卡三角）
            c[i][0] = 1;  // 任意 i 步里挑 0 步都只有 1 种方案
            for (int j = 1; j <= h; ++j) {  // 枚举要挑的步数 j，只需算到 h（H 最多 h 个）
                c[i][j] = c[i - 1][j] + c[i - 1][j - 1];  // 帕斯卡恒等式：C(i, j) = C(i-1, j) + C(i-1, j-1)
            }  // 内层枚举结束
        }  // 组合数表构造完毕
        string ans;  // ans 保存最终生成的指令串
        for (int i = 0; i < n; ++i) {  // 逐位确定指令
            if (h == 0) {  // 剩余步数里已经没有 H，后面只能全填 V
                ans.push_back('V');  // 追加字符 V
            } else {  // 否则还需要比较「以 H 开头」的方案数
                int x = c[v + h - 1][h - 1];  // 以 H 开头的方案数：先放一个 H，再从剩余 v + h - 1 步里挑 h - 1 个 H
                if (k > x) {  // k 大于这些方案，说明答案不以 H 开头
                    ans.push_back('V');  // 这一位确定为 V
                    --v;  // 消耗一个 V 步
                    k -= x;  // 跳过前面 x 个以 H 开头的串，把 k 换算到本层序号
                } else {  // 否则答案以 H 开头
                    ans.push_back('H');  // 这一位确定为 H
                    --h;  // 消耗一个 H 步
                }  // 内层分支结束
            }  // 外层分支结束
        }  // 逐位确定结束
        return ans;  // 返回第 k 小的指令串
    }  // 方法结束
};  // 类定义结束