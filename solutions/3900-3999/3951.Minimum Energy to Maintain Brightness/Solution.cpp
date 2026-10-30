// 题目：3951. 维持亮度的最小总能量（Minimum Energy to Maintain Brightness）
// 思路：按左端点排序后合并所有区间，对合并后的每段长度 m，每点需要 ceil(brightness/3) 点能量，累加 (brightness+2)/3*m。
// 复杂度：时间 O(n log n)（排序），空间 O(n)（存合并结果）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minEnergy(int n, int brightness, vector<vector<int>>& intervals) {  // intervals 是若干区间，brightness 是每个位置要维持的亮度
        sort(intervals.begin(), intervals.end());  // 按左端点排序，便于线性合并
        vector<vector<int>> merged = {intervals[0]};  // merged 存放合并后的互不相交区间，先放入第一个区间
        for (int i = 1; i < intervals.size(); ++i) {  // 从第二个区间开始逐个合并
            auto& x = intervals[i];  // x 是当前待合并的区间
            if (merged.back()[1] < x[0]) {  // 最后一个合并区间的右端点与 x 的左端点之间有间隙
                merged.push_back(x);  // 没有重叠，直接作为一个新区间加入
            } else {  // 否则两者重叠或相邻，需要合并到最后一个区间
                merged.back()[1] = max(merged.back()[1], x[1]);  // 右端点扩展为两者中较大的那个
            }
        }
        long long ans = 0;  // ans 累计总能量
        for (const auto& interval : merged) {  // 遍历合并后的每个区间
            int start = interval[0];  // 区间左端点
            int end = interval[1];  // 区间右端点
            int m = end - start + 1;  // m 是区间长度（包含两端）
            ans += (brightness + 2LL) / 3 * m;  // 每个位置需要 ceil(brightness/3) 点能量，乘以整段长度后累加
        }
        return ans;  // 返回维持亮度所需的最小总能量
    }
};