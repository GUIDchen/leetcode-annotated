// 题目：749. 隔离病毒（Contain Virus）
// 核心思路：每轮 DFS 找出所有病毒连通块，同时统计各块的威胁边界与所需防火墙数；隔离边界最大的块，其余块向外扩散一格，直到没有新感染。
// 时间复杂度：O((mn)^2)，每轮遍历全图做 DFS，最多 mn 轮；空间复杂度：O(mn)，访问标记与各连通块的记录。
class Solution {  // LeetCode 约定的题解类
public:  // 成员与接口对外可见
    const vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向偏移：用 dirs[k]、dirs[k+1] 依次取上下左右
    vector<int> c;  // c[t]：第 t 个病毒块需要的防火墙数量（与空地相邻的边数）
    vector<vector<int>> areas;  // areas[t]：第 t 个病毒块所有格子的线性编号 i * n + j
    vector<unordered_set<int>> boundaries;  // boundaries[t]：第 t 块威胁到的空地集合，去重后用于挑选最危险的块
    vector<vector<int>> infected;  // 网格副本：1 已感染、0 未感染、-1 已被隔离
    vector<vector<bool>> vis;  // DFS 访问标记，防止同一块被重复搜索
    int m;  // 网格行数
    int n;  // 网格列数

    int containVirus(vector<vector<int>>& isInfected) {  // 主过程：逐轮模拟隔离与扩散，返回所需防火墙总数
        infected = isInfected;  // 拷贝一份网格，避免改动调用方传入的数据
        m = infected.size();  // 记录行数供各个成员函数共用
        n = infected[0].size();  // 记录列数（题目保证网格非空）
        vis.assign(m, vector<bool>(n));  // 按行列尺寸初始化访问标记
        int ans = 0;  // 累计需要的防火墙数量
        while (1) {  // 每轮先分析所有病毒块，再决定隔离谁、谁继续扩散
            for (int i = 0; i < m; ++i)  // 清空访问标记，为这一轮的连通块搜索做准备
                for (int j = 0; j < n; ++j) vis[i][j] = false;  // 内层把每一行的标记都重置为未访问
            c.clear();  // 清空上一轮的防火墙数量记录
            areas.clear();  // 清空上一轮的病毒块格子记录
            boundaries.clear();  // 清空上一轮的威胁边界记录
            for (int i = 0; i < m; ++i) {  // 逐行扫描网格
                for (int j = 0; j < n; ++j) {  // 逐列扫描，找出每一个病毒连通块
                    if (infected[i][j] == 1 && !vis[i][j]) {  // 遇到还没被访问过的感染格，说明发现了一个新块
                        c.push_back(0);  // 为新块预置防火墙计数，DFS 过程中累加
                        areas.push_back({});  // 为新块准备空的格子列表
                        boundaries.push_back({});  // 为新块准备空的威胁边界集合
                        dfs(i, j);  // 深度优先遍历整块，填满上面三个容器
                    }  // 结束新块判定
                }  // 结束列扫描
            }  // 结束行扫描
            if (areas.empty()) break;  // 网格里已经没有病毒块，模拟结束
            int idx = getMax();  // 选出威胁边界最大（最危险）的块，优先隔离它
            ans += c[idx];  // 隔离它需要的防火墙数计入答案
            for (int t = 0; t < areas.size(); ++t) {  // 逐个处理每一块：被选中的隔离，其余的继续扩散
                if (t == idx) {  // 这一块被选为隔离对象
                    for (int v : areas[t]) {  // 遍历该块所有格子的线性编号
                        int i = v / n, j = v % n;  // 把线性编号还原成行列坐标
                        infected[i][j] = -1;  // 标记为已隔离，之后既不算病毒也不会再被传播
                    }  // 结束该块格子遍历
                } else {  // 其他块继续向外扩散
                    for (int v : areas[t]) {  // 遍历该块的所有格子
                        int i = v / n, j = v % n;  // 线性编号还原成行列坐标
                        for (int k = 0; k < 4; ++k) {  // 检查上下左右四个邻居
                            int x = i + dirs[k], y = j + dirs[k + 1];  // 用偏移数组算出邻居坐标
                            if (x >= 0 && x < m && y >= 0 && y < n && infected[x][y] == 0) infected[x][y] = 1;  // 邻居合法且是空地，就被这一块感染成 1
                        }  // 结束四方向检查
                    }  // 结束该块格子遍历
                }  // 结束隔离/扩散分支
            }  // 结束所有块的处理
        }  // 结束 while 模拟
        return ans;  // 返回累计的防火墙数量
    }  // 结束 containVirus 方法

    int getMax() {  // 返回威胁边界最大的病毒块下标
        int idx = 0;  // 先假定第 0 块最危险
        int mx = boundaries[0].size();  // mx 记录当前最大的边界规模
        for (int i = 1; i < boundaries.size(); ++i) {  // 从第 1 块开始比较
            int t = boundaries[i].size();  // 第 i 块的边界规模
            if (mx < t) {  // 找到更危险的块（规模相同则保留靠前的下标）
                mx = t;  // 更新最大规模
                idx = i;  // 更新下标
            }  // 结束更优判断
        }  // 结束遍历
        return idx;  // 返回边界最大块的编号
    }  // 结束 getMax 方法

    void dfs(int i, int j) {  // 从 (i, j) 出发遍历整个病毒块，同时统计建墙数与威胁边界
        vis[i][j] = true;  // 标记已访问，避免重复进入
        areas.back().push_back(i * n + j);  // 当前块是最后 push 的那一块，把格子编号记进它的列表
        for (int k = 0; k < 4; ++k) {  // 枚举上下左右四个邻居
            int x = i + dirs[k], y = j + dirs[k + 1];  // 用偏移数组算出邻居坐标
            if (x >= 0 && x < m && y >= 0 && y < n) {  // 邻居在网格范围内才继续判断
                if (infected[x][y] == 1 && !vis[x][y])  // 邻居是尚未访问的感染格，属于同一块
                    dfs(x, y);  // 递归深入，把连通部分全部走完
                else if (infected[x][y] == 0) {  // 邻居是空地：它会被这一块威胁，是建墙的位置
                    c.back() += 1;  // 这个方向需要一段防火墙
                    boundaries.back().insert(x * n + y);  // 集合天然去重，同一片空地只记一次
                }  // 结束空地处理
            }  // 结束范围判断
        }  // 结束四方向遍历
    }  // 结束 dfs 方法
};  // 结束 Solution 类