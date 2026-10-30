// 3391. 设计一个高效的层跟踪三维二进制矩阵 / Design a 3D Binary Matrix with Efficient Layer Tracking
// 核心思路：三维数组 g 记录每个格子的状态，cnt[x] 统计第 x 层中 1 的个数，有序集合按 (-cnt[x], -x) 排序，首元素即 1 最多的层（并列取层号大者），从而只需 O(log n) 就能完成更新与查询
// 复杂度：时间 O(log n)（集合增删为 O(log n)，其余操作 O(1)）、空间 O(n^3)
class matrix3D {  // 定义 matrix3D 类
private:  // 以下为私有成员
    vector<vector<vector<int>>> g;  // g[x][y][z] 表示第 x 层第 (y, z) 个位置是否为 1
    vector<int> cnt;  // cnt[x] 表示第 x 层中 1 的个数
    set<pair<int, int>> sl;  // 有序集合，存放 (-cnt[x], -x)，按 1 的个数降序、层号降序排列

public:  // 以下为公有接口
    matrix3D(int n) {  // 构造函数，建立 n * n * n 的三维矩阵
        g.resize(n, vector<vector<int>>(n, vector<int>(n, 0)));  // 初始化三维数组，全部填 0
        cnt.resize(n, 0);  // 每层 1 的个数初始化为 0
    }  // 构造函数结束

    void setCell(int x, int y, int z) {  // 把 (x, y, z) 位置置为 1
        if (g[x][y][z] == 1) {  // 该位置已经是 1
            return;  // 无需重复操作，直接返回
        }  // 判断结束
        g[x][y][z] = 1;  // 将该格子置为 1
        sl.erase({-cnt[x], -x});  // 先从有序集合中删除第 x 层的旧记录
        cnt[x]++;  // 第 x 层 1 的个数加一
        sl.insert({-cnt[x], -x});  // 再把第 x 层的新记录插入有序集合
    }  // setCell 结束

    void unsetCell(int x, int y, int z) {  // 把 (x, y, z) 位置置为 0
        if (g[x][y][z] == 0) {  // 该位置本来就是 0
            return;  // 无需重复操作，直接返回
        }  // 判断结束
        g[x][y][z] = 0;  // 将该格子置为 0
        sl.erase({-cnt[x], -x});  // 先从有序集合中删除第 x 层的旧记录
        cnt[x]--;  // 第 x 层 1 的个数减一
        if (cnt[x]) {  // 只有该层还剩 1 时才需要记录
            sl.insert({-cnt[x], -x});  // 把更新后的记录重新插入有序集合
        }  // 判断结束
    }  // unsetCell 结束

    int largestMatrix() {  // 返回 1 的个数最多的层号（并列取层号较大者）
        return sl.empty() ? g.size() - 1 : -sl.begin()->second;  // 集合为空说明没有 1，返回最大层号；否则由首元素取反得到层号
    }  // largestMatrix 结束
};  // 类定义结束

/**
 * Your matrix3D object will be instantiated and called as such:
 * matrix3D* obj = new matrix3D(n);
 * obj->setCell(x,y,z);
 * obj->unsetCell(x,y,z);
 * int param_3 = obj->largestMatrix();
 */
