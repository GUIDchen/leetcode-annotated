// 题目：1632. 矩阵转换后的排名（Rank Transform of a Matrix）
// 思路：按值从小到大分组，把同值元素所在的行与列用并查集合并，取组内各行列当前最大排名作基准，最后统一写成基准 +1。
// 时间复杂度：O(mn·(log(mn) + α))，排序分组加并查集；空间复杂度：O(mn)，分组表与答案矩阵。
class UnionFind {  // 并查集：把同值的行结点与列结点合并到同一个「连通块」里
public:  // 对外接口
    UnionFind(int n) {  // 构造函数：n 个结点（这里是 m 行 + n 列）
        p = vector<int>(n);  // p 记录每个结点的父结点
        size = vector<int>(n, 1);  // size 记录每个根的集合大小，用于按大小合并
        iota(p.begin(), p.end(), 0);  // iota 把 p 填成 0,1,2,...,n-1，父结点初始指向自己
    }  // 构造函数结束

    void unite(int a, int b) {  // 合并 a、b 所在集合
        int pa = find(a), pb = find(b);  // 先找到两个结点各自的根
        if (pa != pb) {  // 根不同才需要合并
            if (size[pa] > size[pb]) {  // 比较集合大小，决定把哪一个根挂到另一个根下
                p[pb] = pa;  // pa 集合更大，把 pb 挂到 pa 下
                size[pa] += size[pb];  // 更新新根 pa 的集合大小
            } else {  // 否则（pb 更大或相等）做反向挂接
                p[pa] = pb;  // 把 pa 挂到 pb 下
                size[pb] += size[pa];  // 更新新根 pb 的集合大小
            }  // if-else 结束
        }  // if 结束
    }  // unite 方法结束

    int find(int x) {  // 查找 x 所在集合的根，路径压缩
        if (p[x] != x) {  // 父结点不是自己，说明还没到根
            p[x] = find(p[x]);  // 递归找根，并把路径上所有结点直接挂到根上
        }  // if 结束
        return p[x];  // 返回根结点编号
    }  // find 方法结束

    void reset(int x) {  // 重置单个结点：处理完一组同值元素后，把行/列结点恢复成独立状态
        p[x] = x;  // 父结点指回自己
        size[x] = 1;  // 集合大小恢复为 1
    }  // reset 方法结束

private:  // 以下为私有成员
    vector<int> p, size;  // 父结点数组与集合大小数组
};  // UnionFind 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {  // matrix 是 m×n 整数矩阵，返回每个位置按题意转换后的排名
        int m = matrix.size(), n = matrix[0].size();  // m、n 分别为行数与列数
        map<int, vector<pair<int, int>>> d;  // 有序表：键是矩阵值，值是该值出现的所有坐标（map 保证按值从小到大遍历）
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                d[matrix[i][j]].push_back({i, j});  // 把坐标 (i,j) 挂到对应值 v 的分组里
            }  // 列循环结束
        }  // 行循环结束
        vector<int> rowMax(m);  // rowMax[i]：第 i 行目前已知的最大排名
        vector<int> colMax(n);  // colMax[j]：第 j 列目前已知的最大排名
        vector<vector<int>> ans(m, vector<int>(n));  // 答案矩阵，m 行 n 列，初值为 0
        UnionFind uf(m + n);  // 并查集结点数 = m 个行结点 + n 个列结点，列编号后移 m 以免与行冲突
        vector<int> rank(m + n);  // rank[root]：该连通块当前的基准排名
        for (auto& [_, ps] : d) {  // 按值从小到大处理每一组（_ 是键，ps 是同值的所有坐标）
            for (auto& [i, j] : ps) {  // 第一遍：同值元素所在的行与列全部合并，表示它们排名必须相同
                uf.unite(i, j + m);  // 该元素所在行与所在列（列号 +m）合并
            }  // 遍历同值坐标结束
            for (auto& [i, j] : ps) {  // 第二遍：取整块内「行最大排名」「列最大排名」与自身基准的最大值，作为这块的新基准
                rank[uf.find(i)] = max({rank[uf.find(i)], rowMax[i], colMax[j]});  // 同一连通块内反复取 max，把基准统一到全块的最大值上
            }  // 遍历同值坐标结束
            for (auto& [i, j] : ps) {  // 第三遍：把基准 +1 写进答案，并同步更新该行、该列的最大排名
                ans[i][j] = rowMax[i] = colMax[j] = 1 + rank[uf.find(i)];  // 三个位置一起赋值：答案格、行最大、列最大
            }  // 遍历同值坐标结束
            for (auto& [i, j] : ps) {  // 第四遍：清空本组用到的行列结点，避免影响下一个更大的值
                uf.reset(i);  // 重置行结点
                uf.reset(j + m);  // 重置列结点（编号 +m）
            }  // 遍历同值坐标结束
        }  // 分组循环结束
        return ans;  // 返回转换后的排名矩阵
    }  // matrixRankTransform 方法结束
};  // 题解类定义结束