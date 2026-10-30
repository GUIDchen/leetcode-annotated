// 题目：3310. 移除可疑的方法（Remove Methods From Project）
// 思路：先用有向图 DFS 求出 k 能直接或间接调用的全部方法（可疑集合）；再把调用关系看成无向图，从集合外的方法出发扩展——只要集合外方法与之相连，它就无法被删除，取消可疑标记。
// 复杂度：时间 O(n + m)，每条调用关系只会被两条邻接表各遍历一次；空间 O(n + m)，两个邻接表加上两个标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {  // n：方法总数（编号 0..n-1）；k：可疑方法；invocations 中每条 [a, b] 表示方法 a 调用了方法 b
        vector<bool> suspicious(n);  // suspicious[i]：方法 i 是否属于「从 k 出发可（直接或间接）调用到」的集合
        vector<bool> vis(n);  // vis[i]：反向扩展时方法 i 是否已被访问，避免重复遍历
        vector<int> f[n];  // f：把调用关系当作无向图，用于判断可疑集合是否被集合外的方法牵连
        vector<int> g[n];  // g：只保留 a→b 的有向边，用于从 k 出发求可疑闭包
        for (const auto& e : invocations) {  // 逐条读入调用关系
            int a = e[0], b = e[1];  // 拆出这条边的两个端点：a 调用了 b
            f[a].push_back(b);  // 无向图：a 的邻接表加入 b
            f[b].push_back(a);  // 无向图：b 的邻接表也要加入 a，保证双向可达
            g[a].push_back(b);  // 有向图只记录 a→b 这一条边
        }  // for 循环结束
        auto dfs = [&](this auto&& dfs, int i) -> void {  // C++23 的显式对象参数写法，让 lambda 能够递归调用自己
            suspicious[i] = true;  // 标记当前方法为可疑（它能从 k 被调用到）
            for (int j : g[i]) {  // 遍历方法 i 直接调用的所有方法
                if (!suspicious[j]) {  // 还没标记过才继续深搜，避免在环上无限递归
                    dfs(j);  // 递归处理被调用的方法
                }  // if 结束
            }  // for 循环结束
        };  // dfs lambda 定义结束
        dfs(k);  // 从可疑方法 k 出发，求出完整的可疑集合
        auto dfs2 = [&](this auto&& dfs2, int i) -> void {  // 第二个递归 lambda：从可疑集合外的方法出发，沿无向边向外扩散
            vis[i] = true;  // 标记方法 i 已访问
            for (int j : f[i]) {  // 遍历无向图上的所有邻居
                if (!vis[j]) {  // 邻居还没访问过才处理
                    suspicious[j] = false;  // 该邻居与集合外的方法连通，无法被单独删除，取消它的可疑标记
                    dfs2(j);  // 继续向外扩散
                }  // if 结束
            }  // for 循环结束
        };  // dfs2 lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 枚举所有方法，寻找「在可疑集合之外」的扩散起点
            if (!suspicious[i] && !vis[i]) {  // i 不在可疑集合中且还没有被扩散访问过
                dfs2(i);  // 从它出发，把与之连通的方法都排除在删除范围之外
            }  // if 结束
        }  // for 循环结束
        vector<int> ans;  // 收集最终保留的方法编号
        for (int i = 0; i < n; ++i) {  // 再枚举一次全部方法
            if (!suspicious[i]) {  // 只有未被标记为可疑的方法才保留
                ans.push_back(i);  // 按编号从小到大加入答案，自然满足题目要求的升序
            }  // if 结束
        }  // for 循环结束
        return ans;  // 返回保留的方法编号列表
    }  // 方法结束
};  // 类定义结束
