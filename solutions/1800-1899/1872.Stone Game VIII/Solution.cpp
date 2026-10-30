// 题目：1872. 石子游戏 VIII（Stone Game VIII）
// 思路：先把数组原地变成前缀和，再记忆化搜索 f(i) = max(f(i+1), s[i] - f(i+1))，表示轮到当前玩家时的最大分差。
// 时间复杂度：O(n)，每个状态只计算一次；空间复杂度：O(n)，记忆化数组与递归栈各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int stoneGameVIII(vector<int>& stones) {  // stones：每堆石子的数量
        int n = stones.size();  // 堆数
        for (int i = 1; i < n; ++i) {  // 原地把 stones 改造成前缀和
            stones[i] += stones[i - 1];  // 前缀和：stones[i] 表示前 i+1 堆石子的总数
        }  // 结束 for
        int f[n];  // 记忆化数组：f[i] 表示轮到当前玩家、可从第 i 个位置开始选时的最大分差
        memset(f, -1, sizeof(f));  // 用 -1 标记「尚未计算」
        function<int(int)> dfs = [&](int i) -> int {  // 递归函数：返回从下标 i 开始行动时当前玩家能获得的最大分差
            if (i >= n - 1) {  // 只剩最后一堆可选时只能全取，分差就是这段前缀和
                return stones[i];  // 直接返回累计值
            }  // 结束 if
            if (f[i] == -1) {  // 尚未计算过才继续递归
                f[i] = max(dfs(i + 1), stones[i] - dfs(i + 1));  // 取走前 i+1 堆后由对手从 i+1 行动；或这次跳过、让对手从 i+1 先行动，两者取较大值
            }  // 结束 if
            return f[i];  // 返回记忆化后的结果
        };  // 结束 lambda（递归函数本体）
        return dfs(1);  // 第一次行动必须取走前两堆，因此从下标 1 开始
    }  // 结束方法
};  // 结束类
