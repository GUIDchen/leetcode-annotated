// 题目：1476. 子矩形查询（Subrectangle Queries）
// 思路：不真正修改矩阵，只把每次矩形赋值当作一条「历史操作」追加到 ops 里；查询时从最新操作往回找，第一个覆盖该点的操作即为答案，否则回落到初始矩阵。
// 时间复杂度：updateSubrectangle 为 O(1)，getValue 为 O(q)（q 为操作次数）；空间复杂度：O(r*c + q)，存放矩阵副本与操作列表。
class SubrectangleQueries {  // LeetCode 约定的题解类
public:  // 对外可见
    vector<vector<int>> g;  // 初始矩阵的副本，用于回答没有被任何更新操作覆盖的位置
    vector<vector<int>> ops;  // 历史操作列表，每项为 {row1, col1, row2, col2, newValue}

    SubrectangleQueries(vector<vector<int>>& rectangle) {  // 构造函数：接收初始矩阵
        g = rectangle;  // 保存一份初始矩阵
    }

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {  // 把子矩形内所有值更新为 newValue
        ops.push_back({row1, col1, row2, col2, newValue});  // 惰性更新：只记录这次操作，不真正遍历修改矩阵
    }

    int getValue(int row, int col) {  // 查询 (row, col) 处的当前值
        for (int i = ops.size() - 1; ~i; --i) {  // 从最新操作往回找；~i 即 i != -1
            auto op = ops[i];  // 取出这条历史操作
            if (op[0] <= row && row <= op[2] && op[1] <= col && col <= op[3]) {  // 该点是否落在这次操作的矩形内
                return op[4];  // 最新覆盖它的操作即为最终值，直接返回
            }
        }
        return g[row][col];  // 没有任何更新覆盖过它，返回初始矩阵中的值
    }
};

/**
 * Your SubrectangleQueries object will be instantiated and called as such:
 * SubrectangleQueries* obj = new SubrectangleQueries(rectangle);
 * obj->updateSubrectangle(row1,col1,row2,col2,newValue);
 * int param_2 = obj->getValue(row,col);
 */