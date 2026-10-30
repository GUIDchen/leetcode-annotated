// 题目：370. 区间加法（Range Addition）
// 思路：差分数组。每次区间加 c 只需 d[l] += c 且 d[r+1] -= c，最后对差分数组求前缀和即得每个位置的总增量。
// 时间复杂度：O(n + m)，m 为更新次数；空间复杂度：O(n)，差分数组即答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {  // length：数组长度；updates 每项是 [左端点, 右端点, 增量]
        vector<int> d(length);  // 差分数组，初始全 0，最后原地变成前缀和结果
        for (const auto& e : updates) {  // 逐条处理区间更新
            int l = e[0], r = e[1], c = e[2];  // 拆出左端点 l、右端点 r 和增量 c，变量名与题目语义直接对应
            d[l] += c;  // 区间起点加 c：从 l 开始所有位置都受影响
            if (r + 1 < length) {  // 只有右端点后面还有元素时才需要抵消
                d[r + 1] -= c;  // 区间终点之后减 c，把影响范围截断在 r
            }  // if 分支闭合
        }  // 所有更新处理完毕
        for (int i = 1; i < length; ++i) {  // 从第二个位置开始做前缀和，把区间影响累积回每个下标
            d[i] += d[i - 1];  // 累加差分值得到当前位置的总增量
        }  // 前缀和循环闭合
        return d;  // 此时 d 已就地变为最终结果，直接返回
    }  // 方法结束
};  // 类定义结束
