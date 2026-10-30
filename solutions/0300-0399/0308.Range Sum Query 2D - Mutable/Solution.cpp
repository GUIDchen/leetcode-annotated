// 题目：308. 二维区域和检索 - 矩阵可修改（Range Sum Query 2D - Mutable）
// 思路：每行建一棵树状数组；单点修改只更新所在行，子矩阵求和按行累加一维区间和。
// 时间复杂度：更新 O(log n)、查询 O(m log n)；空间复杂度：O(mn)，每行一棵树状数组。
class BinaryIndexedTree {  // 一维树状数组，二维问题里每行各建一棵
public:  // 对外接口
    int n;  // 数组长度
    vector<int> c;  // c 为树状数组本体，1 基下标，长度 n+1

    BinaryIndexedTree(int _n)  // 构造函数
        : n(_n)  // 保存长度
        , c(_n + 1) {}  // c 分配 n+1 个位置

    void update(int x, int delta) {  // 在下标 x 处加上 delta
        while (x <= n) {  // 向上更新所有管辖 x 的节点
            c[x] += delta;  // 当前节点累加增量
            x += lowbit(x);  // 通过 lowbit 跳到下一个节点
        }  // 循环结束
    }  // update 结束

    int query(int x) {  // 查询前缀和 [1, x]
        int s = 0;  // 累加器
        while (x > 0) {  // 向下切分前缀
            s += c[x];  // 累加当前段
            x -= lowbit(x);  // 去掉最低位的 1，跳到前一段
        }  // 循环结束
        return s;  // 返回前缀和
    }  // query 结束

    int lowbit(int x) {  // 取 x 最低位的 1 所对应的值
        return x & -x;  // 位运算 x & -x 即 lowbit
    }  // lowbit 结束
};  // BinaryIndexedTree 类结束

class NumMatrix {  // LeetCode 约定的题解类
public:  // 对外接口
    vector<BinaryIndexedTree*> trees;  // 每一行存一棵树状数组，行内按列做前缀和

    NumMatrix(vector<vector<int>>& matrix) {  // 构造函数：matrix 是输入矩阵
        int m = matrix.size();  // 行数
        int n = matrix[0].size();  // 列数
        trees.resize(m);  // 为每行预留一个树状数组指针
        for (int i = 0; i < m; ++i) {  // 逐行建树
            BinaryIndexedTree* tree = new BinaryIndexedTree(n);  // 当前行新建一棵长度为 n 的树状数组
            for (int j = 0; j < n; ++j) tree->update(j + 1, matrix[i][j]);  // 把这一行的元素逐个插入（1 基下标）
            trees[i] = tree;  // 挂到对应行上
        }  // 行循环结束
    }  // 构造函数结束

    void update(int row, int col, int val) {  // 把 (row, col) 处的值改为 val
        BinaryIndexedTree* tree = trees[row];  // 取出该行对应的树状数组
        int prev = tree->query(col + 1) - tree->query(col);  // 单点查询得到原来的值
        tree->update(col + 1, val - prev);  // 只把差值更新进去
    }  // update 结束

    int sumRegion(int row1, int col1, int row2, int col2) {  // 查询子矩阵 (row1,col1)-(row2,col2) 的元素和
        int s = 0;  // 累加器
        for (int i = row1; i <= row2; ++i) {  // 逐行累加：每行贡献一个一维区间和
            BinaryIndexedTree* tree = trees[i];  // 取当前行的树状数组
            s += tree->query(col2 + 1) - tree->query(col1);  // 前缀和相减得到这一行在 [col1, col2] 内的和
        }  // 行循环结束
        return s;  // 返回子矩阵和
    }  // sumRegion 结束
};  // NumMatrix 类结束

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */