// 题目：1240. 铺瓷砖（Tiling a Rectangle with the Fewest Squares）
// 思路：按从左到右、从上到下的顺序回溯每个空格子，尝试用所有可行边长的正方形覆盖，用二进制位表记录占用并借助当前最优解剪枝。
// 时间复杂度：最坏指数级（用最优解 ans 剪枝），空间复杂度：O(n·m) 递归深度 + O(n) 位表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    int tilingRectangle(int n, int m) {  // n 行 m 列，返回铺满矩形所需的最少正方形个数
        memset(filled, 0, sizeof(filled));  // 清空「第 i 行哪些列已被覆盖」的位表
        this->n = n;  // 把行数写入成员，供 dfs 使用（避免与形参同名混淆）
        this->m = m;  // 把列数写入成员，供 dfs 使用
        ans = n * m;  // 上界：每格放一个 1×1 正方形，共 n*m 块
        dfs(0, 0, 0);  // 从左上角 (0,0) 出发、已用 0 块开始搜索
        return ans;  // 返回搜索过程中更新到的最小块数
    }

private:  // 以下为内部状态与递归函数
    int filled[13];  // filled[i] 的第 j 位表示格子 (i,j) 已被占用（题目保证 n≤13）
    int n, m;  // 网格的行数、列数
    int ans;  // 当前找到的最少正方形数量

    void dfs(int i, int j, int t) {  // 处理格子 (i,j)，此时已放置 t 个正方形
        if (j == m) {  // 本行已处理完
            ++i;  // 换到下一行
            j = 0;  // 列号归零
        }
        if (i == n) {  // 所有行都处理完，说明矩形已经铺满
            ans = t;  // 有剪枝保证这是当前最优，直接更新答案
            return;  // 结束这条分支
        }
        if (filled[i] >> j & 1) {  // 当前格子已被之前的正方形覆盖
            dfs(i, j + 1, t);  // 跳过该格，接着处理右边一格
        } else if (t + 1 < ans) {  // 只有还能比现有最优解更少时才继续试探
            int r = 0, c = 0;  // r：从 (i,j) 往下连续的空格数；c：往右连续的空格数
            for (int k = i; k < n; ++k) {  // 向下探测最大可用高度
                if (filled[k] >> j & 1) {  // 第 k 行的第 j 列已被占用
                    break;  // 高度探测到此为止
                }
                ++r;  // 可用高度加一
            }
            for (int k = j; k < m; ++k) {  // 向右探测最大可用宽度
                if (filled[i] >> k & 1) {  // 第 i 行的第 k 列已被占用
                    break;  // 宽度探测到此为止
                }
                ++c;  // 可用宽度加一
            }
            int mx = min(r, c);  // 以 (i,j) 为左上角的正方形最大边长
            for (int w = 1; w <= mx; ++w) {  // 依次尝试边长 1..mx 的正方形
                for (int k = 0; k < w; ++k) {  // 只标记底边与右边，这些位足够让后续扫描判断占用
                    filled[i + w - 1] |= 1 << (j + k);  // 标记正方形底边所在的这一行
                    filled[i + k] |= 1 << (j + w - 1);  // 标记正方形右边所在的这一列
                }
                dfs(i, j + w, t + 1);  // 放下该正方形后，从它右侧的格子继续搜索
            }
            for (int x = i; x < i + mx; ++x) {  // 回溯：撤销这一轮试探留下的大量标记
                for (int y = j; y < j + mx; ++y) {  // 覆盖 mx×mx 的整块区域
                    filled[x] ^= 1 << y;  // 异或把区域内被翻转的位恢复成未占用
                }
            }
        }
    }
};  // 类定义结束