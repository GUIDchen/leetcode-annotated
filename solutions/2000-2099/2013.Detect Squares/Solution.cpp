// 题目：2013. 检测正方形（Detect Squares）
// 思路：用嵌套哈希表 cnt[x][y] 统计每个坐标的点数；查询时枚举另一条竖边的横坐标 x2，按带符号边长 d 配出上下两种正方形，累加三个顶点的计数乘积。
// 时间复杂度：add 为 O(1)，count 为 O(不同 x 的个数)（另有 O(log) 的哈希开销）；空间复杂度：O(n)，n 为已添加的点数。
class DetectSquares {  // 统计类，需要支持 add 与 count 两种操作
public:  // 对外接口
    DetectSquares() {  // 构造函数：题目保证先 add 再 count，这里无需初始化任何字段
    }  // 构造函数体为空

    void add(vector<int> point) {  // point = [x, y]，把一个点加入数据结构
        int x = point[0], y = point[1];  // 拆出横纵坐标，便于书写
        ++cnt[x][y];  // 在 x 这一层的哈希表里把 y 的计数加一（该键缺失时会自动插入 0）
    }  // add 结束

    int count(vector<int> point) {  // 返回能与 point 组成轴对齐正方形的已有点三元组个数
        int x1 = point[0], y1 = point[1];  // 查询点的横纵坐标
        if (!cnt.count(x1)) {  // 没有任何已添加的点与查询点同横坐标，构不成竖直边
            return 0;  // 直接返回 0
        }  // 提前返回分支结束
        int ans = 0;  // ans 累加所有可能的正方形个数
        for (auto& [x2, cnt2] : cnt) {  // 枚举另一条竖边的横坐标 x2 及其 y→次数 表
            if (x2 != x1) {  // x2 必须与 x1 不同，否则两个点会退化成同一条竖线
                int d = x2 - x1;  // 正方形边长（带符号），纵向偏移量也取它
                auto& cnt1 = cnt[x1];  // 取出 x1 这一层的 y→次数 表，下面用它查同纵坐标的点
                ans += cnt2[y1] * cnt1[y1 + d] * cnt2[y1 + d];  // 上侧正方形：另两顶点为 (x1, y1+d) 与 (x2, y1+d)，三点计数相乘
                ans += cnt2[y1] * cnt1[y1 - d] * cnt2[y1 - d];  // 下侧正方形：另两顶点为 (x1, y1-d) 与 (x2, y1-d)，三点计数相乘
            }  // 分支结束
        }  // 枚举结束
        return ans;  // 返回正方形总数
    }  // count 结束

private:  // 计数表设为私有，只允许通过 add 修改
    unordered_map<int, unordered_map<int, int>> cnt;  // cnt[x][y] 表示坐标 (x, y) 上的点数
};  // 类定义结束

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */