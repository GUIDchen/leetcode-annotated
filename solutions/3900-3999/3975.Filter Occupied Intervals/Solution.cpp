// 3975. Filter Occupied Intervals | 筛选忙碌区间（中等）
// 核心思路：先把occupiedIntervals 升序排序，顺序扫描合并“相隔不超过 1”的区间得到合并后的忙碌区间集合；再对每个合并区间判断它与空闲区间 [freeStart, freeEnd] 的关系：完全不相交就整段保留，相交则只保留左、右两侧露出来的部分（可能是空）。
// 复杂度：时间 O(n log n)，瓶颈在排序，合并与切割各是 O(n)；空间 O(n)，存放合并后的忙碌区间与答案。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd) {  // 返回扣掉空闲区间后剩余的忙碌区间
        sort(occupiedIntervals.begin(), occupiedIntervals.end());  // 按左端点（相同时再按右端点）升序排序，便于顺序合并

        vector<vector<int>> busy;  // 合并后的忙碌区间集合
        busy.push_back(occupiedIntervals[0]);  // 第一个区间先当作已合并区间的起点

        for (int i = 1; i < occupiedIntervals.size(); i++) {  // 从第二个区间开始顺序扫描
            auto& cur = occupiedIntervals[i];  // 当前待合并区间
            auto& last = busy.back();  // 已合并区间集合的最后一个区间

            if (last[1] + 1 < cur[0]) {  // 中间存在真正的空隙（差超过 1），无法合并
                busy.push_back(cur);  // 当前区间作为一个新的忙碌区间
            } else {  // 重叠或首尾相邻（last[1] + 1 == cur[0] 也算连成一片）
                last[1] = max(last[1], cur[1]);  // 只把右端点扩展到两者的最大值，左端点保持不变
            }  // if 结束
        }  // 合并扫描结束

        vector<vector<int>> ans;  // 存放最终答案

        for (auto& it : busy) {  // 逐个处理合并后的忙碌区间
            int s = it[0], e = it[1];  // 取出该区间的左右端点

            if (e < freeStart || s > freeEnd) {  // 与空闲区间完全没有交集
                ans.push_back({s, e});  // 整段保留
            } else {  // 与空闲区间有交集，需要把空闲那段挖掉
                if (s < freeStart) {  // 左侧还有露出尾部的一部分
                    ans.push_back({s, freeStart - 1});  // 保留 [s, freeStart - 1]
                }  // if 结束
                if (e > freeEnd) {  // 右侧还有露出头部的一部分
                    ans.push_back({freeEnd + 1, e});  // 保留 [freeEnd + 1, e]
                }  // if 结束
            }  // if-else 结束
        }  // 切割扫描结束

        return ans;  // 返回剔除空闲区间后的忙碌区间
    }  // 方法结束
};  // 类定义结束