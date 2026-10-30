// 题目：497. 非重叠矩形中的随机点（Random Point in Non-overlapping Rectangles）
// 思路：先按每个矩形覆盖的整数点个数做前缀和，随机抽出一个 1..总点数 的序号，二分定位它落在哪个矩形，再在该矩形内均匀取点。
// 时间复杂度：构造 O(n)，pick 为 O(log n)；空间复杂度：O(n)，前缀和数组与矩形副本各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> s;  // 前缀和：s[i] 表示前 i 个矩形覆盖的整数点总数
    vector<vector<int>> rects;  // 矩形列表的副本，pick 时需要反复读取

    Solution(vector<vector<int>>& rects) {  // 构造函数：先建前缀和表，再用当前时间初始化随机数种子
        int n = rects.size();  // 矩形个数
        s.resize(n + 1);  // 前缀和长度取 n+1，s[0] 恒为 0，便于统一递推式
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + (rects[i][2] - rects[i][0] + 1) * (rects[i][3] - rects[i][1] + 1);  // 单行 for：第 i 个矩形的点数是 (x2-x1+1)*(y2-y1+1)，累加到 s[i+1]
        this->rects = rects;  // 把矩形列表拷贝到成员变量，供 pick 使用
        srand(time(nullptr));  // 用当前时间播种，避免每次运行的随机序列完全相同
    }  // 构造函数结束

    vector<int> pick() {  // 在矩形并集中按点数加权等概率取一个整数点
        int n = rects.size();  // 矩形个数
        int v = 1 + rand() % s[n];  // 在 [1, 总点数] 中等概率抽一个序号
        int idx = lower_bound(s.begin(), s.end(), v) - s.begin();  // 二分找第一个前缀和大于等于 v 的位置，即 v 落在的矩形（下标偏移了 1）
        auto& rect = rects[idx - 1];  // 下标减一还原：s 比 rects 多一个前导 0
        int x = rect[0] + rand() % (rect[2] - rect[0] + 1);  // 在该矩形的 x 区间内均匀取整数横坐标
        int y = rect[1] + rand() % (rect[3] - rect[1] + 1);  // 在该矩形的 y 区间内均匀取整数纵坐标
        return {x, y};  // 按题目要求返回 {x, y}
    }  // pick 方法结束
};  // 类定义结束

// 下面这段是 LeetCode 判题器自动生成的调用模板，属于平台模板而非解题代码
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */