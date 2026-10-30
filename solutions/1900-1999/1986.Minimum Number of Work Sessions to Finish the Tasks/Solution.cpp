// 题目：1986. 完成任务的最少工作时间段（Minimum Number of Work Sessions to Finish the Tasks）
// 思路：状压 DP。先预处理每个任务子集能否放进一个时间段，再枚举子集划分，f[mask] 表示完成 mask 的最少时间段数。
// 时间复杂度：O(3^n + n·2^n)，子集枚举的总代价；空间复杂度：O(2^n)，两个大小 2^n 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSessions(vector<int>& tasks, int sessionTime) {  // tasks：每项任务的耗时；sessionTime：一个时间段能容纳的总时长
        int n = tasks.size();  // 任务个数（n ≤ 14，2^n 可以接受，适合状态压缩）
        bool ok[1 << n];  // ok[mask] 表示 mask 这组任务能否放进同一个时间段
        memset(ok, false, sizeof(ok));  // 全部先置为 false
        for (int i = 1; i < 1 << n; ++i) {  // 枚举所有非空任务集合
            int t = 0;  // 该集合的总耗时
            for (int j = 0; j < n; ++j) {  // 逐位扫描集合中的每一位
                if (i >> j & 1) {  // 第 j 位为 1，说明集合包含第 j 项任务
                    t += tasks[j];  // 把它的耗时累加进来
                }  // 分支结束
            }  // 集合求和结束
            ok[i] = t <= sessionTime;  // 总耗时不超过上限，就能并成一个时间段
        }  // 预处理结束
        int f[1 << n];  // f[mask]：完成 mask 这些任务所需的最少时间段数
        memset(f, 0x3f, sizeof(f));  // 用 0x3f3f3f3f 这种很大的值初始化，代表尚未可达
        f[0] = 0;  // 一个任务都不做需要 0 个时间段
        for (int i = 1; i < 1 << n; ++i) {  // 按集合编号从小到大递推
            for (int j = i; j; j = (j - 1) & i) {  // 枚举 i 的所有非空子集 j 作为「最后一个时间段」，j 递减到 0 时停止
                if (ok[j]) {  // 这段任务能一次做完
                    f[i] = min(f[i], f[i ^ j] + 1);  // 用剩余集合 i^j 的最优解再加这一段来更新
                }  // 分支结束
            }  // 子集枚举结束
        }  // DP 结束
        return f[(1 << n) - 1];  // 全集 (1<<n)-1 对应的值就是答案
    }  // 方法结束
};  // 类定义结束