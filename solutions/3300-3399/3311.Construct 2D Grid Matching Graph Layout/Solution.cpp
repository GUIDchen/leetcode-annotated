// 题目：3311. 构造符合图结构的二维矩阵（Construct 2D Grid Matching Graph Layout）
// 思路：先按度数确定矩阵形状和第一行——存在度 1 的节点说明只有一行；没有度 4 的节点说明只有两行；否则从角点出发，每次走向「度数小于 4」的邻居，沿边界走到另一个角点得到第一行。之后逐行展开：当前行每个节点取第一个未访问的邻居，正好是它正下方（或正上方）的格子。
// 复杂度：时间 O(n + m)，建图与每行扫描各遍历一次邻接表；空间 O(n + m)，邻接表与标记数组的规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {  // n：节点个数（编号 0..n-1）；edges：无向边；返回还原出来的二维矩阵
        vector<vector<int>> g(n);  // 邻接表，g[i] 存放节点 i 的所有邻居
        for (auto& e : edges) {  // 逐条读入无向边
            int u = e[0], v = e[1];  // 拆出这条边的两个端点 u、v
            g[u].push_back(v);  // u 的邻接表加入 v
            g[v].push_back(u);  // v 的邻接表加入 u，无向图两个方向都要存
        }  // for 循环结束

        vector<int> deg(5, -1);  // deg[d] 记录「某个度数为 d 的节点」，初始 -1 表示不存在这种度数的节点
        for (int x = 0; x < n; ++x) {  // 枚举每个节点统计它的度数
            deg[g[x].size()] = x;  // 以度数作下标记下该节点；同度数有多个时只保留最后一个，取任意一个都够用
        }  // for 循环结束

        vector<int> row;  // row：存放矩阵的第一行，之后每一轮再算出下一行
        if (deg[1] != -1) {  // 存在度数为 1 的节点，说明整个图退化成一条链，矩阵只有一行
            row.push_back(deg[1]);  // 单行矩阵的唯一元素就是这个端点
        } else if (deg[4] == -1) {  // 没有度数为 4 的节点，说明矩阵只有两行（内部节点度数为 3）
            int x = deg[2];  // 取一个角点（度数为 2）作为第一行的起点
            for (int y : g[x]) {  // 在它的邻居里找同行的另一个角点
                if (g[y].size() == 2) {  // 邻居度数也是 2，说明它同样是角点，两者构成长度为 2 的第一行
                    row.push_back(x);  // 放入第一行第一列
                    row.push_back(y);  // 放入第一行第二列
                    break;  // 第一行已经凑齐两个节点，跳出查找
                }  // if 结束
            }  // for 循环结束
        } else {  // 否则矩阵至少 3 行 3 列，一定存在度数为 4 的内部节点
            int x = deg[2];  // 从某个角点（度数 2）出发
            row.push_back(x);  // 角点就是第一行的第一个节点
            int pre = x;  // pre 记录上一个节点，避免下一步走回头路
            x = g[x][0];  // 先沿某条边移动到相邻节点
            while (g[x].size() > 2) {  // 只要当前节点还不是角点（度数仍大于 2），就继续沿边界前进
                row.push_back(x);  // 把当前边界节点加入第一行
                for (int y : g[x]) {  // 在邻居中挑选下一步要走的方向
                    if (y != pre && g[y].size() < 4) {  // 不能回头，且度数小于 4：度数为 4 的邻居在内部，走进去就偏离了边界
                        pre = x;  // 把前驱更新为当前节点
                        x = y;  // 前进到下一个边界节点
                        break;  // 找到下一步就跳出内层循环
                    }  // if 结束
                }  // for 循环结束
            }  // while 结束，此时 x 已走到另一个角点
            row.push_back(x);  // 最后一个角点也要放进第一行
        }  // if/else if/else 分支结束

        vector<vector<int>> ans;  // 最终要返回的二维矩阵，按行存放
        ans.push_back(row);  // 先放入已经确定的第一行
        vector<bool> vis(n, false);  // vis[i]：节点 i 是否已经被放进矩阵，防止重复使用
        int rowSize = row.size();  // 每行的列数，由第一行的长度确定
        for (int i = 0; i < n / rowSize - 1; ++i) {  // 剩余行数为 n / rowSize - 1，逐行向下构造
            for (int x : row) {  // 先把当前行的节点全部标记为已使用
                vis[x] = true;  // 标记当前节点
            }  // for 循环结束
            vector<int> nxt;  // 待生成的下一行
            for (int x : row) {  // 当前行的每个节点各自向下找一个未使用的邻居
                for (int y : g[x]) {  // 遍历它的邻居
                    if (!vis[y]) {  // 第一个还没放进矩阵的邻居，就是它正下方的节点
                        nxt.push_back(y);  // 按当前行的列顺序收集，保证下一行与上一行列对齐
                        break;  // 每个节点只需要一个向下的邻居，找到就停
                    }  // if 结束
                }  // for 循环结束
            }  // for 循环结束
            ans.push_back(nxt);  // 把新算出的下一行加入答案
            row = nxt;  // 迭代：把下一行当作新的当前行继续向下构造
        }  // for 循环结束

        return ans;  // 返回构造出的二维矩阵
    }  // 方法结束
};  // 类定义结束
