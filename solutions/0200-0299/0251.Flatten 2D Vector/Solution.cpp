// 题目：251. 展开二维向量（Flatten 2D Vector）
// 思路：维护二维下标 (i, j)，每次 next/hasNext 前先用 forward() 跳过空行与已遍历完的行，实现惰性按行展开。
// 时间复杂度：均摊 O(1)，每个元素最多被跳过一次；空间复杂度：O(1)，只保存两个下标。
class Vector2D {  // 迭代器类：把二维数组按行展开成线性序列
public:  // 对外接口
    Vector2D(vector<vector<int>>& vec) {  // 构造函数：接收二维数组
        this->vec = move(vec);  // 用 move 接管数据，避免整份拷贝
    }  // 构造函数结束

    int next() {  // 返回下一个元素，并把游标后移一位
        forward();  // 先跳过已结束的行，保证游标指向真实元素
        return vec[i][j++];  // 取出当前元素，然后列下标自增
    }  // next 结束

    bool hasNext() {  // 是否还有元素可读
        forward();  // 先规整游标位置
        return i < vec.size();  // 行下标没越界说明还有剩余元素
    }  // hasNext 结束

private:  // 以下是内部状态
    int i = 0;  // 当前行下标
    int j = 0;  // 当前行内的列下标
    vector<vector<int>> vec;  // 被遍历的二维数组（构造时已接管）

    void forward() {  // 把 (i, j) 推进到下一个有效元素的位置
        while (i < vec.size() && j >= vec[i].size()) {  // 当前行已遍历完（可能是空行）就换到下一行
            ++i;  // 行下标加一
            j = 0;  // 新行从第 0 列开始
        }  // 结束跳行循环
    }  // forward 结束
};  // 结束 Vector2D 类

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */