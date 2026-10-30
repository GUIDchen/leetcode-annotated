// 题目：973. 最接近原点的 K 个点（K Closest Points to Origin）
// 思路：直接按到原点的欧氏距离升序排序，排序后的前 k 个点就是答案。
// 时间复杂度：O(n log n)，来自排序；空间复杂度：O(k)，返回结果占用的空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {  // points：所有点的坐标；k：需要取出的点数
        sort(points.begin(), points.end(), [](const vector<int>& p1, const vector<int>& p2) {  // 按到原点的距离从小到大排序，比较器用 hypot 计算欧氏距离
            return hypot(p1[0], p1[1]) < hypot(p2[0], p2[1]);  // hypot(dx, dy) 等价于 sqrt(dx*dx + dy*dy)，可避免中间结果溢出
        });  // 排序结束，此时最近的 k 个点排在前面
        return vector<vector<int>>(points.begin(), points.begin() + k);  // 取排序后的前 k 个元素构造答案返回
    }  // 题解方法结束
};  // Solution 类结束
