// 题目：2080. 区间内查询数字的频率（Range Frequency Queries）
// 思路：预处理把每个值出现的下标按顺序存进哈希表；查询时对该值的下标数组做两次二分，得到 [left, right] 内的个数。
// 时间复杂度：构造函数 O(n)，每次查询 O(log n)；空间复杂度：O(n)，哈希表存下所有下标。
class RangeFreqQuery {  // 设计类：预处理 + 二分查询
public:  // 构造函数与 query 对外可见
    RangeFreqQuery(vector<int>& arr) {  // 构造函数：arr 为初始数组，一次预处理后支持多次查询
        for (int i = 0; i < arr.size(); ++i) {  // 顺序遍历数组，记录每个值出现在哪些下标
            g[arr[i]].push_back(i);  // 把下标 i 追加到值 arr[i] 对应的列表，下标天然递增
        }  // 结束预处理循环
    }  // 构造函数结束

    int query(int left, int right, int value) {  // 查询 value 在闭区间 [left, right] 中的出现次数
        if (!g.contains(value)) {  // 该值从未出现过，出现次数必然是 0
            return 0;  // 直接返回 0
        }  // 结束 if
        auto& idx = g[value];  // 取出该值的有序下标数组（引用，避免拷贝）
        auto l = lower_bound(idx.begin(), idx.end(), left);  // 第一个 >= left 的位置，即区间内第一个下标
        auto r = lower_bound(idx.begin(), idx.end(), right + 1);  // 第一个 >= right+1，即第一个 > right 的位置（区间右边界外）
        return r - l;  // 两个迭代器相减就是区间内的出现次数
    }  // 结束 query 方法

private:  // 私有数据成员，对外不可见
    unordered_map<int, vector<int>> g;  // 哈希表：值 -> 该值出现的所有下标（升序）
};  // 类定义结束

// 下面是判题器创建对象并调用方法的示例，属于题面说明，不是需要提交的代码
/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */