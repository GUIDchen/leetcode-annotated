class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {  // intervals：互不重叠的区间列表；toBeRemoved：要删除的区间
        int x = toBeRemoved[0], y = toBeRemoved[1];  // 取出要删除区间的左右端点 x、y
        vector<vector<int>> ans;  // 存放删除后的区间结果
        for (auto& e : intervals) {  // 逐个处理原有区间
            int a = e[0], b = e[1];  // 当前区间的左右端点 a、b
            if (a >= y || b <= x) {  // 当前区间完全在删除区间的左边或右边，两者不相交
                ans.push_back(e);  // 没有重叠部分，原样保留
            } else {  // 否则说明当前区间与删除区间有交集
                if (a < x) {  // 交集左侧还剩下片段 [a, x)
                    ans.push_back({a, x});  // 保留左残段
                }  // 结束左残段判断
                if (b > y) {  // 交集右侧还剩下片段 (y, b]
                    ans.push_back({y, b});  // 保留右残段
                }  // 结束右残段判断
            }  // 结束 if/else 分支
        }  // 结束 for 循环
        return ans;  // 返回删除后的区间列表
    }  // removeInterval 方法结束
};  // Solution 类定义结束