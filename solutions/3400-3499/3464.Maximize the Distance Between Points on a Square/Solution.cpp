// 3464. 正方形上的点之间的最大距离 / Maximize the Distance Between Points on a Square
// 核心思路：把正方形边界上的点按顺时针展开成一维周长坐标，再二分最小间距，用贪心在环上验证能否选出 k 个点。
// 复杂度：时间 O(n k log n log side)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有方法
    int maxDistance(int side, vector<vector<int>>& points, int k) {  // 返回任意 k 个点之间最小距离的最大值
        vector<long long> nums;  // 把边界上的点映射为顺时针周长坐标
        for (auto& p : points) {  // 遍历所有给定点
            int x = p[0];  // 横坐标
            int y = p[1];  // 纵坐标
            if (x == 0) {  // 点落在左边（x == 0）
                nums.push_back((long long) y);  // 左边按 y 从下到上编号
            } else if (y == side) {  // 点落在上边（y == side）
                nums.push_back((long long) side + x);  // 上边从左上角起算
            } else if (x == side) {  // 点落在右边（x == side）
                nums.push_back((long long) side * 3 - y);  // 右边从右上角向下编号
            } else {  // 否则点落在下边
                nums.push_back((long long) side * 4 - x);  // 下边从右下角向左编号
            }  // 结束边界判定
        }  // 结束点遍历
        sort(nums.begin(), nums.end());  // 按周长坐标升序排序，便于二分找后继点

        auto check = [&](int lo) -> bool {  // 判定能否选出 k 个点，使相邻点顺时针间距都不小于 lo
            long long total = (long long) side * 4;  // 正方形周长，用于处理首尾相接的环
            for (long long start : nums) {  // 枚举第一个点
                long long end = start + total - lo;  // 最后一个点最晚的坐标，保证它与起点绕回后的间距也不小于 lo
                long long cur = start;  // 当前已选点坐标
                bool ok = true;  // 该起点是否可行
                for (int i = 0; i < k - 1; ++i) {  // 还需要再选 k-1 个点
                    auto it = lower_bound(nums.begin(), nums.end(), cur + lo);  // 找第一个坐标不小于 cur + lo 的点
                    if (it == nums.end() || *it > end) {  // 找不到后继点，或后继点超出上界
                        ok = false;  // 该起点不可行
                        break;  // 提前结束贪心
                    }  // 结束失败分支
                    cur = *it;  // 选中该点，继续向后贪心
                }  // 结束选点循环
                if (ok) {  // k 个点已全部选出
                    return true;  // 该起点可行，判定成功
                }  // 结束可行分支
            }  // 结束起点枚举
            return false;  // 所有起点都不可行
        };  // 结束 check 函数

        int l = 1, r = side;  // 答案的二分区间：最小 1，最大为边长
        while (l < r) {  // 二分最大可行间距
            int mid = (l + r + 1) >> 1;  // 取上中位数，避免只剩两个元素时死循环
            if (check(mid)) {  // mid 可行，尝试更大间距
                l = mid;  // 下界抬到 mid
            } else {  // mid 不可行
                r = mid - 1;  // 上界降到 mid - 1
            }  // 结束分支
        }  // 结束二分
        return l;  // l 即最大可行最小间距
    }  // 结束方法
};  // 结束类定义
