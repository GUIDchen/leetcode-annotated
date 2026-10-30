// 题目：452. 用最少数量的箭引爆气球（Minimum Number of Arrows to Burst Balloons）
// 思路：把所有气球按右端点升序排序，贪心地让每支箭都落在当前未覆盖气球的最右端点；一旦某个气球的左端点超过该位置，就必须再补一支箭。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序所需的递归栈（不计输入本身）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMinArrowShots(vector<vector<int>>& points) {  // points：每个气球的闭区间 [左端点, 右端点]；返回引爆全部气球的最少箭数
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {  // 按右端点升序排序，使每个气球尽量早地被处理
            return a[1] < b[1];  // 右端点更小的气球排在前面，便于贪心确定箭的落点
        });  // 结束排序
        int ans = 0;  // ans：已经使用的箭数
        long long last = -(1LL << 60);  // 最后一支箭的落点，初值取足够小的负数，保证第一支箭一定会被发射
        for (auto& p : points) {  // 按右端点升序依次处理每个气球
            int a = p[0], b = p[1];  // 当前气球的左右端点
            if (a > last) {  // 左端点超过上一支箭的落点，说明当前气球没有被覆盖
                ++ans;  // 必须再射一支箭
                last = b;  // 新箭放在当前气球的右端点，这样能尽可能多地覆盖后面的气球
            }  // 结束「是否需要新箭」的判断
        }  // 结束遍历
        return ans;  // 返回最少箭数
    }  // 结束 findMinArrowShots
};  // 结束 Solution 类