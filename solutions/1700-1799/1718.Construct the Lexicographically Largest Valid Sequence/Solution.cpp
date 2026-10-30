// 题目：1718. 构建字典序最大的可行序列（Construct the Lexicographically Largest Valid Sequence）
// 思路：DFS 回溯。从左往右填位置，每个位置优先放大数字 i（从 n 到 2），把 i 同时放在 u 与 u+i；大数字都放不下时才放 1。先大后小保证第一个解就是字典序最大的解。
// 时间复杂度：O(n!)（回溯剪枝后远小于此）；空间复杂度：O(n)，递归栈与 path/cnt 数组。
class Solution {
public:
    int n;  // 题目给定的 n，dfs 中反复使用，故存为成员变量
    vector<int> cnt, path;  // cnt[i]：数字 i 还剩多少次可放；path：构造中的序列（1 基下标）

    vector<int> constructDistancedSequence(int _n) {  // 构造长度为 2n-1 的字典序最大的合法序列
        n = _n;  // 保存到成员变量，供 dfs 使用
        cnt.resize(n * 2, 2);  // 每个数字最多出现两次（1 除外，稍后改成 1 次）
        path.resize(n * 2);  // 多开一格，让 1..2n-1 的下标都合法
        cnt[1] = 1;  // 数字 1 只出现一次
        dfs(1);  // 从第 1 个位置开始搜索
        vector<int> ans;  // 收集要返回的答案
        for (int i = 1; i < n * 2; ++i) ans.push_back(path[i]);  // 下标 0 是哨兵，答案只取 1..2n-1
        return ans;  // 返回构造结果
    }

    bool dfs(int u) {  // 尝试填第 u 个位置，返回是否成功构造出完整序列
        if (u == n * 2) return 1;  // 所有位置都填满，说明构造成功
        if (path[u]) return dfs(u + 1);  // 该位置已被前一个数字占据，直接处理下一个位置
        for (int i = n; i > 1; --i) {  // 从大到小尝试数字，保证字典序最大
            if (cnt[i] && u + i < n * 2 && !path[u + i]) {  // i 还有剩余次数，且第二个位置不越界、未被占用
                path[u] = path[u + i] = i;  // 两个相距 i 的位置同时填入 i
                cnt[i] = 0;  // 标记 i 已用完
                if (dfs(u + 1)) return 1;  // 继续填下一个空位，成功则直接返回
                cnt[i] = 2;  // 回溯：恢复 i 的可用次数
                path[u] = path[u + i] = 0;  // 回溯：清空刚才填入的两个位置
            }
        }
        if (cnt[1]) {  // 大数字都放不下时，尝试放只出现一次的 1
            path[u] = 1;  // 在 u 处放置 1
            cnt[1] = 0;  // 标记 1 已被使用
            if (dfs(u + 1)) return 1;  // 继续搜索，成功则返回
            cnt[1] = 1;  // 回溯：恢复 1 的可用次数
            path[u] = 0;  // 回溯：清空该位置
        }
        return 0;  // 当前位置放不下任何数字，搜索失败
    }
};